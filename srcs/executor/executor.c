/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:25:49 by brook             #+#    #+#             */
/*   Updated: 2023/02/06 11:23:17 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_io(int fd, int std_file_no)
{
	dup2(fd, std_file_no);
	close(fd);
}

void	exec_child(t_minishell *ms, t_list *cur_proc, char **cmd, char **envp)
{
	t_cmd	*cur_cmd;
	t_cmd	*next_cmd;

	cur_cmd = cur_proc->content;
	if (cur_proc->next)
	{
		next_cmd = cur_proc->next->content;
		close(next_cmd->pipefd[0]);
		set_io(next_cmd->pipefd[1], STDOUT_FILENO);
	}
	if (cur_cmd->pipefd[0] != 0)
		set_io(cur_cmd->pipefd[0], STDIN_FILENO);
	exec_redirt_in(ms, cur_cmd);
	exec_redirt_out(cur_cmd);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (call_builtin(ms, cur_cmd) == 1 && cmd[0])
		execve(cmd[0], cmd, envp);
	exit(g_errno);
}

int	exec_pipe(t_minishell *ms, t_list *cur_proc, char **envp)
{
	t_cmd	*cur_cmd;
	t_cmd	*next_cmd;
	char	**cmd;

	cur_cmd = cur_proc->content;
	next_cmd = cur_proc->content;
	cmd = lst_to_array(cur_cmd->args);
	if (cur_proc->next)
	{
		next_cmd = cur_proc->next->content;
		pipe(next_cmd->pipefd);
	}
	cur_cmd->pid = fork();
	if (cur_cmd->pid == 0)
		exec_child(ms, cur_proc, cmd, envp);
	else
		free(cmd);
	return (EXIT_SUCCESS);
}

void	wait_pipe(t_minishell *ms)
{
	t_list	*cur_proc;
	t_cmd	*cur_cmd;
	int		status;

	cur_proc = ms->cmds;
	while (cur_proc)
	{
		cur_cmd = cur_proc->content;
		waitpid(cur_cmd->pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			g_errno = (WEXITSTATUS(status));
		if (WIFSIGNALED(status))
			g_errno = 130;
		cur_proc = cur_proc->next;
	}
}

void	executor(t_minishell *ms)
{
	t_list	*cur_proc;
	t_cmd	*cur_cmd;
	t_cmd	*next_cmd;
	char	**envp;

	cur_proc = ms->cmds;
	while (cur_proc != NULL)
	{
		g_errno = -1;
		envp = get_env_arry(ms);
		exec_pipe(ms, cur_proc, envp);
		cur_cmd = cur_proc->content;
		if (cur_proc->next)
		{
			next_cmd = cur_proc->next->content;
			close(next_cmd->pipefd[1]);
		}
		if (cur_cmd->pipefd[0] != 0)
			close(cur_cmd->pipefd[0]);
		free(envp);
		cur_proc = cur_proc->next;
	}
	wait_pipe(ms);
}
