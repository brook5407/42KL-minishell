/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brook <brook@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:23:31 by brook             #+#    #+#             */
/*   Updated: 2022/12/12 13:11:46 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Function to swap the keys and values of two elements in the linked list
static void	ft_lstswap(t_list *list)
{
	char	*key;
	char	*value;
	t_env	*a;
	t_env	*b;

	a = list->content;
	b = list->next->content;
	key = a->key;
	value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = key;
	b->value = value;
}

// Function to apply to each element of the list
static void	*cpy_env(void *env)
{
	t_env	*orig;
	t_env	*copy;

	orig = env;
	copy = malloc(sizeof(t_env));
	copy->key = strdup(orig->key);
	copy->value = strdup(orig->value);
	return (copy);
}

// Function to delete elements when the linked list is no longer needed
static void	del_env(void *env)
{
	t_env	*elem;

	elem = env;
	free(elem->key);
	free(elem->value);
	free(elem);
}

// Function to sort the linked list in acceding order by using bubble sort method.
static void	ft_lstsort(t_list **list)
{
	t_list	*a;
	t_list	*b;
	t_env	*tmp_a;
	t_env	*tmp_b;

	a = *list;
	while (a != NULL)
	{
		b = *list;
		while (b->next != NULL)
		{
			tmp_a = a->content;
			tmp_b = b->content;
			if (ft_strcmp(tmp_b->key, tmp_a->key) > 0)
				ft_lstswap(b);
			b = b->next;
		}
		a = a->next;
	}
}

int	call_export(t_minishell *ms, char *key)
{
	t_list	*export;
	t_env	*env_var;

	if (!key)
	{
		export = ft_lstmap(ms->envp, cpy_env, del_env);
		ft_lstsort(&export);
		while (export != NULL)
		{
			env_var = export->content;
			if (env_var->value)
				printf("declare -x %s=%s\n", env_var->key, env_var->value);
			export = export->next;
		}
		free_env(export);
	}
	return (0);
}
