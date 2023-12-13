# 0x16. C - Simple Shell

The Simple Shell is a basic  basic command-line interface or shell program that provides a minimal set of features for interacting with an operating system.
shell program is designed to work in both interactive and non-interactive modes. It offers error handling similar to the _(/bin/sh)_ command, with the only distinction being that the program name is equivalent to _argv[0]_ **(hsh)**.

## List of allowed functions and system calls

* access (man 2 access)

* chdir (man 2 chdir)

* close (man 2 close)

* closedir (man 3 closedir)

* execve (man 2 execve)

* exit (man 3 exit)

* _exit (man 2 _exit)

* fflush (man 3 fflush)

* fork (man 2 fork)

* free (man 3 free)

* getcwd (man 3 getcwd)

* getline (man 3 getline)

* isatty (man 3 isatty)

* kill (man 2 kill)

* malloc (man 3 malloc)

* open (man 2 open)

* opendir (man 3 opendir)

* perror (man 3 perror)

* read (man 2 read)

* readdir (man 3 readdir)

* signal (man 2 signal)

* stat (__xstat) (man 2 stat)

* lstat (__lxstat) (man 2 lstat)

* fstat (__fxstat) (man 2 fstat)

* strtok (man 3 strtok)

* wait (man 2 wait)

* waitpid (man 2 waitpid)

* wait3 (man 2 wait3)

* wait4 (man 2 wait4)

* write (man 2 write)

### Getting Started

Create a repo called simple_shell
After you clone this repository and compile the program with the command above, you will generate a file called hsh that can be executed by entering ./hsh in your shell.
Compilation

GCC command to compile: gcc -Wall -Werror -Wextra -pedantic *.c -o hsh

#### Testing

This wil compile all the '.c' files and change the output's name to 'hsh'.

($)

hsh main.c shell.c

The output after the program is executed should look something like this:

> $ ./hsh
> ($)
> /bin/ls
> hsh main.c shell.c
> ($)
> ($) exit
> $

## Interactive Mode (Version 0.0.0)

* Display a prompt **($)** and await user input for a command. Each command line should terminate with a new line.

* The prompt should reappear after executing each command.

* Command lines are simple and do not involve semicolons, pipes, redirections, or advanced features.

* Commands consist of only one word, and no arguments are passed to programs.

* If an executable cannot be found, an error message is displayed, and the prompt reappears.

* Proper error handling is implemented.

* The 'end-of-file' condition **_(Ctrl+D)_** is handled.

## Interactive Mode (Version 0.1.0)

* Handle command lines with arguments. **Implement PATH handling**
* Avoid calling fork if the command does not exist

**Interactive Mode (Version 0.1.1)**

* Implement the env built-in command to print the current environment.

**Interactive Mode (Version 0.2.0)**

* Develop a custom getline function (since getline is not allowed).

**Interactive Mode (Version 0.2.1)**

* Create a custom strtok function (as strtok is not permitted).

**Interactive Mode (Version 0.3.1)**

* Handle arguments for the built-in exit command. Usage: exit status, where status is an integer used for shell exit.

**InteractIive Mode (Version 1.0.0)**

* Implement the setenv and unsetenv built-in commands. setenv initializes a new environment variable, or modify an existing one and should print something on stderr on failure (**Comm and syntax**: setenv VARIABLE VALUE). unsetenv remove an environment variable and should print something on stderr on failure **(Command syntax: unsetenv VARIABLE)**.

* Implement the built-in command cd (Command syntax: _cd DIRECTORY_). cd changes the current directory of the process. If no argument is given to cd, the command must be interpreted like cd $HOME and handle te command cd -. Remember to update the environment variable PWD when you change directory

* Handle the commands separator ;

* Handle the && and || shell logical operators.

* Implement the alias built-in command Usage: alias [name[='value'] .... alias prints a list of all aliases, one per line, in the form name='value'. alias name [name2 ...] prints the aliases name, name2, etc, 1 per line in the form name='value' and alias name='value' [...] defines an alias for each name whose value is given. If name is already an alias,

* replaces its value with value.

* Handle variables replacement

* Handle the **$?** variable

* Handle the **$$** variable

* Account for comments **(#)**

**Non-Interactive Mode (Version 1.0.0)**

Example

> $ echo "echo 'hello' #this will be ignored!" | ./hsh
> 'hello'

* In non-interactive mode, the Simple Shell accepts a file as a command line argument. To use this mode, execute: • Your shell can take a file as a command line argument (Usage: simple_shell _[filename]_)

* The file contains all the commands that your shell should run before exiting

* The file should contain one command per line

* In this mode the shell should not print a prompt and should not read from stdin


#### Command Execution 👍
After receiving a command, shellex tokenizes it into words using > " " as a delimiter.
The first word is considered the command and all remaining words are considered arguments to that command.
shell then proceeds with the following actions:

1. If the first character of the command is neither a slash (\) nor
dot (.), the shell searches for it in the list of shell builtins.
If there exists a builtin by that name, the builtin is invoked.

2. If the first character of the command is none of a slash (\), dot
(.), nor builtin, **shell** searches each element of the **PATH**
environmental variable for a directory containing an executable file by that name.

3. If the first character of the command is a slash (\) or dot (.)
or either of the above searches was successful, the shell executes the named program with any remaining given arguments in a separate execution environment.

## Author

* Chiamaka Emeti || **[Github](https://www.github.com/chiamablessing)** | [Twitter](https://www.twitter.com/Icehub_techster) | [email](https://www.gmail.com/chiamakaemeti)

## Acknowledgements 🙏

This project was written as part of the curriculum of the ALX-SE programme by Holberton School. Holberton School is a campus-based full-stack software engineering program that prepares students for careers in the tech industry using project-based peer learning.
 For more information about ALX, visit this *[link](https://www.alxafrica.com)*
