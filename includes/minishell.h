/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:48:10 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/07 10:58:32 by chchin           ###   ########.fr       */
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


#define BUFFSIZE 256

/* ====== TEXT STYLING ====== */

/* ====== MACROS ====== */

/* ====== ENUMS ====== */

typedef enum e_token_type
{
	CMD,
	OPR,
	ID,
	LIT
}		t_token_type;

/* ====== STRUCTS ====== */

/* ====== FUNCTION PROTOTYPES ====== */

void	lexer(char *cmds);
int 	call_cd(char *argv);
int 	call_pwd(char *args);
int 	call_env(char **envp);

#endif