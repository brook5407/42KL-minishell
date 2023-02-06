/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 20:52:18 by brook             #+#    #+#             */
/*   Updated: 2023/02/06 11:27:58 by wricky-t         ###   ########.fr       */
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

	rl = ft_strdup("");
	while (1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, quote) == 0)
		{
			free(line);
			break ;
		}
		line = ft_strjoin_free(line, "\n");
		process_here_str(ms, &line);
		rl = ft_strjoin_free(rl, line);
		free(line);
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
