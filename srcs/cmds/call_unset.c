/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:14:28 by chchin            #+#    #+#             */
/*   Updated: 2022/12/20 19:31:36 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_pair(t_minishell *ms, t_env *env)
{
	t_list	*prev;
	t_list	*tmp;

	prev = ms->envp;
	if (prev->content == env)
	{
		ms->envp = prev->next;
		return ;
	}
	while (prev->next != NULL)
	{
		if (prev->next->content == env)
		{
			tmp = prev->next;
			prev->next = prev->next->next;
			free_env_var(env);
			free(tmp);
			return ;
		}
		prev = prev->next;
	}
}

int	call_unset(t_minishell *ms, char *key)
{
	t_env	*env_load;

	if (check_valid("unset", ++key) == 1)
		return (0);
	env_load = load_env_var(ms->envp, key);
	if (env_load == NULL)
		return (0);
	env_pair(ms, env_load);
	return (0);
}
