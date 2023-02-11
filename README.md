<h1 align="center">
  🐚Minishell
</h1>

<p align="center">
	<b><i>As beautiful as a shell</i></b><br>
</p>

<p align="center">
	<img alt="GitHub repo size" src="https://img.shields.io/github/repo-size/brook5407/42KL-minishelll">
	<img alt="Lines of code" src="https://img.shields.io/tokei/lines/github/brook5407/42KL-minishelll">
	<img alt="GitHub language count" src="https://img.shields.io/github/languages/count/brook5407/42KL-minishelll">
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/brook5407/42KL-minishelll">
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/brook5407/42KL-minishelll">
</p>

<h3 align="center">
	<a href="#-about">About</a>
	<span> · </span>
  	<a href="#-content">Content</a>
	<span> · </span>
	<a href="#%EF%B8%8F-usage">Usage</a>
</h3>

## 💡 About

> _This project is about creating a simple shell. Yes, your own little bash. You will learn a lot about processes and file descriptors.._

## 🚀 Content

### 🚩 Mandatory part

Write a shell

• Display a prompt when waiting for a new command.
• Have a working history.
• Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
• Not use more than one global variable. Think about it. You will have to explain its purpose.
• Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
• Handle ’ (single quote) which should prevent the shell from interpreting the meta- characters in the quoted sequence.
• Handle " (double quote) which should prevent the shell from interpreting the meta- characters in the quoted sequence except for $ (dollar sign).
• Implement redirections:
◦ < should redirect input.
◦ > should redirect output.
◦ << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
◦ >> should redirect output in append mode.
• Implement pipes (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.
• Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
• Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
• In interactive mode:
◦ ctrl-C displays a new prompt on a new line. ◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.
• Your shell must implement the following builtins:
◦ echo with option -n
◦ cd with only a relative or absolute path ◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options

| Program name     | minishell                                                                                                                                                                                      |
| :--------------- | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Turn in files    | Makefile, *.h, *.c                                                                                                                                                                                       |
| Makefile         | NAME, all, clean, fclean, re                                                                                                                                                                                       |
| Arguments        | 
| External functs. | readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
| Libft authorized | No                                                                                                                                                                                          
| Description      | philosopher with threads and mutex                                                                                                                                                           |

## 🛠️ Usage

### Requirements

The function is written in C language and thus needs the **`gcc` compiler** and some standard **C libraries** to run.

### Instructions

**1. Compiling the program**

To compile, go to the program path and run:

```shell
$ make
```
**2. Executing the program**

To execute the program, run:

```C
$ ./minishell
```
***Makefile rules***

- `make` -- compiles philo.
- `make clean` -- deletes object files.
- `make fclean` -- deletes object files and philo.
- `make re` -- `fclean` + `make`.
- `make norm` -- check norminette
