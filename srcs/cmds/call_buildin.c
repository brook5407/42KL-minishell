/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_buildin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brook <brook@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:32:44 by brook             #+#    #+#             */
/*   Updated: 2022/12/13 21:39:19 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	call_buildin(t_minishell *ms, char *cmds)
{
	if (ft_strncmp(cmds, "cd", 2) == 0)
		call_cd(ms, ft_strchr(cmds, ' '));
	else if (ft_strcmp(cmds, "env") == 0)
		call_env(ms);
	else if (ft_strncmp(cmds, "export", 6) == 0)
		call_export(ms, ft_strchr(cmds, ' '));
	else if (ft_strncmp(cmds, "exit", 4) == 0)
		call_exit(ms, ft_strchr(cmds, ' '));
	else if (ft_strncmp(cmds, "unset", 5) == 0)
		call_unset(ms, ft_strchr(cmds, ' '));
	else if (ft_strcmp(cmds, "pwd") == 0)
		call_pwd(ms);
	return (0);
}