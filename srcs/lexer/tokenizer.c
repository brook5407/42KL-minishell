/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:57:16 by wricky-t          #+#    #+#             */
/*   Updated: 2023/02/03 20:16:04 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Recognize cmd
 * @brief Identify whether the token is a cmd
 * 
 * The priority will be like this:
 * 1. Check if the cmd is a minishell built-ins command
 * 2. Check if the cmd is a program and can be found on the system
 * 
 * 1. Check if the token is inside a set of quote. If yes, when strdup, don't
 *    duplicate the quotes. If no, do normal strdup.
 * 2. To make minishell to accept uppercase command, we need to convert it
 *    into lowercase first. Then use the lowercase version to check if it's a
 *    built-in or external command.
 * 3. To check if it's a builtin, strcmp with each of the builtins command name
 *    in the list. If yes, add to data structure.
 * TODO: Memory handling here is not clean
 */
int	recognize_cmd(t_minishell *ms, char *token)
{
	int		i;
	char	*token_copy;
	char	*ext_path;

	i = -1;
	token_copy = ft_strlower(ft_strdup(token));
	while (ms->builtins[++i] != NULL)
	{
		if (ft_strcmp(ms->builtins[i], token_copy) == 0)
		{
			add_token(ms, CMD, ft_strdup(token));
			free(token_copy);
			return (1);
		}
	}
	ext_path = get_ext_full_path(ms, token_copy);
	if (ext_path != NULL)
	{
		add_token(ms, EXT_CMD, ft_strdup(token));
		free(ext_path);
		free(token_copy);
		return (1);
	}
	free(token_copy);
	return (0);
}

/**
 * Operators are: | (Pipes), < (Redirect input), > (Redirect output),
 * 				  << (Heredoc) & >> (Append)
 * 
 * 1. Check if the length is greater and equal to 1 and less and equal to 2
*/
int	recognize_operator(t_minishell *ms, char *token)
{
	int				i;
	int				len;
	t_token_type	type;

	i = -1;
	len = ft_strlen(token);
	if (!(len >= 1 && len <= 2))
		return (0);
	while (ms->operators[++i] != NULL)
	{
		if (ft_strcmp(token, ms->operators[i]) == 0)
		{
			type = get_operator_type(ms->operators[i]);
			add_token(ms, type, ft_strdup(token));
			return (1);
		}
	}
	return (0);
}

void	recognize_token(t_minishell *ms, char *token)
{
	char	*ori_token;

	ori_token = token;
	expander(ms, &token, INQUOTE);
	if (recognize_cmd(ms, token) == 0)
	{
		if (recognize_operator(ms, token) == 0)
		{
			add_token(ms, STR, ft_strdup(token));
		}
	}
	if (ori_token != token)
		free(ori_token);
}
