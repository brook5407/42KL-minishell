/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:25:49 by brook             #+#    #+#             */
/*   Updated: 2023/01/31 16:15:57 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_io(int rfd, int wfd)
{
	if (rfd != STDIN_FILENO)
	{
		dup2(rfd, STDIN_FILENO);
		close(rfd);
	}
	if (wfd != STDOUT_FILENO)
	{
		dup2(wfd, STDOUT_FILENO);
		close(wfd);
	}
}

void	exec_child(t_minishell *ms, t_list *cur_proc, char **cmd, char **envp)
{
	int		ret;
	t_cmd	*cur_cmd;
	t_cmd	*next_cmd;

	ret = EXIT_SUCCESS;
	cur_cmd = cur_proc->content;
	if (cur_proc->next != NULL)
	{
		next_cmd = cur_proc->next->content;
		set_io(STDIN_FILENO, next_cmd->pipefd[1]);
	}
	if (cur_cmd->pipefd[0] != 0)
		set_io(cur_cmd->pipefd[0], STDOUT_FILENO);
	if (call_buildin(ms, cur_cmd) == 1)
		ret = execve(cmd[0], cmd, envp);
	exit(ret);
}

int	exec_pipe(t_minishell *ms, t_list *cur_proc, char **envp)
{
	t_cmd	*cur_cmd;
	t_cmd	*next_cmd;
	char	**cmd;
	pid_t	pid;
	int		status;

	cur_cmd = cur_proc->content;
	next_cmd = cur_proc->content;
	cmd = lst_to_array(cur_cmd->args);
	if (cur_proc->next != NULL)
	{
		next_cmd = cur_proc->next->content;
		pipe(next_cmd->pipefd);
	}
	pid = fork();
	if (pid == 0)
		exec_child(ms, cur_proc, cmd, envp);
	waitpid(pid, &status, 0);
	if (cur_proc->next)
		close(next_cmd->pipefd[1]);
	if (cur_cmd->pipefd[0] != 0)
		close(cur_cmd->pipefd[0]);
	free(cmd);
	return (EXIT_SUCCESS);
}

int	executor(t_minishell *ms)
{
	t_list	*cmds;
	char	**envp;

	cmds = ms->cmds;
	while (cmds != NULL)
	{
		if (cmds->next == NULL && call_buildin(ms, cmds->content) == 0)
			;
		else
		{
			envp = get_env_arry(ms);
			exec_pipe(ms, cmds, envp);
			free(envp);
		}
		cmds = cmds->next;
	}
	return (0);
}
