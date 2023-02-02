/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:39:24 by chchin            #+#    #+#             */
/*   Updated: 2023/02/02 16:00:41 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_flag(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' && s[i + 1] == 'n')
	{
		i += 2;
		while (s[i] == 'n')
			i++;
		if (s[i] == '\0')
			return (i);
	}
	return (0);
}

void	call_echo(t_minishell *ms, char **cmds)
{
	int	next_line;

	(void)ms;
	next_line = 1;
	if (*cmds == NULL)
	{
		printf("\n");
		return ;
	}
	while (check_flag(*cmds) > 0)
	{
		next_line = 0;
		cmds++;
	}
	while (*cmds != NULL)
	{
		printf("%s", *cmds);
		cmds++;
		if (*cmds != NULL)
			printf(" ");
	}
	if (next_line == 1)
		printf("\n");
}
