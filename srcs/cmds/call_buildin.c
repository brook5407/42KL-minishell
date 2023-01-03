/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_buildin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:32:44 by brook             #+#    #+#             */
/*   Updated: 2023/01/03 12:41:24 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	call_buildin(t_minishell *ms, char **cmds)
{
	int	i;

	i = 1;
	if (ft_strcmp(*cmds, "cd") == 0)
		i = call_cd(ms, ++cmds);
	else if (ft_strcmp(*cmds, "env") == 0)
		i = call_env(ms);
	else if (ft_strcmp(*cmds, "export") == 0)
		i = call_export(ms, ++cmds);
	else if (ft_strcmp(*cmds, "exit") == 0)
		i = call_exit(ms, ++cmds);
	else if (ft_strcmp(*cmds, "unset") == 0)
		i = call_unset(ms, ++cmds);
	else if (ft_strcmp(*cmds, "pwd") == 0)
		i = call_pwd(ms);
	else if (ft_strcmp(*cmds, "echo") == 0)
		i = call_echo(ms, ++cmds);
	return (i);
}
