# Simple Shell Project

This is a simple shell project, which is a command-line interpreter that allows users to execute commands by typing them manually in the terminal. The project is written in C programming language and was developed by Houssam Mrabet and Mahmoud Khairi as a group project for ALX SE.

## Authors profiles

- Houssam Mrabet:
    [GitHub](https://github.com/HoussamMrabet) 👨‍💻 | [LinkedIn](https://www.linkedin.com/in/houssam-mrabet-6b758a176/) 👨‍💻
- Mahmoud Khairi:
    [GitHub](https://github.com/Mahmoud-Khairi) 👨‍💻 | [LinkedIn](https://www.linkedin.com/in/mahmoud-khairi-39942124a/) 👨‍💻

## How to Run the Simple Shell

To run the simple shell, follow these steps:

1. Clone the repository using the following command:
```
git clone https://github.com/<username>/simple_shell.git
```

2. Compile the program using the following command:
```
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```

3. Run the program using the following command:
```
./hsh
```

Once the program is running, you can type commands and the shell will execute them. You can exit the shell by typing `exit` or pressing `ctrl + d`.

## Features of the Simple Shell

The simple shell supports the following features:

- Executing commands with arguments
- Handling multiple commands separated by `;`
- Handling input and output redirection with `<` and `>`
- Handling pipes with `|`
- Running commands in the background with `&`

## Files in the Repository

- `README.md`: This file, which provides information about the simple shell project.
- `hsh.h`: Header file containing function prototypes and structure definitions.
- `main.c`: Main function of the simple shell.
- `builtins.c`: Contains functions that implement built-in shell commands.
- `exec.c`: Contains functions that execute non-built-in commands.
- `helper_functions.c`: Contains helper functions used by other files.
- `memory_functions.c`: Contains functions that allocate and free memory.
- `parser.c`: Contains functions that parse input into commands and arguments.
- `signal_functions.c`: Contains functions that handle signals.

## Resources

- [Everything you need to know to start coding your own shell](https://intranet.alxswe.com/concepts/64)
- [The Gates of Shell](https://www.gnu.org/software/bash/manual/html_node/Unix-Shells.html)
- [How to write a simple shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [A Unix Shell Programming Overview](https://www.tldp.org/LDP/abs/html/)
- [Linux man pages](https://man7.org/linux/man-pages/index.html)
