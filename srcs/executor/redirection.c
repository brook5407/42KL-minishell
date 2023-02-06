/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:38:49 by chchin            #+#    #+#             */
/*   Updated: 2023/02/06 16:07:48 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_redirt_in(t_minishell *ms, t_cmd *cur_cmd)
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
				ft_putstr_fd(file->name, 2);
				ft_putendl_fd(": No such file or directory", 2);
				exit(EXIT_FAILURE);
			}
			lst_redir = lst_redir->next;
		}
		dup2(port, STDIN_FILENO);
		close(port);
	}
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
				flag = O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT;
			else if (file->rdr_type == APPEND)
				flag = O_RDONLY | O_WRONLY | O_APPEND | O_CREAT;
			port = open(file->name, flag);
			dup2(port, STDOUT_FILENO);
			close(port);
			lst_redir = lst_redir->next;
		}
	}
}
