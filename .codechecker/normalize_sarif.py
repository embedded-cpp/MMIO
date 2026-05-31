#!/usr/bin/env python3
"""
Normalise les chemins de fichiers dans un rapport SARIF pour qu'ils soient
relatifs à la racine du dépôt.

SonarCloud exige des chemins relatifs correspondant à sonar.sources.
Les chemins absolus produits par CodeChecker ne fonctionnent pas entre jobs CI.

Usage : python3 .codechecker/normalize_sarif.py <sarif_file> <repo_root>
"""

import json
import os
import sys


def _to_relative(uri: str, root: str) -> str:
    """
    Convertit un URI (absolu, ou préfixé 'file://') en chemin relatif à root.
    Retourne l'URI inchangé s'il n'est pas sous root.
    """
    path = uri[len("file://") :] if uri.startswith("file://") else uri
    if os.path.isabs(path):
        try:
            return os.path.relpath(path, root)
        except ValueError:
            # Windows : drives différents
            return path
    return path


def _normalize_artifact_location(location: dict, root: str) -> bool:
    """Normalise le champ 'uri' d'un artifactLocation. Retourne True si modifié."""
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
    Normalise tous les chemins de fichiers dans le rapport SARIF.
    Retourne le nombre de chemins modifiés.
    """
    with open(sarif_path, encoding="utf-8") as f:
        sarif = json.load(f)

    fixed = 0
    root = os.path.abspath(repo_root)

    for run in sarif.get("runs", []):
        # Déclarations d'artefacts
        for artifact in run.get("artifacts", []):
            if _normalize_artifact_location(artifact.get("location", {}), root):
                fixed += 1

        # Résultats
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
        print(f"Erreur : fichier SARIF introuvable : {sarif_file}", file=sys.stderr)
        sys.exit(1)

    count = normalize_sarif(sarif_file, os.path.abspath(repo_root))
    print(f"Normalisé : {count} chemin(s) dans {sarif_file}")
    print(f"Racine de référence : {os.path.abspath(repo_root)}")


if __name__ == "__main__":
    main()