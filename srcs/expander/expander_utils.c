/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 21:53:40 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/23 21:03:45 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Check if the given id is a valid parameter name that follows the 
 *        naming convention of shell parameter.
 * 
 * @param id Should only consists of the name of the id, excluding the '$'
 * 
 * @note Naming convention:
 * 1. Acceptable characters: UNDERSCORE (_), ALPHABETS (A-Za-z), DIGITS (0-9)
 * 2. Parameter should not start with DIGITS & any other unacceptable characters.
 * 3. Parameter can start with ALPHABETS or UNDERSCORE.
 * 4. What's follow after the first character does not matter as long as
 * 	  it's constructed using the acceptable characters.
 * 
 * This function first check if the first character follows the guideline.
 * Then check the rest of the characters to make sure follows the naming
 * convention. If the function is able to iterate through the id string,
 * meaning it's valid.
*/
int	is_valid_id(char *id)
{
	if (ft_isalpha(*id) == 0 && *id != '_')
		return (0);
	while (*(++id) != '\0')
	{
		if (ft_isalnum(*id) == 0 && *id != '_')
			return (0);
	}
	return (1);
}

/**
 * @brief Extract the id or id chain.
 * 
 * @param str: The string inside the double quote, because only double quote
 *             should expand the ids, not single quotes. Using double point,
 * 	           so that the str can point to the next substring to extract.
 * 
 * Output will be either:
 * 1. $HEY$HO$HE$HA - id chain
 * 2. $SINGLE - single id
 * 
 * If the input is something like this:
 * 1. "$HEY$HO      $BABA". This function will extract "$HEY$HO" and return it
 * .  then mark the starting point of next substring to "      $BABA"
 * 
 * Notice that this function will also consider the naming convention of shell
 * parameter. This is to prevent the function to extract characters that are
 * not part of the id.
 */
char	*extract_ids(char **str, int ignore)
{
	char	*ids;
	char	*next;
	int		i;

	next = (*str + 1);
	i = 0;
	if (ft_isdigit(*next) == 1)
		next++;
	else if ((*next == '\'' || *next == '"') && ignore == 1)
		i = 1;
	else if (*next == '$')
		next++;
	else
	{
		while (*next != '\0')
		{
			if ((ft_isalnum(*next) == 0 && *next != '_'))
				break ;
			next++;
		}	
	}
	ids = ft_strndup((*str), next - (*str) + i);
	*str = next;
	return (ids);
}

/**
 * @brief Get the shell parameter value
 * 
 * @param token string that in a form of $VAR
 * 
 * Get the value of the parameter from environment variable.
 * If the parameter is not set, meaning NULL, return value should be an
 * empty string. The return value of this function is not malloced.
 */
char	*get_parameter_value(t_minishell *ms, char *token)
{
	char	*id;
	char	*value;

	id = ft_strchr(token, '$') + 1;
	if (*id == '$')
		value = "";
	else if (*id == '\0')
		value = "$";
	else
		value = get_env_value(ms, id);
	if (value == NULL)
		value = "";
	free(token);
	return (value);
}

char	*join_expanded(char *str, char *prefix, char *value)
{
	char	*suffix;

	suffix = ft_strjoin_free(prefix, value);
	if (str == NULL)
		str = ft_strjoin("", suffix);
	else
		str = ft_strjoin_free(str, suffix);
	free(suffix);
	return (str);
}

void	remove_slash(char **str)
{
	char	*token;
	char	*prefix;
	char	*new;
	char	*value;

	token = *str;
	prefix = *str;
	new = NULL;
	while (*token != '\0')
	{
		if (*token == '\\')
		{
			prefix = ft_strndup(prefix, token - prefix);
			value = ft_strndup(token + 1,
					ft_strchr(token + 1, *token) - token - 1);
			new = join_expanded(new, prefix, value);
			token = ft_strchr(token + 1, *token) + 1;
			prefix = token;
			continue ;
		}
		token++;
	}
	free(*str);
	*str = ft_strjoin_free(new, ft_strndup(prefix, token - prefix));
}
