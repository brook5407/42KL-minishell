/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:48:10 by wricky-t          #+#    #+#             */
/*   Updated: 2023/01/03 13:38:13 by wricky-t         ###   ########.fr       */
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

/**
 * Enum for token type
 * CMD		: Builtins command
 * EXT_CMD	: External program/command
 * OPR		: Operator
 * STR		: String literals
 * RDRIN	: Redirection in
 * RDROUT	: Redirection out
 * HEREDOC	: Heredoc
 * APPEND	: Redirection append
 * PIPE		: pipe
 */
typedef enum e_token_type
{
	CMD,
	EXT_CMD,
	STR,
	RDRIN,
	RDROUT,
	HEREDOC,
	APPEND,
	PIPE,
	TYPE_TOTAL,
	UNKNOWN
}		t_token_type;

typedef enum e_expand_type
{
	PARAM,
	INQUOTE,
	BOTH
}		t_expand_type;

/**
 * Enum for different types of grammar
 * START_GRAMMAR: Represent the acceptable tokens at the start of a grammar
 * FREE_FORM_GRAMMAR: Not restricted tokens. Any type is ok.
 * POST_PIPE_GRAMMAR: Represent the acceptable tokens after a pipe
 * POST_RDR_GRAMMAR: Represent the acceptable tokens after a redirection
 * CMD_ONLY_GRAMMAR: Only accepts CMD / EXT_CMD token.
 */
typedef enum e_grammar
{
	START,
	FREE_FORM,
	POST_RDR,
	CMD_ONLY,
	UNSET
}		t_grammar;

/**
 * Enum for error type, errno
 * The type are descriptive enough hehe
 */
typedef enum e_error_type
{
	SYNTAX_ERROR = 258,
	CMD_NOT_FOUND = 127,
	FILE_NOT_FOUND = 1,
	INVALID_ID = 1,
}		t_error_type;

/* ====== STRUCTS ====== */
/**
 * Struct for token
 * @param type	: Token type (Check t_token_type)
 * @param value	: Value of the token
 */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
}		t_token;

/**
 * Struct for environment variable
 * @param key	: ID
 * @param value	: value
 */
typedef struct s_env
{
	char	*key;
	char	*value;
}		t_env;
/**
 * Struct for minishell (main struct)
 * @param prompt	: Prompt message
 * @param builins	: Name of the builtins
 * @param operators : List of the operators
 * @param envp		: Environment variable linked list
 * @param tokens	: Token list
 * @param cmds		: Command list
 */
typedef struct s_minishell
{
	char	*prompt;
	char	**builtins;
	char	**operators;
	t_list	*envp;
	t_list	*tokens;
	t_list	*cmds;
}		t_minishell;

/**
 * Struct for file
 * @param rdr_type	: Redirection type (>, <, >>, <<)
 * @param name		: The name of the file
 */
typedef struct s_file
{
	t_token_type	rdr_type;
	char			*name;
}		t_file;

/**
 * Struct for command
 * @param cmd_path	: Path to command if it's an external program
 * @param args		: Arguments to run the command
 * @param infile	: List of t_file (infile)
 * @param outfile	: List of t_file (outfile)
 */
typedef struct s_cmd
{
	char	*cmd_name;
	t_list	*args;
	t_list	*infile;
	t_list	*outfile;
}		t_cmd;

typedef struct s_parser
{
	t_grammar		curr_grammar;
	t_token_type	rdr_mode;
	t_token_type	expected[TYPE_TOTAL];
	t_cmd			*cmd;
}		t_parser;

/* Global errno is defined here */
int8_t			g_errno;

/* ====== FUNCTION PROTOTYPES ====== */

void			init_minishell(t_minishell *ms, char **ev);
void			init_environment(t_minishell *ms, char **ev);
void			init_signal(void);
void			set_prompt(t_minishell *ms);
void			add_env_var(t_minishell *ms, char *key, char *value);

void			lexer(t_minishell *ms, char *cmds);
void			tokenizer(t_minishell *ms, char *word);
void			expander(t_minishell *ms, char **token, t_expand_type type);
void			recognize_token(t_minishell *ms, char *token);

int				is_valid_id(char *id);
char			*extract_ids(char **str, int ignore);
char			*get_parameter_value(t_minishell *ms, char *token);
char			*join_expanded(char *str, char *prefix, char *id);

int				token_in_quote(char *token);
char			*get_next_file(DIR *dir);
int				only_contain_operator(char *token);
t_token_type	get_operator_type(char *opr);
char			*get_ext_full_path(t_minishell *ms, char *token);

void			add_token(t_minishell *ms, t_token_type type, char *token);
void			list_all_token(void *content);
void			free_token(void *content);

void			parser(t_minishell *ms);
void			add_as_cmd_block(t_minishell *ms, t_parser *hlpr);
void			show_cmd_block(void *content);
void			free_cmd_block(void *content);

void			builder_helper(t_minishell *ms, t_parser *hlpr, t_token *token);

void			init_parser(t_parser *phlpr);
void			reset_all_type(t_parser *phlpr, int status);
void			reject_type(t_parser *phlpr, t_token_type type);
void			toggle_type(t_parser *phlpr, t_token_type type);
int				is_type_on(t_parser *phlpr, t_token_type type);

void			apply_grammar(t_parser *phlpr, t_grammar grammar);
void			set_next_grammar(t_parser *phlpr, t_token_type curr);

int				check_operator_syntax(t_minishell *ms, char *token);
void			check_incomplete_grammar(t_minishell *ms);

int				call_buildin(t_minishell *ms, char *cmds);
int				call_cd(t_minishell *ms, char *path);
int				call_pwd(t_minishell *ms);
int				call_env(t_minishell *ms);
int				call_unset(t_minishell *ms, char *key);
int				call_export(t_minishell *ms, char *key);
int				call_echo(t_minishell *ms, char *s);
int				call_exit(t_minishell *ms, char *cmds);
int				check_valid(char *cmds, char *args);

t_env			*load_env_var(t_list *envp, char *var);
void			edit_env_val(t_minishell *ms, char *key, char *value);
char			*get_env_value(t_minishell *ms, char *key);
char			**get_env_arry(t_minishell *ms);

char			**lst_to_array(t_list *lst);
int				executor(t_list *cmds, char **envp);

void			show_error(t_minishell *ms, t_error_type type, char *token);

void			free_env_var(t_env *env_var);
void			free_env(t_list *envp);

#endif