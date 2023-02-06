/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:30:09 by wricky-t          #+#    #+#             */
/*   Updated: 2023/02/06 21:01:46 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Expand the shell parameter to its value
 * 
 * The token should contain shell parameter. Acceptable format:
 * 1. Hello$TEST
 * 2. Hello World $TEST
 * 3. $TEST$TEST$TEST
 * 4. $TEST"$TEST"$TEST
 * 5. $TEST'$TEST'$TEST
 * 
 * Be aware that, this function should not call when the string
 * is inside of a set of single quote. Otherwise the parameter
 * will be expanded and cause unexpected result.
 * 
 * Prefix: The string before a shell parameter
 * Remaining: The remaining string after the loop is completed
 * 
 * Iterate through the token, when encounter a '$', extract the prefix.
 * Get the extract the id and get its value. Strjoin the prefix and id value
 * to the final str.
 * 
 * Extract id will modify the token to point to the next starting point of id.
 * So, use continue to skip to the next iteration.
 * 
 * After the loop exits, extract the remaining str and append to the final
 * string.
 * 
 * Return the string at the end.
 */
char	*expand_parameter(t_minishell *ms, char *token)
{
	char	*prefix;
	char	*str;
	char	*value;
	char	*remaining;

	str = NULL;
	prefix = token;
	while (*token != '\0')
	{
		if (*token == '$')
		{
			prefix = ft_strndup(prefix, token - prefix);
			value = get_parameter_value(ms, extract_ids(&token, 0));
			str = join_expanded(str, prefix, value);
			prefix = token;
			continue ;
		}
		token++;
	}
	remaining = ft_strndup(prefix, token - prefix);
	str = ft_strjoin_free(str, remaining);
	free(remaining);
	return (str);
}

/**
 * @brief Expand whatever it's in a set of quote.
 * @param token The string in a set of quote. The acceptable format:
 * 				1. "HEY", "$1HEY$TEST", "$1 $TEST"
 * 				2. 'HEY', '$1HEY$TEST', '$1 $TEST'
 * 
 * In shell, in a pair of single quote ('), every character inside will
 * just be treated as normal character. For double quote ("), expand
 * the dollar sign (shell parameter), if have.
 * 
 * The string (param: token) that been passed into this function must start
 * and end with either double or single quote. Both quote must be same. Due
 * to that, to determine whether to expand the string or not becomes easier.
 * 
 * First, check if the starting quote is a single quote. If yes, return
 * whatever is inside that pair of single quote.
 * 
 *      'Hello $TEST'
 * start ↑         ↑ end
 * 
 * Even though we need to expand whatever is inside double quote if needed, but
 * if there's no '$' inside, it's the same process as handling single quote.
 * 
 * If the token can pass the condition above, it means that the string is
 * confirmed to be in a pair of double quote and will have shell parameter
 * to expand. Extract the string inside the double quote and pass it into
 * expand_parameter.
 * 
 * After expand_parameter done its work, it will return the final string.
 */
char	*expand_quotes(t_minishell *ms, char *token)
{
	char	*temp;
	char	*value;

	temp = token;
	if (*token == '\'' || (*token == '"' && ft_strchr(token, '$') == NULL))
		value = ft_strndup(token + 1, ft_strlen(token + 1) - 1);
	else
	{
		token = ft_strndup(token +1, ft_strlen(token + 1) - 1);
		value = expand_parameter(ms, token);
		free(token);
	}
	free(temp);
	return (value);
}

/**
 * @brief The process of expander
 * 
 * 1. Get the prefix. Prefix is just the string before the expanded value.
 * 	  Example: ec$B, "ec" is the prefix in this case.
 * 2. If the current str starts with single or double quote, pass it to
 * 	  expand quote to the the expaneded value. Before that, the str that
 * 	  start and end with quote must be extracted out. The pointer should
 *    point to the next extract point after the value expanded.
 * 3. If the current str nor start or end with quote, it means it must
 *    be a normal expansion. Get the parameter value and join it together
 *    with the final str.
 * 
 * Noted that this function directly modify the pointer of the str. So if
 * this function is called inside a loop, it should call continue after this
 * function exit (if the loop is post-increment). So that it won't miss
 * any of the character.
 */
void	expander_process(t_minishell *ms, char **str, char **token, char **pre)
{
	char	*copy;
	char	*prefix;
	char	*next;
	char	*value;

	copy = *token;
	prefix = *pre;
	prefix = ft_strndup(prefix, copy - prefix);
	if (*copy == '\'' || *copy == '"')
	{
		next = ft_strchr(copy + 1, *copy) + 1;
		value = expand_quotes(ms, ft_strndup(copy, next - copy));
		*str = join_expanded(*str, prefix, value);
		// free(value);
		copy = next;
	}
	else
		*str = join_expanded(*str, prefix,
				get_parameter_value(ms, extract_ids(&copy, 1)));
	prefix = copy;
	*token = copy;
	*pre = prefix;
}

/**
 * @brief Expander. Expand the quotes and shell parameter ($).
 * 
 * @param token The pointer to the original string (double pointer)
 * @param type The expansion type (PARAM, INQUOTE, BOTH)
 * 
 * Iterate through a string and perform expansion. Can either choose
 * to expand certain type based on the "type" value.
 * Available type:
 * 1. PARAM - Expand only the shell parameter that are not in quotes
 * 2. INQUOTE - Expand only the shell parameter in quotes, value in
 *              single and double quotes.
 * 3. BOTH - Do all.
 * 
 * If type is PARAM, when encounter a quote, the pointer to string will
 * advance to the end of the quote.
 * If type is BOTH or INQUOTES, when encounter a '$' that is not in a
 * quote, don't expand it.
 * 
 * After everything is done, extract the remaining character and join it
 * together with the final string.
 */
void	expander(t_minishell *ms, char **token, t_expand_type type)
{
	char	*copy;
	char	*prefix;
	char	*str;
	char	*remaining;

	copy = *token;
	str = NULL;
	prefix = copy;
	while (*copy != '\0')
	{
		if (type == PARAM && ft_strchr(QUOTES, *copy))
			copy = ft_strchr(copy + 1, *copy);
		else if ((*copy == '$' && (type == PARAM || type == BOTH))
			|| *copy == '\'' || *copy == '"')
		{
			expander_process(ms, &str, &copy, &prefix);
			continue ;
		}
		copy++;
	}
	if (str == NULL)
		return ;
	remaining = ft_strndup(prefix, copy - prefix);
	*token = ft_strjoin_free(str, remaining);
	free(remaining);
}
