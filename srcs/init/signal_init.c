/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:36:52 by wricky-t          #+#    #+#             */
/*   Updated: 2023/02/09 11:04:45 by wricky-t         ###   ########.fr       */
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

/**
 * Signal handler for SIGINT
 *
 * @brief Replicate the behaviour of Bash when using CTRL + C
 *
 * 1. Print a new line
 * 2. Replace the current line in the input buffer to ""
 * 3. Move the cursor to the start of the next line
 * 4. Redraw the current input line on the screen
*/
static void	signal_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	if (g_errno < 0)
		return ;
	g_errno = 1;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	init_termios_signal(int set_sig)
{
	struct termios		termios_current;

	if (tcgetattr(STDIN_FILENO, &termios_current) == -1)
	{
		perror("tcgetattr failed\n");
		exit(0);
	}
	termios_current.c_cflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_current) == 1)
	{
		perror("tcsetattr failed\n");
		exit(0);
	}
	if (set_sig)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}

/**
 * @brief Signal handler for heredoc
*/
static void	heredoc_signal_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	g_errno = INTERRUPTED;
	rl_on_new_line();
	ft_printf("\n");
	rl_replace_line("", 0);
}

/**
 * @brief Set heredoc signal
*/
void	init_heredoc_signal(void)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
