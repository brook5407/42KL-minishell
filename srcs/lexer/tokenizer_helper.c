/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:57:16 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/06 17:11:02 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>
/**
 * Recognize cmd
 * @brief Identify whether the token is a cmd
 * 
 * The priority will be like this:
 * 1. Check if the cmd is a minishell built-ins command
 * 2. Check if the cmd is a program and can be found on the system
 */
void	recognize_cmd(char *token)
{
	char		*token_copy;
	// Temporary start
	char		*builtins[8];

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "env";
	builtins[4] = "unset";
	builtins[5] = "export";
	builtins[6] = "exit";
	builtins[7] = NULL;
	// Temporary end
	int i = -1;
	token_copy = ft_strlower(ft_strdup(token));
	while (builtins[++i] != NULL)
	{
		if (strcmp(token_copy, builtins[i]) == 0)
			printf("[CMD]: %s\n", builtins[i]);
	}
	// when iterate through null, meaning it's not builtins, search
	// if it's a system program instead.
}
