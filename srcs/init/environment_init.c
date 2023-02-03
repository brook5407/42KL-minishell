/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:05:04 by wricky-t          #+#    #+#             */
/*   Updated: 2023/02/03 11:30:21 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Add environment variable as a node to env list
*/
void	add_env_var(t_minishell *ms, char *key, char *value)
{
	t_env	*env_var;

	env_var = malloc(sizeof(t_env));
	if (env_var == NULL)
		return ;
	env_var->key = key;
	env_var->value = value;
	ft_lstadd_back(&ms->envp, ft_lstnew(env_var));
}

/**
 * @brief Convert the environment variables into a list
 * 
 * @details
 * Extract the key and value out and add as env_var.
*/
void	init_environment(t_minishell *ms, char **ev)
{
	char	*key;
	char	*value;

	while (*ev != NULL)
	{
		value = ft_strchr(*ev, '=');
		key = ft_strndup(*ev, (value - *ev));
		value = ft_strdup(value + 1);
		add_env_var(ms, key, value);
		ev++;
	}
}

/**
 * @brief Copy and create a new env variable
*/
void	*cpy_env(void *env)
{
	t_env	*ori;
	t_env	*cpy;

	ori = env;
	cpy = malloc(sizeof(t_env));
	cpy->key = ft_strdup(ori->key);
	cpy->value = ft_strdup(ori->value);
	return (cpy);
}

/**
 * @brief Free out the malloced space of each env var
*/
void	clear_env_var(void *content)
{
	t_env	*env;

	env = content;
	free(env->key);
	free(env->value);
	free(env);
}
