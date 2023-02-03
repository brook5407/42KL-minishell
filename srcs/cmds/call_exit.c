/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:32:50 by chchin            #+#    #+#             */
/*   Updated: 2023/02/03 17:51:49 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_isdigit(char *args)
{
	int	i;

	i = 0;
	while (args[i])
		if (ft_isdigit(args[i++]) == 0)
			return (1);
	return (0);
}

void	call_exit(t_minishell *ms, char **args)
{
	write(1, "exit\n", 5);
	if (args != NULL && *args != NULL)
	{
		if (check_isdigit(*args))
		{
			printf("exit: %s: numeric argument required\n", *args);
			exit(255);
		}
		if (ft_strarrsize(args) > 1)
		{
			show_error(TOO_MANY_ARG, "EXIT");
			return ;
		}
	}
	free(ms->prompt);
	free_env(ms->envp);
	free(args);
	exit(g_errno);
}
