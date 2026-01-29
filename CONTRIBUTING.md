# Contributing to Budget Tracker Application

First off, thank you for considering contributing to the Budget Tracker Application! It's people like you that make this project better for everyone.

## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [How Can I Contribute?](#how-can-i-contribute)
  - [Reporting Bugs](#reporting-bugs)
  - [Suggesting Enhancements](#suggesting-enhancements)
  - [Your First Code Contribution](#your-first-code-contribution)
  - [Pull Requests](#pull-requests)
- [Style Guidelines](#style-guidelines)
  - [Git Commit Messages](#git-commit-messages)
  - [C++ Style Guide](#c-style-guide)
  - [Documentation Style Guide](#documentation-style-guide)

## Code of Conduct

This project and everyone participating in it is governed by our Code of Conduct. By participating, you are expected to uphold this code. Please report unacceptable behavior to mnk.7muzammil86@gmail.com.

## How Can I Contribute?

### Reporting Bugs

Before creating bug reports, please check the existing issues to see if the problem has already been reported. If it has and the issue is still open, add a comment to the existing issue instead of opening a new one.

**When filing a bug report, please include:**

- A clear and descriptive title
- Exact steps to reproduce the problem
- Expected behavior vs. actual behavior
- Screenshots if applicable
- Your environment (OS, Qt version, compiler)
- Any error messages or logs

### Suggesting Enhancements

Enhancement suggestions are tracked as GitHub issues. When creating an enhancement suggestion, please include:

- A clear and descriptive title
- A detailed description of the proposed functionality
- Explain why this enhancement would be useful
- List any alternative solutions you've considered

### Your First Code Contribution

Unsure where to begin? You can start by looking through `beginner` and `help-wanted` issues:

- **Beginner issues** - issues which should only require a few lines of code
- **Help wanted issues** - issues which are more involved than beginner issues

### Pull Requests

1. **Fork the repository** and create your branch from `main`
2. **Follow the project structure**:
   - Source files (`.cpp`) go in `src/`
   - Header files (`.h`) go in `include/`
   - Resources (`.qrc`, images) go in `resources/`
   - Build files go in `build/`
3. **Write clear, commented code** that follows the project's style guidelines
4. **Test your changes** thoroughly before submitting
5. **Update documentation** if you're changing functionality
6. **Write a clear commit message** following our commit message guidelines
7. **Create a pull request** with a clear title and description

## Style Guidelines

### Git Commit Messages

- Use the present tense ("Add feature" not "Added feature")
- Use the imperative mood ("Move file to..." not "Moves file to...")
- Limit the first line to 72 characters or less
- Reference issues and pull requests after the first line
- Consider starting the commit message with an applicable emoji:
  - 🎨 `:art:` when improving code structure/format
  - 🐛 `:bug:` when fixing a bug
  - ✨ `:sparkles:` when adding a new feature
  - 📝 `:memo:` when writing docs
  - 🚀 `:rocket:` when improving performance
  - ✅ `:white_check_mark:` when adding tests

### C++ Style Guide

- **Naming Conventions**:
  - Classes: `PascalCase` (e.g., `Transaction`, `Project`)
  - Functions/Methods: `camelCase` (e.g., `getUserId`, `onAddIncome`)
  - Variables: `camelCase` (e.g., `userId`, `currentBalance`)
  - Constants: `UPPER_CASE` (e.g., `MAX_TRANSACTIONS`)
  - Private members: `camelCase` (e.g., `userId`, `tableWidget`)

- **Code Organization**:
  - One class per file (with matching `.h` and `.cpp` files)
  - Include guards in all header files
  - Forward declarations when possible to reduce dependencies
  - Keep functions short and focused on a single task

- **Comments**:
  - Use `//` for single-line comments
  - Use `/** */` for documentation comments (Doxygen style)
  - Comment complex algorithms and business logic
  - Keep comments up-to-date with code changes

- **Formatting**:
  - Indentation: 4 spaces (no tabs)
  - Line length: Maximum 100 characters
  - Braces: Opening brace on the same line for functions and control structures
  - One statement per line

### Documentation Style Guide

- Use **Markdown** for all documentation
- Include code examples where appropriate
- Use clear, concise language
- Structure documents with proper headings
- Keep the README up-to-date with any changes
- Add screenshots or diagrams when they add value

## Questions?

Feel free to contact the maintainer at mnk.7muzammil86@gmail.com or open an issue with your question.

Thank you for contributing! 🎉
