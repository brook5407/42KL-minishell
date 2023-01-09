/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:14:28 by chchin            #+#    #+#             */
/*   Updated: 2023/01/09 14:26:36 by chchin           ###   ########.fr       */
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

void	call_unset(t_minishell *ms, char **key)
{
	t_env	*env_load;

	if (check_valid("unset", *key) == 1)
		return ;
	env_load = load_env_var(ms->envp, *key);
	if (env_load == NULL)
		return ;
	env_pair(ms, env_load);
}
