/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:06:16 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/13 15:34:31 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Set the list of builtins name
 * 
 * This is to avoid the if else ft_strcmp chain. Can just iterate
 * through this list using a loop and do whatever you want.
*/
static void	init_builtins(t_minishell *ms)
{
	char	**builtins;

	builtins = ft_calloc(BUILTINS_TOTAL + 1, sizeof(char *));
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "env";
	builtins[4] = "unset";
	builtins[5] = "export";
	builtins[6] = "exit";
	ms->builtins = builtins;
}

/**
 * @brief Set the list of operators
 * 
 * This is to avoid the if else ft_strcmp chain. Can just iterate
 * through this list using a loop and do whatever you want.
*/
static void	init_operators(t_minishell *ms)
{
	char	**operators;

	operators = ft_calloc(OPERATORS_TOTAL + 1, sizeof(char *));
	operators[0] = "|";
	operators[1] = ">";
	operators[2] = "<";
	operators[3] = ">>";
	operators[4] = "<<";
	ms->operators = operators;
}

/**
 * @brief Set the prompt message
 * 
 * Format: [USER] @ [CURRENT DIRECTORY] $
 * 
 * Special case:
 * 1. If at HOME, current_directory show "~" instead of directory name
 * 2. If PWD is not set, current_directory set as "🤷"
 * 3. If PWD is set, dir's pointer set to the last '/'
*/
void	set_prompt(t_minishell *ms)
{
	char	*user;
	char	*dir;
	char	*prompt;

	user = get_env_value(ms, "USER");
	if (user == NULL)
		user = "user";
	dir = get_env_value(ms, "PWD");
	if (dir != NULL && ft_strcmp(dir, get_env_value(ms, "HOME")) == 0)
		dir = "~";
	else if (dir != NULL)
		dir = ft_strrchr(dir, '/');
	else
		dir = "🤷";
	prompt = ft_strjoin(user, " @ ");
	prompt = ft_strjoin_free(prompt, dir);
	prompt = ft_strjoin_free(prompt, " $ ");
	ms->prompt = prompt;
}

/**
 * @brief Initialize the main struct
 * 
 * 1. Initialize signal
 * 2. Initialize environment variables
 * 3. Initialize builtins name
 * 4. Set the prompt
*/
void	init_minishell(t_minishell *ms, char **ev)
{
	ms->envp = NULL;
	init_signal(ms);
	init_environment(ms, ev);
	init_builtins(ms);
	init_operators(ms);
	// set_prompt(ms);
}
