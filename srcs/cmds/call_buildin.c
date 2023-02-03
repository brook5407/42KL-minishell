/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_buildin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:32:44 by brook             #+#    #+#             */
/*   Updated: 2023/02/02 16:00:51 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**lst_to_array(t_list *lst)
{
	int		i;
	int		size;
	char	**array;

	size = ft_lstsize(lst) + 1;
	array = malloc(sizeof(char *) * size);
	if (!array)
		return (NULL);
	i = 0;
	while (lst)
	{
		array[i++] = lst->content;
		lst = lst->next;
	}
	array[i] = NULL;
	return (array);
}

int	call_buildin(t_minishell *ms, t_cmd *cmd)
{
	char	**cmds;

<<<<<<< HEAD
	// show_cmd_block(cmd);
=======
	if (!cmd->cmd_name)
		return (EXIT_FAILURE);
>>>>>>> d83ca5a6d9e9059a1fa197a5971e16bd5b0f37d2
	cmds = lst_to_array(cmd->args);
	if (ft_strcmp(*cmds, "cd") == 0)
		call_cd(ms, ++cmds);
	else if (ft_strcmp(*cmds, "env") == 0)
		call_env(ms);
	else if (ft_strcmp(*cmds, "export") == 0)
		call_export(ms, ++cmds);
	else if (ft_strcmp(*cmds, "exit") == 0)
		call_exit(ms, ++cmds);
	else if (ft_strcmp(*cmds, "unset") == 0)
		call_unset(ms, ++cmds);
	else if (ft_strcmp(*cmds, "pwd") == 0)
		call_pwd(ms);
	else if (ft_strcmp(*cmds, "echo") == 0)
		call_echo(ms, ++cmds);
	else
	{
		free(cmds);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
