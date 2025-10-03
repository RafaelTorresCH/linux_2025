# Prompt Log

## 1. Project Structure Setup
**Prompt:** Create a basic project structure for an embedded Linux systemd service assignment.
**AI Response:** Suggested creating directories `src/`, `systemd/`, `tests/`, `ai/`, and top-level files `README.md`, `Makefile`, and `.gitignore`.
**Commit:** [commit-hash]

## 2. C Program Implementation
**Prompt:** Write a C program named `assignment-sensor.c` that accepts CLI flags, reads from `/dev/urandom`, logs data, and handles SIGTERM.
**AI Response:** Provided a complete implementation with error handling, fallback for unwritable `/tmp`, and ISO-8601 timestamp formatting.
**Commit:** [commit-hash]

## 3. Makefile Creation
**Prompt:** Create a Makefile to compile `assignment-sensor.c` into a binary with `gcc` and include a `clean` target.
**AI Response:** Suggested a simple Makefile with `-Wall -Wextra -O2` flags and targets for building and cleaning.
**Commit:** [commit-hash]

## 4. Systemd Unit File
**Prompt:** Create a systemd service unit file for `assignment-sensor` with specific configurations.
**AI Response:** Generated a `systemd/assignment-sensor.service` file with `Type=simple`, restart on failure, and default execution as root.
**Commit:** [commit-hash]

## 5. README Documentation
**Prompt:** Write a comprehensive README.md for the project, covering build, installation, configuration, testing, and uninstallation.
**AI Response:** Provided detailed sections for cloning, building, installing, configuring, testing, and uninstalling the service, along with fallback behavior and `/dev/urandom` rationale.
**Commit:** [commit-hash]
