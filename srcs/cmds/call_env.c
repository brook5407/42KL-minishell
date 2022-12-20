/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:57:46 by chchin            #+#    #+#             */
/*   Updated: 2022/12/20 19:31:36 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	call_env(t_minishell *ms)
{
	t_list	*envp;
	t_env	*env_var;

	envp = ms->envp;
	while (envp != NULL)
	{
		env_var = envp->content;
		if (env_var->value[0])
			printf("%s=%s\n", env_var->key, env_var->value);
		envp = envp->next;
	}
	return (0);
}
