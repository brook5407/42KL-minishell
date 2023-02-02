/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:12:41 by wricky-t          #+#    #+#             */
/*   Updated: 2023/01/12 16:30:30 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * GRAMMAR
 * 1. After a string, can be anything
 *    CODE:
 *    reset_all_type(), status = 1
 *    TYPE: FREE_FORM_GRAMMAR
 *
 * 2. At the start of a grammar, the acceptable tokens are:
 *      i.	 Redirection (Append, in, out)
 *      ii.	 Heredoc
 *      iii. CMD / EXT_CMD
 * 	  turn off PIPE & STR
 *    If it's a str at the very first, error: invalid command
 *    If it's a |, error: parse error
 *    CODE:
 *    reset_all_type(), status = 1
 *    toggle_type(PIPE) // should be 0
 *    toggle_type(STR) // should be 0
 *    TYPE: START_GRAMMAR
 *
 * 3. After a pipe, reset the grammar
 *    CODE:
 *    reset_all_type(), status = 1
 *    toggle_type(PIPE) // should be 0
 *    toggle_type(STR) // should be 0
 *    TYPE: POST_PIPE_GRAMMAR / START_GRAMMAR
 *
 * 4. After a redirection must be a filename
 *      i.   Redirection out/append -> outfile
 *      ii.  Redirection in-> infile
 *    Don't care it's a CMD, EXT_CMD, or STR. Treat that as a file.
 *    CODE:
 *    reset_all_type(), status = 0
 *    toggle_type(CMD) // should be 1
 *    toggle_type(EXT_CMD) // should be 1
 *    toggle_type(STR) // should be 1
 *    TYPE: POST_RDR_GRAMMAR
 *
 * 5. After a file could be anything.
 *    CODE:
 *    reset_all_type(), status = 1.
 *    TYPE: FREE_FORM_GRAMMAR
 *
 *
 * 6. After a CMD or EXT_CMD, whatever behind it will be valid.
 *    CODE:
 *    reset_all_type(), status = 1
 *    TYPE: FREE_FORM_GRAMMAR
 */

/**
 * @brief Reset all acceptable token to a status (1 = Accept, 0 = Reject)
 */
void	reset_all_type(t_parser *hlpr, int status)
{
	int	i;

	if (status != 0 && status != 1)
		return ;
	i = -1;
	while (++i < TYPE_TOTAL)
		hlpr->expected[i] = status;
}

/**
 * @brief Toggle the acceptability of a type of token
 *
 * @param hlpr pointer to parser helper
 * @param type token type
 *
 * Reject will become Accept
 * Accept will become Reject
 */
void	toggle_type(t_parser *hlpr, t_token_type type)
{
	if (!(type >= 0 && type < TYPE_TOTAL))
		return ;
	hlpr->expected[type] = !hlpr->expected[type];
}

/**
 * @brief Check if a token is acceptable in the current grammar
 *
 * @param hlpr pointer to parser helper
 * @param type token type
 *
 * Return 1 if it's acceptable, 0 if it's not acceptable.
 */
int	is_type_on(t_parser *hlpr, t_token_type type)
{
	if (!(type >= 0 && type < TYPE_TOTAL))
		return (-1);
	return (hlpr->expected[type] == 1);
}

/**
 * @brief Apply grammar based on the specified grammar.
 *
 * @param hlpr pointer to parser helper
 * @param grammar grammar type
 *
 * There are 5 types of grammar:
 * 1. START - Represent the acceptable tokens at the start of a grammar
 * 2. POST_RDR - Represent the acceptable tokens after a redirection
 * 3. CMD_ONLY - Accept only CMD/EXT_CMD token
 * 4. FREE_FORM - Accept any types of token
 */
void	apply_grammar(t_parser *hlpr, t_grammar grammar)
{
	if (grammar == POST_RDR)
		reset_all_type(hlpr, 0);
	else
		reset_all_type(hlpr, 1);
	if (grammar == START)
		toggle_type(hlpr, PIPE);
	if (grammar == POST_RDR)
	{
		toggle_type(hlpr, CMD);
		toggle_type(hlpr, EXT_CMD);
	}
	if (grammar == START || grammar == POST_RDR)
		toggle_type(hlpr, STR);
}

/**
 * @brief Set the next grammar so that the next token is what's expected.
 *        The grammar is set based on the current token.
 *
 * @param hlpr pointer to parser helper
 * @param curr type of the current token
 */
void	set_next_grammar(t_parser *hlpr, t_token_type curr)
{
	t_grammar	grammar;

	grammar = UNSET;
	if ((curr == STR || curr == CMD || curr == EXT_CMD))
		grammar = FREE_FORM;
	if (curr == PIPE)
		grammar = START;
	if (curr == RDRIN || curr == RDROUT || curr == APPEND || curr == HEREDOC)
		grammar = POST_RDR;
	if (grammar != UNSET)
	{
		apply_grammar(hlpr, grammar);
		hlpr->curr_grammar = grammar;
	}
}
