/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:02:40 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/03 20:24:42 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Lexer - Perform Lexical Analysis
*/
void	lexer(char *cmds)
{
	char	**words;

	// Breaks the commands into smaller pieces
	words = ft_split_ws(cmds);
	while (*words != NULL)
	{
		// Identify the tokens into category
		// get_token(): 
		printf("%s\n", *words);
		words++;
	}
	return ;
}
