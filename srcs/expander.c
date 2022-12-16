/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:31:40 by chchin            #+#    #+#             */
/*   Updated: 2022/12/16 16:32:41 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_env_var(char *str)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	// if (ft_strcmp("key", "~"))
		// return(getenv("HOME"))
	
	value = get_env_value(ms, key);
	return(value);
}

char	handle_quote(char *arg)
{
	char	*str;
	char	*tmp;
	char	*value;

	if (arg[0] == '"' && arg[ft_strlen(arg)] == '"')
	{
		str = ft_strndup(arg, ft_strlen(arg - 2));
		tmp = ft_strchr(str, '$');
		if (tmp == NULL)
			return (str);
		
	}
	else if (arg[0] == '\'' && arg[ft_strlen(arg)] == '\'')
		str = ft_strndup(arg, ft_strlen(arg - 2));
}