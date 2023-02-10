/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:39:24 by chchin            #+#    #+#             */
/*   Updated: 2023/02/10 12:03:08 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_option(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (i);
	return (0);
}

void	call_echo(t_minishell *ms, char **args)
{
	int	omit_nl;

	(void)ms;
	omit_nl = 0;
	if (*args == NULL)
	{
		ft_printf("\n");
		return ;
	}
	while (*args != NULL && is_option(*args) > 0)
	{
		omit_nl = 1;
		args++;
	}
	while (*args != NULL)
	{
		ft_printf("%s", *(args++));
		if (*args != NULL)
			ft_printf(" ");
	}
	if (omit_nl == 0)
		ft_printf("\n");
}
