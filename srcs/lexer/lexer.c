/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:02:40 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/20 19:31:36 by brook            ###   ########.fr       */
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
	char	**ori_words;

	words = ft_split_delims(cmds, "\"\'");
	ori_words = words;
	while (*words != NULL)
	{
		tokenizer(ms, *words);
		words++;
	}
	ft_freestrarr(ori_words);
}
