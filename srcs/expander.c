/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:31:40 by chchin            #+#    #+#             */
/*   Updated: 2022/12/20 12:32:53 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	key_len(char *str)
{
	int	i;

	i = 0;
//	if (ft_strlen(str) < 1)
//		return (0);
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
			break ;
	}
	return (i);
}

//char	*check_env_var(t_minishell *ms, char *str)
//{
//	size_t	len;
//	char	*begin;
//	char	*var;
//	char	*new_str;
//
//	new_str = strdup(str);
//	while (ft_strchr(new_str, '$'))
//	{
//		var = ft_strchr(new_str, '$');
//		begin = ft_strndup(new_str, new_str - var);
//		var = ft_strndup(var, key_len(var));
//	}
//	return (new_str);
//}

char	*check_env_var(t_minishell *ms, char *str)
{
	char	**split;
	size_t	len;
	char	*var;
	char	*value;
	char	*new_str;

	split = ft_split(str, '$');
	new_str = NULL;
	while (*split)
	{
		len = key_len(*split);
		var = ft_strndup(*split, len);
		value = get_env_value(ms, var);
		free(var);
		var = *split;
		if (value)
			*split = ft_strjoin(value, *split + len);
		else
			*split = ft_strdup(*split + len);
		free(var);
		if (!new_str)
			new_str = ft_strdup(*split);
		else
			new_str = ft_strjoin_free(new_str, *split);
		free(*split++);
	}
	return (new_str);
}

//char	*handle_quote(char *arg)
//{
//	char	*str;
//	char	*tmp;
//	char	*value;
//
//	if (arg[0] == '"' && arg[ft_strlen(arg)] == '"')
//	{
//		str = ft_strndup(arg, ft_strlen(arg - 2));
//		tmp = ft_strchr(str, '$');
//		if (tmp == NULL)
//			return (str);
//	}
//	else if (arg[0] == '\'' && arg[ft_strlen(arg)] == '\'')
//		str = ft_strndup(arg, ft_strlen(arg - 2));
//}

void	expand(t_minishell *ms, char *str)
{
	char	*test;

	test = check_env_var(ms, str);
	printf("Before: %s, after: %s\n", str, test);
}