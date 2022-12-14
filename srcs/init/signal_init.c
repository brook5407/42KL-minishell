/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:36:52 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/14 20:40:37 by wricky-t         ###   ########.fr       */
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
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signal(void)
{
	struct termios		old_state;

	if (tcgetattr(STDIN_FILENO, &old_state) == -1)
	{
		printf("Get terminal control attribute failed.\n");
		exit(0);
	}
	old_state.c_cflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &old_state) == -1)
	{
		printf("Set terminal control attribute failed.\n");
		exit(0);
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
