/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:22:20 by chchin            #+#    #+#             */
/*   Updated: 2022/12/11 18:04:53 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_var(t_env *env_var)
{
	free(env_var->key);
	free(env_var->value);
	free(env_var);
}

void	free_env(t_list	*envp)
{
	t_env	*env_var;

	if (envp != NULL)
	{
		env_var = envp->content;
		free_env_var(env_var);
		envp = envp->next;
	}
}

void	free_arry(char **arry)
{
	while (*arry)
		free(*arry++);
	free(arry);
}
