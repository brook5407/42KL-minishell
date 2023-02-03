/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:25:49 by brook             #+#    #+#             */
/*   Updated: 2023/02/02 13:36:42 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_child(t_minishell *ms, t_list *cur_proc, char **cmd, char **envp)
{
	int		ret;
	t_cmd	*cur_cmd;
	t_cmd	*next_cmd;

	ret = EXIT_SUCCESS;
	cur_cmd = cur_proc->content;
	if (cur_proc->next)
	{
		next_cmd = cur_proc->next->content;
		close(next_cmd->pipefd[0]);
		dup2(next_cmd->pipefd[1], STDOUT_FILENO);
		close(next_cmd->pipefd[1]);
	}
	if (cur_cmd->pipefd[0] != 0)
	{
		dup2(cur_cmd->pipefd[0], STDIN_FILENO);
		close(cur_cmd->pipefd[0]);
	}
	exec_redirt_in(cur_cmd);
	exec_redirt_out(cur_cmd);
	if (call_buildin(ms, cur_cmd) == 1 && cmd[0])
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
	if (cur_proc->next)
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
	t_list	*cur_proc;
	char	**envp;

	cur_proc = ms->cmds;
	while (cur_proc != NULL)
	{
		if (cur_proc->next == NULL && call_buildin(ms, cur_proc->content) == 0)
			;
		else
		{
			envp = get_env_arry(ms);
			exec_pipe(ms, cur_proc, envp);
			free(envp);
		}
		cur_proc = cur_proc->next;
	}
	return (0);
}
