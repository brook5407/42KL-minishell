/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:38:49 by chchin            #+#    #+#             */
/*   Updated: 2023/02/03 13:24:56 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_here_str(char *quote)
{
	char	*line;
	char	*rl;

	rl = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, quote) == 0)
		{
			free(line);
			break ;
		}
		line = ft_strjoin_free(line, "\n");
		rl = ft_strjoin_free(rl, line);
		free(line);
	}
	return (rl);
}

int	exec_heredoc(char *quote)
{
	int		fd[2];
	char	*heredoc;

	if (pipe(fd) == -1)
		perror("PIPE");
	heredoc = get_here_str(quote);
	write(fd[1], heredoc, ft_strlen(heredoc));
	free(heredoc);
	close(fd[1]);
	return (fd[0]);
}

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
				port = open(file->name, O_RDONLY);
			else if (file->rdr_type == HEREDOC)
				port = exec_heredoc(file->name);
			if (port < 0)
			{
				ft_putstr_fd(file->name, 2);
				ft_putendl_fd(": No such file or directory", 2);
				exit (EXIT_FAILURE);
			}
			dup2(port, STDIN_FILENO);
			close(port);
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
