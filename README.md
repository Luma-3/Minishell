![Minishell](https://github.com/user-attachments/assets/bc9d3626-f764-40b8-ac2c-9750540e6f1b)
<h1 align="center">
	42 Project - Minishell
</h1>

<p align="center">
	<b><i> As beautiful as a shell !</i></b>
</p>

<p align="center">
	<img src="https://github.com/luma-3/Minishell/blob/main/img/minishellm.png" alt="mimishell_logo" />
</p>

---
<p align="center">
	<img src="https://img.shields.io/badge/Score-125-blue?style=flat-square&logo=42" alt="Score project :125"/>
	<img alt="Static Badge" src="https://img.shields.io/badge/Outstanding-3-blue?style=flat-square&logo=42">
	<img alt="GitHub repo size" src="https://img.shields.io/github/repo-size/Luma-3/Minishell?style=flat-square&logo=github">
</p>




## Overview

This project serves an educational purpose and is based on the **common core of 42 School**. Therefore, it is subject to educational restrictions. Please be aware of these restrictions before making any contributions.

Please note that due to the private nature of the subject, it cannot be publicly shared on this GitHub repository.

### Team project

This project is a collaborative effort between two students:

[jbrousse](https://profile.intra.42.fr/users/jbrousse)
[antgabri](https://profile.intra.42.fr/users/antgabri)


## 📄 Features

### Mandatory Features
- Display a prompt and maintain history in interactive mode
- Execute commands using:
  - PATH resolution or absolute/relative paths
- Input/output redirection:
  - `<` (input)
  - `>` (output overwrite)
  - `>>` (output append)
  - `<<` here-doc (reading until delimiter)
- Pipelines using `|`
- Environment variable expansion: `$VAR`, `$?`
- Signal handling for Ctrl-C (interrupt), Ctrl-D (EOF), Ctrl-\ (SIGQUIT)
- Built-in commands:
  - `echo` (supports `-n`)
  - `cd` (relative/absolute paths)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

### Bonus Features
- Logical operators `&&` and `||`, with parentheses to define execution order
- Wildcard (`*`) expansion in the current working directory

## Requirements
- Written in C, following the [42 School Norm]
- No memory leaks or crashes permitted
- Code must compile without warnings or errors (`-Wall -Wextra -Werror` flags)
- One global variable allowed (for signal tracking only)
- Use of `libft` is allowed if included and compiled properly
- Essential Makefile targets:
  - `all`, `clean`, `fclean`, `re`, `bonus` (for optional features)

## 📥 Installation

Installation and compilation commands :

```
git clone --recursive https://github.com/Luma-3/Minishell.git
cd Minishell
make
```


## 🦆 Usage

For launch Kikishell :
```
./minishell
```

Launch Shell :
<p align="center">
	<img src="https://github.com/Luma-3/Minishell/blob/main/img/Screenshot%20from%202024-04-24%2017-51-33.png" alt="launch shell"/>
</p>

Execute Command :
<p align="center">
	<img src="https://github.com/Luma-3/Minishell/blob/main/img/Screenshot%20from%202024-04-24%2017-52-28.png" alt="CMD exec"/>
</p>

Exit Shell :
<p align="center">
	<img src="https://github.com/Luma-3/Minishell/blob/main/img/Screenshot%20from%202024-04-24%2017-50-21.png" alt="exit shell"/>
</p>


This work is published under the terms of **[42 Unlicense](https://github.com/gcamerli/42unlicense)**.

