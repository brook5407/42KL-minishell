/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:48:10 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/13 13:54:57 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ====== LIBRARIES ====== */
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include "../lib42/lib42.h"

/* ====== TEXT STYLING ====== */
# define GY "\033[1;30m"
# define BL "\033[5;34m"
# define YL "\033[1;33m"
# define GN "\033[1;32m"
# define DEF "\033[0m"

/* ====== MACROS ====== */
# define OPERATORS "<>|"
# define QUOTES "\"\'"
# define BUILTINS_TOTAL 7
# define OPERATORS_TOTAL 5
# define BUFFSIZE 256

/* ====== ENUMS ====== */

typedef enum e_token_type
{
	CMD,
	EXT_CMD,
	OPR,
	LIT
}		t_token_type;

typedef enum e_operators
{
	RDRIN,
	RDROUT,
	HEREDOC,
	APPEND,
	PIPE
}		t_operators;

/* ====== STRUCTS ====== */
typedef struct s_token
{
	t_token_type	type;
	void			*content;
}		t_token;

typedef struct s_env
{
	char	*key;
	char	*value;
}		t_env;

typedef struct s_minishell
{
	char	*prompt;
	char	**builtins;
	char	**operators;
	t_list	*envp;
}		t_minishell;

/* ====== FUNCTION PROTOTYPES ====== */

void	init_minishell(t_minishell *ms, char **ev);
void	init_environment(t_minishell *ms, char **ev);
void	init_signal(void);
void	add_env_var(t_minishell *ms, char *key, char *value);

void	lexer(t_minishell *ms, char *cmds);
void	tokenizer(t_minishell *ms, char *word);
void	recognize_token(t_minishell *ms, char *token);

int		token_in_quote(char *token);
char	*get_next_file(DIR *dir);
int		only_contain_operator(char *token);

char	*check_dangling_quote(char *cmds);

int		call_cd(t_minishell *ms, char *path);
int		call_pwd(t_minishell *ms);
int		call_env(t_minishell *ms);
int		call_unset(t_minishell *ms, char *key);
int		call_export(t_minishell *ms, char *key);
int		call_exit(t_minishell *ms, char *cmds);

t_env	*load_env_var(t_list *envp, char *var);
void	edit_env_val(t_list *envp, char *var, char *value);
char	*get_env_value(t_minishell *ms, char *key);

void	free_env_var(t_env *env_var);
void	free_env(t_list *envp);

#endif