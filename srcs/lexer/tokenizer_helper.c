/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:57:16 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/11 18:07:10 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_next_file(DIR *dir)
{
	struct dirent	*entity;

	while (1)
	{
		entity = readdir(dir);
		if (entity == NULL)
			break ;
		if (entity->d_type == DT_REG)
			return (entity->d_name);
	}
	return (NULL);
}

void	recognize_external(t_minishell *ms, char *token)
{
	char			*path;
	char			**paths;
	char			**temp_paths;
	DIR				*dir;
	struct dirent	*entity;

	path = get_env_value(ms, "PATH");
	paths = ft_split(path, ':');
	temp_paths = paths;
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
	ft_freestrarr(temp_paths);
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
	token_copy = ft_strdup(token);
	token_copy = ft_strlower(token_copy);
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
	free(token_copy);
}

/**
 * Operators are: | (Pipes), < (Redirect input), > (Redirect output),
 * 				  << (Heredoc) & >> (Append)
*/
// void	recognize_operator(t_minishell *ms, char *token)
// {
// 	int	i;

// 	i = -1;
// 	(void)ms;
// 	printf("token: %s\n", token);
// 	exit(0);
// 	while (token[++i] != '\0')
// 	{
// 		// printf("%c", token[i]);
// 	}
// 	// printf("i: %d\n", i);
// 	// must be the first character, because tokenizer stops at operator
// }
