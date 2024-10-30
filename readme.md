# ShellX

An simple Unix shell implementation with job control, command history persistence, and pipeline support.

## Features

### Core Functionality
- Command execution with arguments
- Pipeline support for command chaining
- Job control (background/foreground processes)
- Command history with SQLite persistence
- Directory navigation
- Signal handling (SIGINT, SIGTSTP, SIGCHLD)

### Built-in Commands
- `cd [path]`: Change directory (supports `~` for home directory)
- `bg [job_id]`: Resume stopped job in background
- `fg [job_id]`: Bring background/stopped job to foreground
- `jobs`: List all background and stopped jobs
- `exit`: Exit the shell


## Prerequisites

- GCC compiler
- Make build system
- SQLite3 development libraries
- GNU Readline development libraries

## Installation

1. Install dependencies (Ubuntu/Debian):
```bash
sudo apt-get install gcc make libsqlite3-dev libreadline-dev
```

2. Clone the repository:
```bash
git clone https://github.com/yourusername/shellx.git
cd shellx
```

3. Build the project:
```bash
make
```

4. Run the shell:
```bash
./shell
```

## Project Structure

```
shellx/
├── Makefile
├── include/
│   ├── shell.h          # Core definitions and structures
│   ├── job_control.h    # Job control functionality
│   ├── command.h        # Command parsing and execution
│   ├── history.h        # Command history management
│   ├── builtins.h       # Built-in command handlers
│   └── signals.h        # Signal handling
├── src/
│   ├── main.c          # Shell entry point
│   ├── job_control.c   # Job management implementation
│   ├── command.c       # Command processing
│   ├── history.c       # History database operations
│   ├── builtins.c      # Built-in command implementation
│   └── signals.c       # Signal handlers
└── build/              # Compiled objects (created by Makefile)
```


## Usage Examples

1. Basic command execution:
```bash
[/home/user]🐚 ls -l
```

2. Pipeline commands:
```bash
[/home/user]🐚 cat file.txt | grep pattern | wc -l
```

3. Job control:
```bash
[/home/user]🐚 sleep 100
^Z
[/home/user]🐚 bg
[/home/user]🐚 fg
```
