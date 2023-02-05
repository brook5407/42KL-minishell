/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:39:24 by chchin            #+#    #+#             */
/*   Updated: 2023/02/05 20:11:46 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_option(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' && arg[i + 1] == 'n')
		i += 2;
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
