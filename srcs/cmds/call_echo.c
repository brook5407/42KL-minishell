/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:39:24 by chchin            #+#    #+#             */
/*   Updated: 2023/01/03 13:55:08 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_flag(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' && s[i + 1] == 'n')
	{
		i++;
		while (s[i] == 'n')
			i++;
		if (s[i] == ' ' || !s[i])
		{
			if (s[i] == ' ')
				return (++i);
			else
				return (i);
		}
	}
	return (0);
}

int	call_echo(t_minishell *ms, char **cmds)
{
	int	i;

	(void)ms;
	while (*cmds)
	{
		if (check_flag(*cmds) > 0)
		{
			i = 1;
			cmds++;
		}
	}
	while (*cmds)
	{
		if (!i)
			printf("%s\n", *cmds);
		else
			printf("%s", *cmds);
		printf(" ");
		cmds++;
	}
	return (0);
}
