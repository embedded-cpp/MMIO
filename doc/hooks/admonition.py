import re

SIMPLE_MAP = {
    "Warning": "warning",
    "Note": "note",
    "Bug": "bug",
    "Attention": "warning",
    "Remark": "note",
    "Precondition": "info",
    "Postcondition": "info",
    "Invariant": "info",
}

SIMPLE_PATTERN = re.compile(
    r"\*\*(" + "|".join(re.escape(k) for k in SIMPLE_MAP) + r"):\*\*\n+"
    r"(.*?)"
    r"(?=\n\n\*\*\w|\n<hr>|\n#{1,6}\s|\Z)",
    re.DOTALL,
)


def _indent(body: str) -> str:
    return "\n".join(
        f"    {line}" if line.strip() else "" for line in body.rstrip().splitlines()
    )


def _repl_simple(m):
    title, body = m.group(1), m.group(2)
    kind = SIMPLE_MAP[title]
    return f'!!! {kind} "{title}"\n{_indent(body)}\n\n'


def on_page_markdown(markdown, page, config, files):
    markdown = SIMPLE_PATTERN.sub(_repl_simple, markdown)
    return markdown
