/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:26:33 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/06 16:48:17 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Get token
 * 
 * @brief Return the token and set the start of next token
 * 
 * @param word The string that potentially has token hiding inside.
 * 			   Using double pointer here so that can set the pointer to the
 * 			   start of the next token.
 * @var token The token/lexemes. The category of the token is unknown.
 * @var copy The copy of the param word.
 * @var len The length of the span
 * 
 * Firstly, iterate through the word and check if there's any operator hiding
 * inside. If there is, meaning there are multiple token inside the word.
 * Stop the searching and get the span of the characters between the operator
 * & the starting character of the word. By using the span and strndup, get
 * the token exist before the operator.
 * Next, change the address of word to point to the starting character of
 * the next token. If it's a '\0' meaning the word has already tokenize all
 * the tokens hiding inside the word. If it's not a '\0' set the word point
 * to the operator character.
 */
char	*get_token(char **word)
{
	char	*token;
	char	*copy;
	int		len;

	copy = *word;
	while (*copy != '\0')
	{
		if (ft_strchr(OPERATORS, *copy) != NULL)
			break ;
		copy++;
	}
	len = copy - *word;
	token = ft_strndup(*word, len);
	if (*copy == '\0')
		*word = NULL;
	else
		*word = copy;
	return (token);
}

void	identify_token(char *token)
{
	recognize_cmd(token);
}

/**
 * Tokenizer - Identify the tokens/lexemes inside a words.
 * 
 * @param word Before this function executes, the commands has been
 * 			   pre-processed by the lexer (split the commands into words).
 * 			   The word here is the part of a command and there's potentially
 * 			   some tokens hiding somewhere in the words.
 * 
 * @brief Tokenizer will identify and tokenize the tokens hiding in the word and
 * store them into cmd_list (data structure to store the commands).
*/
void	tokenizer(char *word)
{
	char	*token;

	if (word == NULL)
		return ;
	token = get_token(&word); // need to recognize the token
	identify_token(token);
	free(token);
}
