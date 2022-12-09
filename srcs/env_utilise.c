/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utilise.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:25:36 by chchin            #+#    #+#             */
/*   Updated: 2022/12/09 16:52:17 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*load_env_var(t_list *envp, char *var)
{
	t_env *env_var;

	while (envp != NULL)
	{
		env_var = envp->content;
		if (ft_strcmp(var, env_var->key) == 0)
			return (env_var);
		envp = envp->next;
	}
	return (NULL);
}

void edit_env_val(t_minishell *ms, char *key, char *value)
{
	t_env	*env;

	env = load_env_var(ms->envp, key);
	if (!env)
		add_env_var(ms, key, value);
	else
	{
		free(env->value);
		// printf("change key %s, value %s\n", key, value);
		env->value = ft_strdup(value);
		// printf("after duplicate %s\n", env->value);
	}
}
