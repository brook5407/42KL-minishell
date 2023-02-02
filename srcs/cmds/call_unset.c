/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:14:28 by chchin            #+#    #+#             */
/*   Updated: 2023/02/02 14:35:25 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	del_env_var(t_minishell *ms, t_env *env)
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
	t_env	*env;

	if (*key == NULL)
		return ;
	while (*key != NULL)
	{
		if (is_valid_id(*key) == 0)
		{
			show_error(INVALID_ID_UNS, *(key++));
			continue ;
		}
		env = load_env_var(ms->envp, *key);
		if (env == NULL)
		{
			key++;
			continue ;
		}
		del_env_var(ms, env);
		key++;
	}
}
