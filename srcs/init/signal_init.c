/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:36:52 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/08 20:50:20 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Ctrl + C
 * Expected: Display a new prompt on a new line.
 * Default : Kill the process (SIGINT)
 * 
 * Ctrl + D
 * Expected: Exits the shell
 * Default : Same (SIGTERM)
 * 
 * Ctrl + \
 * Expected: Do nothing
 * Default : Quit program (SIGQUIT)
 */

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signal()
{
	struct termios		old_state;

	tcgetattr(STDIN_FILENO, &old_state);
	old_state.c_cflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &old_state);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}