/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:25:36 by chchin            #+#    #+#             */
/*   Updated: 2023/02/06 13:40:29 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*load_env_var(t_list *envp, char *var)
{
	t_env	*env_var;

	while (envp != NULL)
	{
		env_var = envp->content;
		if (ft_strcmp(var, env_var->key) == 0)
			return (env_var);
		envp = envp->next;
	}
	return (NULL);
}

void	edit_env_val(t_minishell *ms, char *key, char *value)
{
	t_env	*env;

	env = load_env_var(ms->envp, key);
	if (env == NULL)
		add_env_var(ms, key, value);
	else if (value == NULL && env->value != NULL)
	{
		free(value);
		free(key);
	}
	else
	{
		free(env->value);
		env->value = value;
		free(key);
	}
}

char	*get_env_value(t_minishell *ms, char *key)
{
	t_list	*envp;
	t_env	*env_var;

	envp = ms->envp;
	while (envp != NULL)
	{
		env_var = envp->content;
		if (ft_strcmp(key, env_var->key) == 0)
			return (env_var->value);
		envp = envp->next;
	}
	return (NULL);
}

char	**get_env_arry(t_minishell *ms)
{
	t_list	*envp;
	t_env	*env_var;
	char	**env_arry;
	char	*tmp;
	int		i;

	i = 0;
	env_arry = malloc(sizeof(char *) * (ft_lstsize(ms->envp) + 1));
	envp = ms->envp;
	while (envp != NULL)
	{
		env_var = envp->content;
		if (env_var->value != NULL && env_var->value[0] != '\0')
		{
			tmp = ft_strjoin(env_var->key, "=");
			env_arry[i++] = ft_strjoin_free(tmp, env_var->value);
		}
		envp = envp->next;
	}
	env_arry[i] = NULL;
	return (env_arry);
}
