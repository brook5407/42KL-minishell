/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:25:49 by brook             #+#    #+#             */
/*   Updated: 2023/01/03 10:42:34 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_io(int infd, int outfd)
{
	if (infd != STDIN_FILENO)
	{
		dup2(infd, STDIN_FILENO);
		close(infd);
	}
	if (outfd != STDOUT_FILENO)
	{
		dup2(outfd, STDOUT_FILENO);
		close(outfd);
	}
}

void	pipe_exec(t_list *cmds, t_cmd *cmd, char **cmd_args, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	pipe(pipefd);
	pid = fork();
	if (pid > 0)
		;
	else if (pid == 0)
	{
		cmd_args = lst_to_array(cmd->args);
		close(pipefd[0]);
		set_io(STDIN_FILENO, pipefd[1]);
		execve(cmd->cmd_name, cmd_args, envp);
	}
	else
	{
		wait(NULL);
		cmds = cmds->next;
		close(pipefd[1]);
		set_io(pipefd[0], STDOUT_FILENO);
		executor(cmds, envp);
	}
	free(cmd_args);
}

int	executor(t_list *cmds, char **envp)
{
	char	**cmd_args;
	t_cmd	*cmd;

	cmd = cmds->content;
	cmd_args = lst_to_array(cmd->args);
	if (!cmds->next)
	{
		set_io(STDIN_FILENO, STDOUT_FILENO);
		execve(cmd_args[0], cmd_args, envp);
	}
	else
		pipe_exec(cmds, cmd, cmd_args, envp);
	return (0);
}
