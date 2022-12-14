/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognizer_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:11:31 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/14 14:21:05 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Check if a token is in a set of quote
 * 
 * Return 1 if yes, 0 otherwise.
 * 
 * The reason to check this is because to make minishell to accept command
 * that is wrapped inside a set of quote like:
 * "echo" - Valid command (echo)
 * "EcHo" - Valid command (echo)
 * 'ECHo' - Valid command (echo)
 * "/bin/cat" - Valid external command (cat)
*/
int	token_in_quote(char *token)
{
	char	*quote;

	quote = ft_strchr(QUOTES, *token);
	if (quote == NULL)
		return (0);
	if (*(token + (ft_strlen(token) - 1)) == *quote)
		return (1);
	return (0);
}

int	only_contain_operator(char *token)
{
	while (*token != '\0')
	{
		if (ft_strchr(OPERATORS, *token) == NULL)
			return (0);
		token++;
	}
	return (1);
}
