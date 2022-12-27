/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:25:49 by brook             #+#    #+#             */
/*   Updated: 2022/12/27 16:18:08 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	set_io(t_cmd *cmd, int rfd, int wfd)
// {
// 	if (cmd->)
// }

// void executor(t_minishell *ms, char *str)
// {
// 	int fd[2];
	
// 	if(!pcmd->next)
// 	{
// 		setIO(pcmd,STDIN_FILENO,STDOUT_FILENO);
// 		execve(pcmd->args[0],pcmd->args, );
// 	}
// 	pipe(fd);
// 	pid_t pid = fork();
// 	if(pid<0)
// 		Error(FORK_ERROR);
// 	else if (pid==0)
// 	{
// 		close(fd[0]);
// 		setIO(pcmd,STDIN_FILENO,fd[1]);
// 		execvp(pcmd->args[0],pcmd->args);
// 		Error(EXEC_ERROR);
// 	}
// 	else
// 	{
// 		wait(NULL);
// 		pcmd = pcmd->next;  //notice
// 		close(fd[1]);
// 		setIO(pcmd,fd[0],STDOUT_FILENO);  
// 		executer(pcmd);
// 	}
// 	return (0);

}