/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:23:31 by brook             #+#    #+#             */
/*   Updated: 2022/12/13 21:31:33 by brook            ###   ########.fr       */
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

// Function to sort the linked list by using bubble sort method.
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

void	print_export(t_minishell *ms)
{
	t_list	*export;
	t_list	*tmp;
	t_env	*env_var;

	export = ft_lstmap(ms->envp, cpy_env, NULL);
	ft_lstsort(&export);
	while (export != NULL)
	{
		env_var = export->content;
		if (env_var->value[0])
			printf("declare -x %s=\"%s\"\n", env_var->key, env_var->value);
		else
			printf("declare -x %s\n", env_var->key);
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
	char	*key;
	char	*value;

	if (!s)
		print_export(ms);
	else
	{
		value = ft_strchr(++s, '=');
		if (value == NULL)
		{
			value = strdup("");
			key = ft_strdup(s);
		}
		else
		{
			key = ft_strndup(s, value - s);
			value = ft_strdup(value + 1);
		}
		edit_env_val(ms, key, value);
	}
	return (0);
}
