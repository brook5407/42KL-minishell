/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:22:20 by chchin            #+#    #+#             */
/*   Updated: 2022/12/09 15:31:39 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_minishell *ms)
{
	t_list	*envp;
	t_env	*env_var;

	envp = ms->envp;
	if (envp != NULL)
	{
		env_var = envp->content;
		free(env_var->key);
		free(env_var->value);
		free(envp->content);
		envp = envp->next;
	}
}