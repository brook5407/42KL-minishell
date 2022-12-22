/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:39:24 by chchin            #+#    #+#             */
/*   Updated: 2022/12/20 19:31:36 by brook            ###   ########.fr       */
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

int	call_echo(t_minishell *ms, char *s)
{
	int	i;

	i = check_flag(s);
	(void)ms;
	if (!i)
		printf("%s\n", s);
	else
		printf("%s", s + i);
	return (0);
}
