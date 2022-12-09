/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:06:16 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/09 19:39:01 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	else if (dir != NULL && ft_strcmp(dir, "/") != 0)
		dir = ft_strrchr(dir, '/');
	else
		dir = "🤷";
	prompt = ft_strjoin(user, " @ ");
	prompt = ft_strjoin_free(prompt, dir);
	prompt = ft_strjoin_free(prompt, " $ ");
	ms->prompt = prompt;
}

void	init_minishell(t_minishell *ms, char **ev)
{
	ms->envp = NULL;
	init_signal();
	init_environment(ms, ev);
	init_builtins(ms);
	set_prompt(ms);
}
