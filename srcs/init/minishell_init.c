/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:06:16 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/08 11:27:39 by wricky-t         ###   ########.fr       */
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

// char	*set_color(char *str, char *color)
// {
// 	char	*colored;
// 	char	*temp;

// 	colored = ft_strjoin(color, str);
// 	temp = colored;
// 	free(temp);
// 	colored = ft_strjoin(colored, DEF);
// 	free(colored);
// 	return (colored);
// }

void	set_prompt(t_minishell *ms)
{
	char	*user;
	char	*dir;
	char	*prompt;
	char	*temp;

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
	temp = prompt;
	prompt = ft_strjoin(prompt, dir);
	free(temp);
	temp = prompt;
	prompt = ft_strjoin (prompt, " $ ");
	free(temp);
	ms->prompt = prompt;
}

void	init_minishell(t_minishell *ms, char **ev)
{
	ms->envp = NULL;
	init_environment(ms, ev);
	init_builtins(ms);
	set_prompt(ms);
}
