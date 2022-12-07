/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:48:10 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/06 16:59:24 by wricky-t         ###   ########.fr       */
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
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include "../lib42/lib42.h"

/* ====== TEXT STYLING ====== */

/* ====== MACROS ====== */
# define OPERATORS "<>|="

/* ====== ENUMS ====== */

typedef enum e_token_type
{
	CMD,
	OPR,
	ID,
	VAL,
	LIT
}		t_token_type;

typedef enum e_operators
{
	DOLLAR,
	RDRIN,
	RDROUT,
	HEREDOC,
	APPEND,
	PIPE,
	ASSG,
	AND,
	OR,
	WILDCARD
}		t_operators;

/* ====== STRUCTS ====== */

typedef struct s_built_in {
	char	*name;
	char	*str;
}	t_built_in;

/* ====== FUNCTION PROTOTYPES ====== */

void	lexer(char *cmds);
void	tokenizer(char *word);
void	recognize_cmd(char *token);

#endif