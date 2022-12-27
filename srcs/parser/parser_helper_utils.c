/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 17:46:05 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/27 21:12:54 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_parser_helper(t_parse_hlpr *phlpr)
{
	int i;

    i = -1;
	phlpr->prev = UNKNOWN;
	reset_all_type(phlpr, 1);
}

void	reset_all_type(t_parse_hlpr *phlpr, int status)
{
	int	i;

	if (status != 0 && status != 1)
		return ;
	i = -1;
	while (++i < TYPE_TOTAL)
		phlpr->expected[i] = status;
}

void	reject_type(t_parse_hlpr *phlpr, t_token_type type)
{
	if (!(type >= 0 && type < TYPE_TOTAL))
		return ;
	phlpr->expected[type] = 0;
}

void	toggle_type(t_parse_hlpr *phlpr, t_token_type type)
{
	if (!(type >= 0 && type < TYPE_TOTAL))
		return ;
	phlpr->expected[type] = !phlpr->expected[type];
}

int	is_type_on(t_parse_hlpr *phlpr, t_token_type type)
{
	if (!(type >= 0 && type < TYPE_TOTAL))
		return (-1);
	return (phlpr->expected[type] == 1);
}
