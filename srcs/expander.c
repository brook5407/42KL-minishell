/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:31:40 by chchin            #+#    #+#             */
/*   Updated: 2022/12/21 10:35:22 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	key_len(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			break ;
		i++;
	}
	return (i);
}

char	*expand_var(t_minishell *ms, char *str)
{
	size_t	len;
	char	*key;
	char	*value;

	len = key_len(str);
	key = ft_strndup(str, len);
	value = get_env_value(ms, key);
	free(key);
	if (!value)
	{
		if (!len)
			return (ft_strjoin("$", str));
		return (ft_strdup(str + len));
	}
	else
		return (ft_strjoin(value, str + len));
}

char	*convrt_env_var(t_minishell *ms, char *str)
{
	char	*new_str;
	char	*token;
	char	*tmp;

	token = ft_strtok(str, "$");
	if (str[0] != '$')
	{
		new_str = strdup(token);
		token = ft_strtok(NULL, "$");
	}
	else if (str[0] == '$' && str[1] == '\0')
		new_str = ft_strdup("$");
	else
		new_str = ft_strdup("");
	while (token != NULL)
	{
		tmp = expand_var(ms, token);
		new_str = ft_strjoin_free(new_str, tmp);
		free(tmp);
		token = ft_strtok(NULL, "$");
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

char	*expand(t_minishell *ms, char *str)
{
	char	*tmp;

	tmp = str;
	str = convrt_env_var(ms, str);
	printf("Before: %s, after: %s\n", tmp, str);
	free(tmp);
	return(str);
}