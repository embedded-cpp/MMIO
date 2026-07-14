# Contributing

Contributions are welcome. If you would like to improve MMIO, please open an issue or start a discussion first so the direction of the change can be discussed clearly.

## Contribution guidelines

Please keep the following expectations in mind:

- Follow the existing C++ and CMake style of the repository.
- Keep changes focused and easy to review.
- Update documentation when behavior or usage changes.
- Ensure your change does not introduce regressions.

## What is expected before merging

The project uses GitHub workflows to validate contributions:

- style checks run through the style workflow and expect formatting to be valid
- unit tests are expected to pass for the core library behavior
- integration builds are expected to stay compatible with the target MCU configuration
- documentation generation should continue to work for the published docs site
- no new static analysis defects

## Practical advice

Before opening a pull request, make sure that:

1. the change builds locally,
2. relevant tests still pass,
3. the docs still build if your change affects documentation or public API usage.

If you are unsure about the scope of a change, opening a discussion first is a good idea.
