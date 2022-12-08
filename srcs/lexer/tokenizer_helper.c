/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:57:16 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/07 22:07:38 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	recognize_external(t_minishell *ms, char *token)
{
	char			*path;
	char			**paths;
	DIR				*dir;
	struct dirent	*entity;

	path = getenv("PATH");
	paths = ft_split(path, ':');
	while (*paths != NULL)
	{
		dir = opendir(*paths);
		if (dir == NULL)
			continue ;
		while (1)
		{
			entity = readdir(dir);
			if (entity == NULL)
				break ;
			if (entity->d_type == DT_REG && !ft_strcmp(token, entity->d_name))
				printf("[EXT_CMD]: %s\n", entity->d_name);
		}
		paths++;
	}
	(void)ms;
}

/**
 * Recognize cmd
 * @brief Identify whether the token is a cmd
 * 
 * The priority will be like this:
 * 1. Check if the cmd is a minishell built-ins command
 * 2. Check if the cmd is a program and can be found on the system
 */
void	recognize_cmd(t_minishell *ms, char *token)
{
	char	*token_copy;
	char	**builtins;

	builtins = ms->builtins;
	token_copy = ft_strlower(ft_strdup(token));
	while (*builtins != NULL)
	{
		if (ft_strcmp(*builtins, token_copy) == 0)
			break ;
		builtins++;
	}
	if (*builtins == NULL)
		recognize_external(ms, token_copy);
	else
		printf("[CMD]: %s\n", *builtins);
}

// void	recognize_operator(t_minishell *ms, char *operator)
// {}
