# **Simple Shell**

## 📝 Description
Simple Shell is a UNIX command line interpreter written in **C**. This project replicates the basic behavior of a standard Linux shell, including executing commands, handling the `PATH` environment variable, and supporting simple built-in commands.

The shell uses low-level system calls like `fork`, `execve`, `waitpid`, and `access` to create and manage processes.

---

## 🎯 Learning Objectives
* Understand how a shell works internally.
* Learn how processes are created using `fork`.
* Execute programs using `execve`.
* Manage parent and child processes using `waitpid`.
* Handle environment variables and memory management.
* Implement basic command parsing.

---

## ✨ Features
* **Interactive Mode:** Displays a prompt (`newshell$ `) and waits for user input.
* **Non-Interactive Mode:** Can receive commands via pipes (e.g., `echo "ls" | ./simple_shell`).
* **Command Arguments:** Executes commands with multiple arguments.
* **PATH Handling:** Automatically searches for executables in the system PATH.
* **Built-in Commands:** Supports `exit` and `env`.
* **Safe Execution:** Does **not** call `fork` if the command is not found.
* **EOF Handling:** Gracefully exits on `Ctrl+D`.

---

## 💡Requirements

- Ubuntu 20.04 LTS
- GCC compiler
- Betty style compliant
- Allowed system calls and functions:
  - `fork`
  - `execve`
  - `wait`
  - `waitpid`
  - `access`
  - `getline`
  - `strtok`
  - `malloc`
  - `free`
  - `perror`

---

## 🔹Compilation

To compile the shell, run:

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o simple_shell
```

## 🚀Usage

**Interactive Mode**
```bash
$ ./simple_shell
newshell$ ls
file1.c file2.c
newshell$ /bin/ls
file1.c file2.c
newshell$ env
PATH=/usr/local/bin:/usr/bin:/bin
newshell$ exit
$
```

**Non-Interactive Mode**
```bash
echo "/bin/ls" | ./simple_shell
file1.c file2.c
```

## 📂 File Structure
 - **`shell.c`**       - Main loop and input handling
 - **`execute.c`**     - Command execution logic
 - **`path.c`**        - PATH searching logic
 - **`tokenize.c`**    - Command parsing
 - **`builtins.c`**    - Built-in commands (exit, env)
 - **`shell.h`**       - Header file and function prototypes

---

## ⚠️ Error Handling
* Error Handling

* Displays error message if command is not found

* Handles fork and execve failures

* Handles End Of File (Ctrl+D)

* Prevents fork from being called if command does not exist

## 👨‍💻 Authors

* **Aysu Mustafazade** - AysuMustafazade
* **Salim Haciyev** - hajieew