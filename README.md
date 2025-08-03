# c-json-cli-tasker
Task Runner Tool (CLI Project in C)
A C-based CLI utility to automate and execute custom tasks defined in a JSON file using shell commands. Supports --list, --help, --version, and direct task execution. Features colored terminal output (info, success, error), formatted logs, and clear usage hints. Built to learn C, JSON parsing, memory handling, and shell execution,easily extendable.
A colorful and lightweight Command Line Interface (CLI) tool written in C that reads a task.json file and runs shell commands defined as tasks. Built with file handling, JSON parsing using cJSON, and system call execution in mind, this project is ideal for automating developer workflows and understanding CLI app architecture.

This tool supports task dependencies, colored output logs, command validation, and helpful flags. Just define your tasks once in JSON format and run them effortlessly from the terminal.

🔹 Supports commands like `--list`, `--help`, `--version`
- 🔹 Direct shell task execution from JSON configuration
- 🔹 Colored terminal output for info, success, error
- 🔹 Formatted logs and clear usage hints
- 🔹 Built to explore:
  - ✅ JSON parsing in C
  - ✅ Shell command execution
  - ✅ Memory handling
  - ✅ Modular C development

How to compile: make sure tasker.c (your main file) and cJSON.c (from the cJSON library) are in the same folder, then compile using
gcc tasker.c cJSON.c -o tasker_runner.exe

If cJSON.h is missing, install the cJSON library and place the headers correctly.

Usage:
Run a task:
./tasker_runner.exe <task_name>

List all available tasks:
./tasker_runner.exe --list

Show help:
./tasker_runner.exe --help

About/version info:
./tasker_runner.exe --version

If no arguments are provided, the tool prints a friendly intro message with usage hints.

The terminal output uses ANSI escape codes to differentiate logs:
Yellow → Info & usage instructions
Green → Success logs & confirmations
Red → Errors & alerts
Pink → Task names & structure
Bright Blue → Executed commands

Colors are reset after each message to avoid terminal bleed.

Made by Ritika Bhasin as a personal project to learn CLI tools, JSON parsing, memory handling, and shell execution using pure C.

MIT License – Free to use, modify, and distribute.
