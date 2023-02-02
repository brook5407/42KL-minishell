/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:38:49 by chchin            #+#    #+#             */
/*   Updated: 2023/02/02 15:54:57 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	exec_heredoc(t_cmd *cur_cmd, char *quote)
// {
// 	int		fd;
// 	char	*line;
// 	char	*rl;
// 	t_file	*heredoc;

// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (ft_strchr(line, quote))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		line = ft_strjoin_free(line, "\n");
// 		rl = ft_strjoin_free(rl, line);
// 		free(line);
// 	}
// }

void	exec_redirt_in(t_cmd *cur_cmd)
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
			{
				port = open(file->name, O_RDONLY);
				dup2(port, STDIN_FILENO);
				close(port);
			}
			lst_redir = lst_redir->next;
		}
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
				flag = O_WRONLY | O_TRUNC | O_CREAT;
			else if (file->rdr_type == APPEND)
				flag = O_WRONLY | O_APPEND | O_CREAT;
			port = open(file->name, flag);
			dup2(port, STDOUT_FILENO);
			close(port);
			lst_redir = lst_redir->next;
		}
	}
}

