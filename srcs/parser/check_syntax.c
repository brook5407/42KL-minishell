/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:01:19 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/27 15:57:00 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Check the syntax of the command
 * 
 * Checks for:
 * 1. Invalid operators
 * 2. Incomplete grammar, with dangling operator
 * 		- [cmd] [opr]
 * 3. Check grammar
 * 		- Simple command grammar: [CMD] [STR...] [OPR] [CMD] [STR...]
 * 		- Operator (pipe only) resets the grammar
*/
// void	check_syntax(t_minishell *ms)
// {}

/**
 * SIMPLE COMMAND (definition from Bash documentation)
 * A simple command is the kind of command encountered most often. It’s just
 * a sequence of words separated by blanks, terminated by one of the shell’s
 * control operators. (ex: ||, &&, &, ;, ;;, ;&, ;;&, |, |&, (, ))
 * Redirections: <, >, <<, >> are not "control operators".
 * The first word generally specifies a command to be executed, with the
 * rest of the words being that command’s arguments.
*/

/**
 * PIPELINES (|)
 * A pipeline is a sequence of one or more commands separated by one of
 * the control operators ‘|’ or ‘|&’.
 * 
 * 
*/

/**
 * In general, redirections are performed before pipelines in Bash.
 * However, if a redirection comes after a pipeline operator, it will be ignored.
*/

/**
 * Operators:
 * 1. |
 * 2. >
 * 3. <
 * 4. >>
 * 5. <<
*/
int	check_operator_syntax(t_minishell *ms, char *token)
{
	int	i;
	int	token_len;
	int	opr_len;

	i = -1;
	token_len = ft_strlen(token);
	while (ms->operators[++i] != NULL)
	{
		opr_len = ft_strlen(ms->operators[i]);
		if (ft_strncmp(ms->operators[i], token, opr_len) == 0)
			break ;
	}
	if (token_len != opr_len)
	{
		show_error(ms, SYNTAX_ERROR, token + opr_len);
		return (0);
	}
	return (1);
}

// void	check_incomplete_grammar(t_minishell *ms)
// {
// 	t_list	*tokens;
// 	t_token	*tok;

// 	tokens = ms->tokens;
// 	while (tokens != NULL)
// 	{
// 		tok = tokens->content;
// 		if (tok->type == OPR && tokens->next == NULL)
// 		{
// 			show_error(ms, SYNTAX_ERROR, NULL);
// 			return ;
// 		}
// 		tokens = tokens->next;
// 	}
// }
