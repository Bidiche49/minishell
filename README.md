
---

# minishell

## Description

`minishell` is a simple Unix shell implementation written in C. This project aims to recreate the basic functionality of a shell, allowing users to execute commands, manage processes, and handle input/output redirection. The `minishell` project serves as a practical exercise in understanding system calls, process management, and command parsing.

## Features

- **Command Execution**: Executes user-defined commands and built-in shell commands.
- **Process Management**: Supports running processes in the foreground and background.
- **Input/Output Redirection**: Handles input and output redirection using `<`, `>`, and `|` operators.
- **Environment Variables**: Allows users to access and modify environment variables.

## Key Technologies

- **C Programming Language**: The primary language used for implementing the shell.
- **System Calls**: Utilizes various system calls such as `fork`, `execve`, and `wait` for process management.
- **Signal Handling**: Manages signals for proper shell behavior (e.g., handling `CTRL+C`).

## Learning Outcomes

- Gained a deeper understanding of how shells operate and interact with the operating system.
- Developed skills in parsing command-line input and managing processes.
- Learned to handle input/output redirection and environment variables.

## How to Use

1. Clone the repository:
   ```bash
   git clone https://github.com/Bidiche49/minishell
   cd minishell
   ```
2. Compile the project:
   ```bash
   make
   ```
3. Run the shell:
   ```bash
   ./minishell
   ```

## Example Usage

To run a command in the shell:
```bash
minishell$ ls -la
```

To set an environment variable:
```bash
minishell$ export MY_VAR=value
```

To execute a command with output redirection:
```bash
minishell$ echo "Hello, World!" > output.txt
```

## Compilation

To compile the project:
```bash
make
```

---
