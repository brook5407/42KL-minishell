/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_buildin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:32:44 by brook             #+#    #+#             */
/*   Updated: 2022/12/27 15:51:52 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	call_buildin(t_minishell *ms, char *cmds)
{
	int	i;

	i = 1;
	if (ft_strncmp(cmds, "cd", 2) == 0)
		i = call_cd(ms, ft_strchr(cmds, ' '));
	else if (ft_strcmp(cmds, "env") == 0)
		i = call_env(ms);
	else if (ft_strncmp(cmds, "export", 6) == 0)
		i = call_export(ms, ft_strchr(cmds, ' '));
	else if (ft_strncmp(cmds, "exit", 4) == 0)
		i = call_exit(ms, ft_strchr(cmds, ' '));
	else if (ft_strncmp(cmds, "unset", 5) == 0)
		i = call_unset(ms, ft_strchr(cmds, ' '));
	else if (ft_strcmp(cmds, "pwd") == 0)
		i = call_pwd(ms);
	else if (ft_strncmp(cmds, "echo", 4) == 0)
		i = call_echo(ms, ft_strchr(cmds, ' ') + 1);
	return (i);
}
