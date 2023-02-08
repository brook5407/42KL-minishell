/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:38:49 by chchin            #+#    #+#             */
/*   Updated: 2023/02/08 11:22:21 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_io(int fd, int std_file_no)
{
	dup2(fd, std_file_no);
	close(fd);
}

int	exec_redirt_in(t_minishell *ms, t_cmd *cur_cmd)
{
	int		port;
	t_list	*lst_redir;
	t_file	*file;

	if (cur_cmd->infile != NULL)
	{
		lst_redir = cur_cmd->infile;
		while (lst_redir)
		{
			file = lst_redir->content;
			if (file->rdr_type == RDRIN)
				port = open(file->name, O_RDONLY);
			else if (file->rdr_type == HEREDOC)
				port = exec_heredoc(ms, file->name);
			if (port < 0)
			{
				show_error(FILE_NOT_FOUND, file->name);
				set_io(port, STDIN_FILENO);
				return (EXIT_FAILURE);
			}
			lst_redir = lst_redir->next;
		}
		set_io(port, STDIN_FILENO);
	}
	return (EXIT_SUCCESS);
}

void	exec_redirt_out(t_cmd *cur_cmd)
{
	int		flag;
	int		port;
	t_list	*lst_redir;
	t_file	*file;

	if (cur_cmd->outfile != NULL)
	{
		lst_redir = cur_cmd->outfile;
		while (lst_redir)
		{
			file = lst_redir->content;
			if (file->rdr_type == RDROUT)
				flag = O_CREAT | O_TRUNC | O_WRONLY;
			else if (file->rdr_type == APPEND)
				flag = O_CREAT | O_APPEND | O_WRONLY;
			port = open(file->name, flag, 0644);
			set_io(port, STDOUT_FILENO);
			lst_redir = lst_redir->next;
		}
	}
}
