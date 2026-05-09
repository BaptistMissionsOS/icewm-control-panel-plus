# Contributing to IceWM Control Panel Plus

Thank you for considering contributing to this project! Below are some guidelines to help you get started.

## How to Contribute

1. **Fork the repository**
   - Click the **Fork** button at the top right of the repository page.
2. **Clone your fork**
   ```bash
   git clone https://github.com/your-username/icewm-control-panel-plus.git
   cd icewm-control-panel-plus
   ```
3. **Create a new branch** for your changes:
   ```bash
   git checkout -b my-feature-branch
   ```
4. **Make your changes**
   - Follow the existing code style and conventions.
5. **Commit your changes**
   ```bash
   git add .
   git commit -m "Brief description of your changes"
   ```
6. **Push to your fork**
   ```bash
   git push origin my-feature-branch
   ```
7. **Open a Pull Request**
   - Navigate to the original repository and click **New Pull Request**.
   - Provide a clear description of what you have done and why.

## Code Style

- Use **C++17** features and follow the existing coding style.
- Run `clang-format` (or the project's formatting tool) before committing.
- Keep lines under 100 characters where possible.

## Testing

- Add or update unit tests for any new functionality.
- Run the test suite locally:
  ```bash
  ctest
  ```
- Ensure all tests pass before submitting a PR.

## Documentation

- Update the `README.md` or relevant documentation files if your changes affect usage.
- If you add new public APIs, document them using Doxygen comments.

## Reporting Issues

- Use the **Issues** tab on GitHub to report bugs or request features.
- Provide a clear title, description, and steps to reproduce (if applicable).

## License

By contributing, you agree that your contributions will be licensed under the same GPL‑3.0 license as the project.

---

