/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:02:40 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/07 15:30:49 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Lexer - Perform Lexical Analysis
*/
void	lexer(t_minishell *ms, char *cmds)
{
	char	**words;

	// Breaks the commands into smaller pieces
	words = ft_split_delims(cmds, "\"\'");
	while (*words != NULL)
	{
		// Identify the tokens into category
		// printf("Processing [%s]\n", *words);
		tokenizer(ms, *words);
		words++;
	}
}