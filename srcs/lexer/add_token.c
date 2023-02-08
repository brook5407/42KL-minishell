/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:14:03 by wricky-t          #+#    #+#             */
/*   Updated: 2023/02/08 11:23:54 by wricky-t         ###   ########.fr       */
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

	tok = malloc(sizeof(t_token));
	if (tok == NULL)
		return ;
	tok->type = type;
	tok->value = token;
	ft_lstadd_back(&ms->tokens, ft_lstnew(tok));
}
