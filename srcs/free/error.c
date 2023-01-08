/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:49:34 by wricky-t          #+#    #+#             */
/*   Updated: 2023/01/08 18:03:14 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (type == CMD_NOT_FOUND)
		ft_printf("%s: command not found\n", token);
	if (type == FILE_NOT_FOUND)
		ft_printf("%s: no such file or directory\n");
	if (type == INVALID_ID)
		ft_printf("export: `%s': not a valid identifier\n", token);
}
