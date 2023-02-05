/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brook <brook@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 20:52:18 by brook             #+#    #+#             */
/*   Updated: 2023/02/05 22:14:19 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_here_str(t_minishell *ms, char *quote)
{
	char	*line;
	char	*rl;

	rl = ft_strdup("");
//	quote = ft_strjoin_free(quote, "\n");
	while (1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
//		write(1, "< ", 2);
//		line = get_next_line(STDIN_FILENO);
		line = readline("< ");
		if (line == NULL || ft_strcmp(line, quote) == 0)
		{
			free(line);
			break ;
		}
		line = ft_strjoin_free(line, "\n");
		expander(ms, &line, PARAM);
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