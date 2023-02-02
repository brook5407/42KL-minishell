/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:14:28 by chchin            #+#    #+#             */
/*   Updated: 2023/02/02 17:45:05 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Delete environment variable out from the env list and join back
 *        the list.
 * 
 * @details
 * Check if the target node is the current (head). If yes, free the node and
 * its content. Return to caller afterward.
 * 
 * If it's not the head, iterate through the list until we found the target.
 * When found, free the node and its content. Return to caller afterward.
*/
static void	del_env_var(t_minishell *ms, t_env *env)
{
	t_list	*curr;
	t_list	*tmp;

	curr = ms->envp;
	if (curr->content == env)
	{
		ms->envp = curr->next;
		free_env_var(env);
		free(curr);
		return ;
	}
	while (curr->next != NULL)
	{
		if (curr->next->content == env)
		{
			tmp = curr->next;
			curr->next = curr->next->next;
			free_env_var(env);
			free(tmp);
			return ;
		}
		curr = curr->next;
	}
}

/**
 * @brief Call builtin (unset)
 * 
 * Unset environment variable. Delete the specified environment variable.
 * 
 * @details
 * When passing in to the function, the key array has been incremented to skip
 * over the cmd name. If the current element in the key array is NULL, return
 * back to the caller. Else, iterate through the keys.
 * 
 * While iterate through the keys, check if the specified key is a valid id or
 * not. If it's not a valid one, skip over this key and display error. Else,
 * load the environment variable. If the environment variable is NULL, meaning
 * that key does not existed. Skip over current key.
 * 
 * If the key is valid and existed, delete it from the environment variable list.
 */
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
