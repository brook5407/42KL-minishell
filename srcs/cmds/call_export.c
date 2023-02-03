/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:23:31 by brook             #+#    #+#             */
/*   Updated: 2023/02/03 12:29:34 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Function to swap the keys and values of two elements in the linked list
// static void	ft_lstswap(t_list *list_a, t_list *list_b)
// {
// 	t_env	*tmp;

// 	tmp = list_a->content;
// 	list_a->content = list_b->content;
// 	list_b->content = tmp;
// }

// Function to apply to each element of the list
// static void	*cpy_env(void *env)
// {
// 	t_env	*orig;
// 	t_env	*copy;

// 	orig = env;
// 	copy = malloc(sizeof(t_env));
// 	copy->key = ft_strdup(orig->key);
// 	copy->value = ft_strdup(orig->value);
// 	return (copy);
// }

// Function to sort the linked list by using bubble sort method.
// void	ft_lstsort(t_list **list)
// {
// 	t_list	*a;
// 	t_list	*b;
// 	t_env	*tmp_a;
// 	t_env	*tmp_b;

// 	a = *list;
// 	while (a != NULL)
// 	{
// 		b = *list;
// 		while (b->next != NULL)
// 		{
// 			tmp_a = a->content;
// 			tmp_b = b->content;
// 			if (ft_strcmp(tmp_a->key, tmp_b->key) < 0)
// 				ft_lstswapcontent(a, b);
// 			b = b->next;
// 		}
// 		a = a->next;
// 	}
// }

// Function to print out every node in enviroment list follow by export format
// int	print_export(t_minishell *ms, char *s)
// {
// 	t_list	*export;
// 	t_list	*tmp;
// 	t_env	*env_var;

// 	if (s)
// 		return (1);
// 	export = ft_lstmap(ms->envp, cpy_env, NULL);
// 	ft_lstsort(&export);
// 	while (export != NULL)
// 	{
// 		env_var = export->content;
// 		if (env_var->value[0])
// 			printf("declare -x %s=\"%s\"\n", env_var->key, env_var->value);
// 		else
// 			printf("declare -x %s\n", env_var->key);
// 		free(env_var->key);
// 		free(env_var->value);
// 		free(env_var);
// 		tmp = export->next;
// 		free(export);
// 		export = tmp;
// 	}
// 	return (0);
// }

/** TODO: Refactor this */
// void	call_export2(t_minishell *ms, char **args)
// {
// 	char	*key;
// 	char	*value;

// 	if (*args == NULL)
// 		return (print_export(ms));
// 	while (*args != NULL)
// 	{
// 		value = ft_strchr(*args, '=');
// 		if (value == NULL)
// 		{
// 			key = ft_strdup(*args);
// 			value = strdup("");
// 		}
// 		else
// 		{
// 			key = ft_strndup(*args, value - *args);
// 			value = ft_strdup(value + 1);
// 		}
// 		if (!check_valid("export", key))
// 			edit_env_val(ms, key, value);
// 		else
// 		{
// 			free(key);
// 			free(value);
// 		}
// 		args++;
// 	}
// }

/**
 * @brief Helper function to sort the env var. Sort in ascending order (ASCII)
*/
static int	compare_env(void *cont1, void *cont2)
{
	t_env	*a;
	t_env	*b;

	a = cont1;
	b = cont2;
	return (ft_strcmp(a->key, b->key));
}

/**
 * @brief Sort and print the environment variables.
 * 
 * @details
 * The format of each environment variable should be in a format of:
 * 		`declare -x key=value`
 * 				OR
 * 		`declare -x key` (if there is no value)
 * 
 * This function will first create a copy of env vars and sort it. Iterate
 * through the list and print it out in the format above. Free out the list
 * before return to caller.
*/
static void	print_export(t_minishell *ms)
{
	t_list	*export;
	t_list	*tmp_head;
	t_env	*env_var;

	export = ft_lstmap(ms->envp, cpy_env, NULL);
	ft_lstbubblesort(&export, compare_env);
	tmp_head = export;
	while (export != NULL)
	{
		env_var = export->content;
		if (env_var->value == NULL)
			ft_printf("declare -x %s\n", env_var->key);
		else if (env_var->value[0] == '\0')
			ft_printf("declare -x %s=\"\"\n", env_var->key);
		else
			printf("declare -x %s=\"%s\"\n", env_var->key, env_var->value);
		export = export->next;
	}
	ft_lstclear(&tmp_head, clear_env_var);
}

/**
 * @brief Extract the key and value pair out of the arg
 * 
 * @details
 * Locate the start of the value using strchr. If there's no '=', meaning
 * there's no value for this export key. In this case, copy the key and
 * return back. Please noted that value will be NULL in this case.
 * 
 * If there's a '=', meaning this key has a value and we need to add it
 * to the env list. Extract the key using strndup, and strdup for the value.
*/
static void	extract_key_value(char *arg, char **key, char **value)
{
	*value = ft_strchr(arg, '=');
	if (*value == NULL)
	{
		*key = ft_strdup(arg);
		return ;
	}
	*key = ft_strndup(arg, *value - arg);
	*value = ft_strdup(*value + 1);
}

/**
 * @brief Call the export builtin
 * 
 * @details
 * If call export without args, print all the environment list in a format.
 * (Please refer to print_export() function to know more about the format)
 * If there's args, iterate through the args and extract the key and value.
 * Check if the id is valid afterward, if the id is not valid, show error
 * and free the key and value. Else, either add or edit the env var using
 * edit_env_val.
*/
void	call_export(t_minishell *ms, char **args)
{
	char	*key;
	char	*value;

	if (*args == NULL)
		return (print_export(ms));
	while (*args != NULL)
	{
		extract_key_value(*args, &key, &value);
		if (is_valid_id(key) == 0)
		{
			show_error(INVALID_ID_EXP, *(args++));
			free(key);
			free(value);
			continue ;
		}
		edit_env_val(ms, key, value);
		args++;
	}
}
