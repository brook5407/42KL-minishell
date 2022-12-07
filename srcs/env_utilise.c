/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utilise.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:25:36 by chchin            #+#    #+#             */
/*   Updated: 2022/12/07 16:23:18 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*load_env_var(const t_list *envp, char *var)
{
	t_env *env_var;

	while (envp != NULL)
	{
		env_var = envp->content;
		if (env_var->key == var)
			return (env_var);
		envp->next;
	}
	return (NULL);
}

void edit_env_val(const t_list *envp, char *var, char *value)
{
	t_env *env;

	env = load_env_var(envp, var);
	if (env)
		env->value = value;
	// else
		// add_env
}
