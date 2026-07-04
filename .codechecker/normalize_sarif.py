#!/usr/bin/env python3
"""
Normalize file paths in a SARIF report so they are
relative to the repository root.

SonarCloud requires relative paths matching sonar.sources.
The absolute paths produced by CodeChecker do not work across CI jobs.

Usage: python3 .codechecker/normalize_sarif.py <sarif_file> <repo_root>
"""

import json
import os
import sys


def _to_relative(uri: str, root: str) -> str:
    """
    Convert a URI (absolute, or prefixed with 'file://') into a path relative to root.
    Return the URI unchanged if it is not under root.
    """
    path = uri[len("file://") :] if uri.startswith("file://") else uri
    if os.path.isabs(path):
        try:
            return os.path.relpath(path, root)
        except ValueError:
            # Windows: different drives
            return path
    return path


def _normalize_artifact_location(location: dict, root: str) -> bool:
    """Normalize the 'uri' field of an artifactLocation. Return True if modified."""
    uri = location.get("uri", "")
    if not uri:
        return False
    normalized = _to_relative(uri, root)
    if normalized != uri:
        location["uri"] = normalized
        return True
    return False


def normalize_sarif(sarif_path: str, repo_root: str) -> int:
    """
    Normalize all file paths in the SARIF report.
    Return the number of paths modified.
    """
    with open(sarif_path, encoding="utf-8") as f:
        sarif = json.load(f)

    fixed = 0
    root = os.path.abspath(repo_root)

    for run in sarif.get("runs", []):
        # Artifact declarations
        for artifact in run.get("artifacts", []):
            if _normalize_artifact_location(artifact.get("location", {}), root):
                fixed += 1

        # Results
        for result in run.get("results", []):
            for loc in result.get("locations", []):
                phys = loc.get("physicalLocation", {})
                if _normalize_artifact_location(phys.get("artifactLocation", {}), root):
                    fixed += 1

            for related in result.get("relatedLocations", []):
                phys = related.get("physicalLocation", {})
                if _normalize_artifact_location(phys.get("artifactLocation", {}), root):
                    fixed += 1

    with open(sarif_path, "w", encoding="utf-8") as f:
        json.dump(sarif, f, indent=2)

    return fixed


def main() -> None:
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <sarif_file> <repo_root>", file=sys.stderr)
        sys.exit(1)

    sarif_file, repo_root = sys.argv[1], sys.argv[2]

    if not os.path.isfile(sarif_file):
        print(f"Error: SARIF file not found: {sarif_file}", file=sys.stderr)
        sys.exit(1)

    count = normalize_sarif(sarif_file, os.path.abspath(repo_root))
    print(f"Normalized: {count} path(s) in {sarif_file}")
    print(f"Reference root: {os.path.abspath(repo_root)}")


if __name__ == "__main__":
    main()