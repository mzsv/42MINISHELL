# Minishell - a custom-built shell

## Table of Contents

1. [Overview](#overview)
3. [Features](#features)
4. [Implementation Details](#implementation-details)
5. [How to use](#how-to-use)
6. [Contributors](#contributors)
7. [Acknowledgments](#acknowledgments)

## Overview

**Minishell** is a custom-built shell that replicates essential functionalities of a Unix shell environment. This project serves as a minimalistic shell interpreter with core features to handle command execution, redirections, pipes, environment variable management, and built-in commands. The shell is designed to offer an interactive command-line interface with a focus on simplicity and efficiency.

## Features

- **Command Prompt**: Displays a prompt for user input when waiting for new commands.
- **Command History**: Maintains a history of previously executed commands.
- **Executable Search**: Searches for and executes commands based on the `PATH` variable or a provided relative/absolute path.
- **Signal Handling**: Utilizes a single global variable to handle signals, ensuring the signal handler does not access the main data structures.
- **Quoting**:
  - Handles single quotes (`'`) to prevent interpretation of meta-characters within quoted sequences.
  - Handles double quotes (`"`) to prevent interpretation of meta-characters, except for dollar signs (`$`).
- **Redirections**:
  - `<` redirects input.
  - `>` redirects output.
  - `<<` reads input until a delimiter line is encountered (does not update history).
  - `>>` appends output to an existing file.
- **Pipes**: Connects the output of one command to the input of the next command using pipes (`|`).
- **Environment Variables**:
  - Expands environment variables (`$`) to their values.
  - Expands `$?` to the exit status of the most recently executed foreground pipeline.
- **Signal Handling**:
  - `Ctrl-C` displays a new prompt on a new line.
  - `Ctrl-D` exits the shell.
  - `Ctrl-\` does nothing.
- **Built-in Commands**:
  - `echo -n`: Outputs text without a trailing newline.
  - `cd`: Changes the current directory (supports relative and absolute paths).
  - `pwd`: Prints the current working directory.
  - `export`: Sets environment variables (no options).
  - `unset`: Removes environment variables (no options).
  - `env`: Displays environment variables (no options or arguments).
  - `exit`: Exits the shell (no options).

## Implementation Details

- **Signal Handling**: Uses a single global variable to capture signal numbers, avoiding direct manipulation of main data structures within the signal handler.
- **Memory Management**: The `readline()` function, used for command input, may cause memory leaks, which are not fixed in this implementation. However, the shell’s own code is managed to avoid memory leaks.

## How to use

### Installation

1. **Clone the Repository**:
    ```bash
    git clone <repository-url>
    ```

2. **Compile the Project**:
    ```bash
    make
    ```

3. **Run the Shell**:
    ```bash
    ./minishell
    ```

### Usage

- **Command Execution**: Type commands at the prompt and press Enter.
- **Redirections**: Use `<`, `>`, `<<`, and `>>` to manage input and output redirections.
- **Pipes**: Connect commands using `|`.
- **Built-ins**: Utilize the implemented built-in commands for various shell functionalities.

## Contributors

- [Alexandru Mitcul](https://github.com/AlexMitcul)
- [Andre Silva](https://github.com/mzsv/)

## Acknowledgements

- The 42 School for providing the project specifications and environment.
