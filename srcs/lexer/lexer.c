/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:02:40 by wricky-t          #+#    #+#             */
/*   Updated: 2023/02/04 18:55:45 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Get string literal token, not neccessary means it's a string literal.
 * @brief This function is to extract token that is wrapped with quotes
 *        and treat them as a token.
 * 
 * This function will be called if the get_token function detects a quote.
 * If that's the case, meaning the starting character of the word must be
 * a quote. Hence, locate the closing quote, to mark the end of the token.
 * The next token will start at the closing quote + 1.
 * 
 * But, here's a twist, that's not actual the end of a token if the
 * following character is not an operator. So it's the case like this:
 * 
 * echo "Hello World"echo
 * tokens: [echo], ["Hello World"echo]
 * 
 * Hence, if the characters after the closing quote is not an operator,
 * the pointer to the end of the token keep incrementing until it hits
 * either a '\0' or an operator.
*/
char	*get_str_token(char **word)
{
	char	quote;
	char	*token;
	char	*next;

	quote = *(*word);
	next = ft_strchr(*word + 1, quote);
	if (next == NULL)
		next = *word + ft_strlen(*word) - 1;
	next++;
	while (*next != '\0')
	{
		if (ft_strchr(OPERATORS, *next) != NULL)
			break ;
		next++;
	}
	token = ft_strndup(*word, next - *word);
	*word = next;
	return (token);
}

/**
 * Get the operator token. The validity of the operator token is not
 * determined yet.
 * @brief This function is to extract the operator out from the word
 * 
 * This function will be called when detects an operator. Which means the
 * first character must be an operator. As long as the following character
 * is an operator, which ever it is, increment the pointer.
 * When hit a non-operator character, this marks the start of the next token.
 * Point the pointer to next token to that character. Return the operator
 * afterward.
*/
char	*get_operator_token(char **word)
{
	char	*token;
	char	*next;
	int		is_pipe;
	char	opr;

	next = *word;
	is_pipe = (*next == '|');
	opr = *(next++);
	if (*next == opr && is_pipe == 0)
		next++;
	token = ft_strndup(*word, next - *word);
	*word = next;
	return (token);
}

/**
 *  * Get token
 * 
 * @brief Return the token and set the start of next token
 * 
 * @param word The string that potentially has token hiding inside.
 * 			   Using double pointer here so that can set the pointer to the
 * 			   start of the next token.
 * 
 * This function should be called in a while loop. The while loop condition
 * should check if the word has reach the '\0' or not.
 * 
 * What determines/delimit the start & end of a token.
 * - What's in between "" or '' is a token.
 * - When detects a operator, what's infront of that operator is a token
 * - A series of operator is a token
 * - When reach '\0', what's before it, will be treated as a token no
 *   matter what. And the pointer to next token should be pointing to
 *   '\0'.
 * 
 * The word that's been pass in will not have a space anymore, except if
 * the word is something like: "Hello World", then it's possible. But
 * this will be treated as a token anyway.
 * 
 * The start of the next token should be the end of the previous token + 1
 * 
 * Example:
 * "Hello World" - ["Hello World"]
 * "Hello"&&echo - ["Hello"], [&&], [echo]
 * hello|echo - [hello], [|], [echo]
 * '"hello"' - ['"hello"']
 * "'Hello"' - ["'Hello"], [']
 * 'echo "Hello"' - ['echo "Hello"']
*/
char	*get_token(char **word)
{
	char	*token;
	char	*next;

	next = *word;
	if (ft_strchr(OPERATORS, *next) != NULL)
		return (get_operator_token(word));
	else if (ft_strchr(QUOTES, *next) != NULL)
		return (get_str_token(word));
	while (*next != '\0')
	{
		if (ft_strchr(OPERATORS, *next) != NULL)
			break ;
		next++;
	}
	token = ft_strndup(*word, next - *word);
	*word = next;
	return (token);
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
 * 		  store them into cmd_list (data structure to store the commands).
*/
void	tokenizer(t_minishell *ms, char *word)
{
	char	*token;
	char	*start;
	char	*str;
	char	**words;

	if (word == NULL)
		return ;
	words = ft_split_delims(word, "\"\'");
	while (*words != NULL)
	{
		start = *words;
		str = *words;
		while (*str != '\0')
		{
			token = get_token(&str);
			recognize_token(ms, token);
		}
		if (start == str)
			add_token(ms, STR, ft_strdup(str));
		words++;
	}
}

/**
 * Lexer - Perform Lexical Analysis
 * 
 * 1. Breaks the command into small pieces (words)
 * 2. Tokenize the words to identify their category
 * 3. Parse the command list to check if the grammar is correct
*/
/** TODO: Need to reconsider the expander process */
void	lexer(t_minishell *ms, char *cmds)
{
	char	**words;
	char	**ori_words;
	char	*ori_cmds;
	char	*ori_word;

	ori_cmds = cmds;
	words = ft_split_delims(cmds, "\"\'");
	ori_words = words;
	while (*words != NULL)
	{
		ori_word = *words;
		expander(ms, &(*words), PARAM);
		tokenizer(ms, *words);
		if (ori_word != *words)
			free(ori_word);
		words++;
	}
	ft_freestrarr(ori_words);
	free(cmds);
	if (ori_cmds != cmds)
		free(ori_cmds);
}
