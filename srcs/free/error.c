/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:49:34 by wricky-t          #+#    #+#             */
/*   Updated: 2023/02/03 15:45:12 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_errno(t_error_type type)
{
	if (type == INVALID_ID_EXP || type == INVALID_ID_UNS)
	{
		g_errno = 1;
		return ;
	}
	g_errno = type;
}

void	show_error(t_error_type type, char *token)
{
	if (type == SUCCESS)
		return ;
	ft_printf("minishell: ");
	if (type == SYNTAX_ERROR)
	{
		ft_printf("syntax error near unexpected token ");
		if (token == NULL)
			ft_printf("`newline'\n");
		else
			ft_printf("`%s'\n", token);
	}
	if (type == TOO_MANY_ARG)
		ft_printf("%s: too many arguments\n", token);
	if (type == CMD_NOT_FOUND)
		ft_printf("%s: command not found\n", token);
	if (type == FILE_NOT_FOUND)
		ft_printf("%s: no such file or directory\n", token);
	if (type == INVALID_ID_EXP)
		ft_printf("export: `%s': not a valid identifier\n", token);
	if (type == INVALID_ID_UNS)
		ft_printf("unset: `%s': not a valid identifier\n", token);
	set_errno(type);
}
