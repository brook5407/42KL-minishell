/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:02:40 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/09 14:14:05 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Lexer - Perform Lexical Analysis
 * 
 * 1. Breaks the command into small pieces (words)
 * 2. Tokenize the words to identify their category
 * 3. Parse the command list to check if the grammar is correct
*/
void	lexer(t_minishell *ms, char *cmds)
{
	char	**words;

	words = ft_split_delims(cmds, "\"\'");
	while (*words != NULL)
	{
		ft_printf("processing: %s\n", *words);
		tokenizer(ms, *words);
		ft_printf("\n");
		words++;
	}
}
