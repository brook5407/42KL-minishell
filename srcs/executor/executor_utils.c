/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:38:49 by chchin            #+#    #+#             */
/*   Updated: 2023/02/05 17:48:18 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_here_str(t_minishell *ms, char **line)
{
	char	*id;
	char	*line_tmp;
	char	*str;

	line_tmp = *line;
	id = ft_strchr(line_tmp, '$');
	if (id == NULL)
		return ;
	str = expand_parameter(ms, line_tmp);
	free(*line);
	*line = str;
}

char	*get_here_str(t_minishell *ms, char *quote)
{
	char	*line;
	char	*rl;
	char	*tmp;

	rl = ft_strdup("");
	ft_printf("> ");
	while (1)
	{
		init_termios_signal(0);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			return (rl);
		tmp = ft_strndup(line, ft_strlen(line) - 1);
		if (ft_strcmp(tmp, quote) == 0)
		{
			free(line);
			break ;
		}
		free(tmp);
		process_here_str(ms, &line);
		rl = ft_strjoin_free(rl, line);
		free(line);
		ft_printf("> ");
	}
	return (rl);
}

int	exec_heredoc(t_minishell *ms, char *quote)
{
	int		fd[2];
	char	*heredoc;

	if (pipe(fd) == -1)
		perror("PIPE");
	heredoc = get_here_str(ms, quote);
	write(fd[1], heredoc, ft_strlen(heredoc));
	free(heredoc);
	close(fd[1]);
	return (fd[0]);
}

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

/** TODO: Move this to somewhere else maybe */
void	exec_exit_status(int status)
{
	if (WIFEXITED(status))
		g_errno = (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		g_errno = 130;
}
