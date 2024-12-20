# 42-minishell

Welcome to the 42-minishell project, part of the 42 Network Projects.Let's say the bigg project that i implemented in my cursus to this time 

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Commands](#commands)
- [Contributing](#contributing)

## Introduction

42-minishell is a simple shell implementation written in C. It is designed to provide the basic functionalities of a shell(mimic to Bash Shell), including executing commands, handling input/output redirection, and managing processes.

## Features

- Command execution and simple script shell
- I/O redirection
- Support for multi pipes
- Basic built-in commands (e.g., `cd`, `echo`, `exit`, `pwd`, `unset`, `export`, `env`)
- Signal handling (e.g, `ctrl-C`, `ctrl-\`, `ctrl-D (EOF)`)

## Installation

To install and run the minishell, follow these steps:

1. Clone the repository:
   ```sh
   git clone https://github.com/1MhDjant23/42-minishell.git

2. Enter to minishell directory:
  ```sh
  cd minishell
```
3. install readline:
  before entering to minishell dir, you see a bash script(install_readline.bash) you can use it to install readline faster.
  you can tak a look to it
```sh
  vim install_readline.bash
```

4. Now, after readline installed successfully, add the absolute path of the readline lib to Makfile:
  ```sh
  vim Makfile
```
  inside Makfile you can see ;"INRL = -I/Users/mait-taj/.brew/include/" and "LNRL= -lreadline -L/Users/mait-taj/.brew/lib/"
    replace "/Users/mait-taj/.brew/include/" by the path of your'e readline. That's all
    after this last step you can execute the minishell program and enjoy with owr minishell 😀😎
```sh
  make
```

## Commands
New i think you finish compliation of the program
so! you can test it by running any command, and test with multiple command line

## Contributing

Finally! this project developed by me (mait-taj) and  [@ysouhail](https://github.com/yssf).

`Executor(me)` -> [@mait-taj](https://github.com/1MhDjant23)

`Parser` -> [@ysouhail](https://github.com/yssf)  {great member, do a great work in it's part!}
