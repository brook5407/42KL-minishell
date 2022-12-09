/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dangling_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:16:36 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/09 19:49:34 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Get the dangling quote
 * 
 * Iterate through the string and look for QUOTES (" & '). If there's, check for
 * another one to ensure that the found quote is enclosed. If there's, ignore the
 * characters in between the found quotes and increment the pointer to (2nd found
 * quote + 1). After that, iterate the string from there and look for another
 * dangling quote. If the second quote is not found, return the starting quote.
 * The caller should use the return value to ask user for the closing quote.
*/
static char	get_dangling_quote(char *cmds)
{
	char	*start_quote;
	char	*end_quote;

	while (*cmds != '\0')
	{
		start_quote = ft_strchr(QUOTES, *cmds);
		if (start_quote != NULL)
		{
			end_quote = ft_strchr(cmds + 1, *cmds);
			if (end_quote != NULL)
				cmds = end_quote + 1;
			else if (end_quote == NULL)
				return (*start_quote);
		}
		if (*cmds == '\0')
			break ;
		cmds++;
	}
	return (0);
}

char	*check_dangling_quote(char *cmds)
{
	char	dang_quote;
	char	*enclosed;
	char	*line;

	dang_quote = get_dangling_quote(cmds);
	cmds = ft_strjoin_free(cmds, "\n");
	if (dang_quote == 0)
		return (cmds);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		enclosed = ft_strchr(line, dang_quote);
		cmds = ft_strjoin_free(cmds, line);
		if (enclosed != NULL)
			break ;
		cmds = ft_strjoin_free(cmds, "\n");
	}
	return (cmds);
}
