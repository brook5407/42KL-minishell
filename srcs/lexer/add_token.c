/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:14:03 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/27 16:11:52 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token(void	*content)
{
	t_token	*token;

	token = content;
	free(token->value);
	free(token);
}

void	add_token(t_minishell *ms, t_token_type type, char *token)
{
	t_token		*tok;
	char		*temp;

	tok = malloc(sizeof(t_token));
	if (tok == NULL)
		return ;
	tok->type = type;
	temp = token;
	expander(ms, &token, INQUOTE);
	if (temp != token)
		free(temp);
	tok->value = token;
	ft_lstadd_back(&ms->tokens, ft_lstnew(tok));
}

/**
 * Testing start
*/

void	print_token_type(t_token_type type, char *token)
{
	if (type == CMD)
		printf("[CMD]: %s\n", token);
	else if (type == EXT_CMD)
		printf("[EXT_CMD]: %s\n", token);
	else if (type == RDRIN)
		printf("[RDRIN]: %s\n", token);
	else if (type == RDROUT)
		printf("[RDROUT]: %s\n", token);
	else if (type == HEREDOC)
		printf("[HEREDOC]: %s\n", token);
	else if (type == APPEND)
		printf("[APPEND]: %s\n", token);
	else if (type == PIPE)
		printf("[PIPE]: %s\n", token);
	else if (type == STR)
		printf("[STR]: %s\n", token);
}

void	list_all_token(void *content)
{
	t_token	*tok;

	tok = content;
	printf(" | ");
	print_token_type(tok->type, tok->value);
}

/**
 * Testing end
*/