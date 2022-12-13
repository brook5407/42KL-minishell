/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:23:31 by brook             #+#    #+#             */
/*   Updated: 2022/12/13 13:47:34 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Function to swap the keys and values of two elements in the linked list
static void	ft_lstswap(t_list *list_a, t_list *list_b)
{
	t_env	*tmp;

	tmp = list_a->content;
	list_a->content = list_b->content;
	list_b->content = tmp;
}

// Function to apply to each element of the list
static void	*cpy_env(void *env)
{
	t_env	*orig;
	t_env	*copy;

	orig = env;
	copy = malloc(sizeof(t_env));
	copy->key = ft_strdup(orig->key);
	copy->value = ft_strdup(orig->value);
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
			if (ft_strcmp(tmp_a->key, tmp_b->key) < 0)
				ft_lstswap(a, b);
			b = b->next;
		}
		a = a->next;
	}
}

void print_export(t_minishell *ms)
{
	t_list	*export;
	t_list	*tmp;
	t_env	*env_var;

	export = ft_lstmap(ms->envp, cpy_env, del_env);
	ft_lstsort(&export);
	while (export != NULL)
	{
		env_var = export->content;
		if (env_var->value)
			printf("declare -x %s=%s\n", env_var->key, env_var->value);
		free(env_var->key);
		free(env_var->value);
		free(env_var);
		tmp = export->next;
		free(export);
		export = tmp;
	}
}
int	call_export(t_minishell *ms, char *s)
{
	// t_env	*env_var;
	// char	*key;
	// char	*value;
	

	if (!s)
		print_export(ms);
	// else
	// {
	// 	value = ft_strchr(s, '=') + 1;
	// 	key = ft_strlcpy()
	// }
	return (0);
}
