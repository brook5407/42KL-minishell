/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:01:19 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/14 21:39:22 by wricky-t         ###   ########.fr       */
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
*/
// void	check_syntax(t_minishell *ms)
// {}

/**
 * Operators:
 * 1. |
 * 2. >
 * 3. <
 * 4. >>
 * 5. <<
*/
void	check_operator_syntax(t_minishell *ms, char *token)
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
		printf("ms: syntax error near unexpected token `%c'\n", *(token + opr_len));
		exit(1);
	}
}

void	check_incomplete_grammar(t_minishell *ms)
{
	t_list	*tokens;
	t_token	*tok;

	tokens = ms->tokens;
	while (tokens != NULL)
	{
		tok = tokens->content;
		if (tok->type == OPR && tokens->next == NULL)
		{
			printf("ms: syntax error near unexpected token `newline'\n");
			exit(1);
		}
		tokens = tokens->next;
	}
}
