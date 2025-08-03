# c-json-cli-tasker
Task Runner Tool (CLI Project in C)
<br>
A C-based CLI utility to automate and execute custom tasks defined in a JSON file using shell commands. Supports --list, --help, --version, and direct task execution. Features colored terminal output (info, success, error), formatted logs, and clear usage hints. Built to learn C, JSON parsing, memory handling, and shell execution,easily extendable.
<br>
A colorful and lightweight Command Line Interface (CLI) tool written in C that reads a task.json file and runs shell commands defined as tasks. Built with file handling, JSON parsing using cJSON, and system call execution in mind, this project is ideal for automating developer workflows and understanding CLI app architecture.
<br>
This tool supports task dependencies, colored output logs, command validation, and helpful flags. Just define your tasks once in JSON format and run them effortlessly from the terminal.
<br>
🔹 Supports commands like `--list`, `--help`, `--version`
- 🔹 Direct shell task execution from JSON configuration
- 🔹 Colored terminal output for info, success, error
- 🔹 Formatted logs and clear usage hints
- 🔹 Built to explore:
  - ✅ JSON parsing in C
  - ✅ Shell command execution
  - ✅ Memory handling
  - ✅ Modular C development
<br>
How to compile: make sure tasker.c (your main file) and cJSON.c (from the cJSON library) are in the same folder, then compile using
<br>
gcc tasker.c cJSON.c -o tasker_runner.exe
<br>
If cJSON.h is missing, install the cJSON library and place the headers correctly.
<br>
Usage:
Run a task:
<br>
./tasker_runner.exe <task_name>
<br>
List all available tasks:
<br>
./tasker_runner.exe --list
<br>
Show help:
<br>
./tasker_runner.exe --help
<br>
About/version info:
<br>
./tasker_runner.exe --version
<br>
If no arguments are provided, the tool prints a friendly intro message with usage hints.
<br>
The terminal output uses ANSI escape codes to differentiate logs:
<br>
Yellow → Info & usage instructions
<br>
Green → Success logs & confirmations
<br>
Red → Errors & alerts
<br>
Pink → Task names & structure
<br>
Bright Blue → Executed commands
<br>
Colors are reset after each message to avoid terminal bleed.
<br>
Made by Ritika Bhasin as a personal project to learn CLI tools, JSON parsing, memory handling, and shell execution using pure C.
<br>
MIT License – Free to use, modify, and distribute.
