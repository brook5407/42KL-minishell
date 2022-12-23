/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:30:09 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/23 12:16:45 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * There are two expansion needed for our minishell.
 * 1. Tilde expansion "~" (extra)
 * 2. Shell parameter expansion "$" together with quote expansion
 * 
 * If the variable is not found in the environment variables, keep the original
 * form and just return it.
 * If the token merely just a "$", return the original token as well.
 * 
 * Naming convention for env var, ALPHABETS, DIGITS and UNDERSCORE. Other than
 * these, the character are not part of the VAR name.
 */

/**
 * TILDE EXPANSION
 * 
 * If a word begins with an unquoted tilde character (‘~’), all of the characters
 * up to the first unquoted slash (or all characters, if there is no unquoted
 * slash) are considered a tilde-prefix. If HOME is unset, the home directory
 * of the user executing the shell is substituted instead. Otherwise, the
 * tilde-prefix is replaced with the home directory associated with the specified
 * login name.
 * 
 * 1. ~
 * 	  The value of $HOME
 * 2. ~/foo
 * 	  $HOME/foo
 * 
 * Idea:
 * Replace ~ to $HOME, and shell expansion will then do the shell expansion
 */

/**
 * SHELL PARAMETER EXPANSION
 * 
 * 1. If the PARAMETER is not in the list yet, keep the ori name, return it.
 * 2. If the PARAMETER is in the list, get the value, replace it with the value.
 * 		a. If the value is NULL, join with nothing. NOTE: "" and NULL is two
 *         different thing.
 * 
 * To get the PARAMETER name, follow the naming convention for PARAMETER, when
 * encounter an invalid character for PARAMETER name, stop, that marks the end
 * of a ENV PARAMETER, get the value.
 * 
 * Whatever is between "", expand. Whatever is between '', don't expand. Quotes
 * are first come first serve. So if:
 * "'$TEST'", expand. Quotes in between will be treated as normal characters.
 * '"$TEST"', don't expand. Same as above for the quotes in between.
 * 
 * When getting the shell parameter, the delimiter between parameter is $, '\0'.
 * If the parameter does not have a valid parameter name, remove it.
 */

/**
 * Expander should works like so:
 * 1. Check if there's a tilde in the token, expand it to "$HOME". (ON-HOLD)
 * 2. Expand the shell parameter.
*/

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
char	*expand_parameter(t_minishell *ms, char *token, int ignore)
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
			value = get_parameter_value(ms, extract_ids(&token));
			str = join_expanded(str, prefix, value);
			prefix = token;
			continue ;
		}
		if (*token == '\'' && ignore == 1)
			token = ft_strchr(token + 1, '\'');
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
	char	*str;

	temp = token;
	if (*token == '\'' || (*token == '"' && ft_strchr(token, '$') == NULL))
	{
		str = ft_strndup(token + 1, ft_strlen(token + 1) - 1);
		free(temp);
		return (str);
	}
	token = ft_strndup(token + 1, ft_strlen(token + 1) - 1);
	str = expand_parameter(ms, token, 0);
	free(token);
	free(temp);
	return (str);
}

void	expander_process(t_minishell *ms, char **str, char **token, char **pre)
{
	char	*copy;
	char	*prefix;
	char	*next;

	copy = *token;
	prefix = *pre;
	prefix = ft_strndup(prefix, copy - prefix);
	if (*copy == '\'' || *copy == '"')
	{
		next = ft_strchr(copy + 1, *copy) + 1;
		*str = join_expanded(*str, prefix,
				expand_quotes(ms, ft_strndup(copy, next - copy)));
		copy = next;
	}
	else
		*str = join_expanded(*str, prefix,
				get_parameter_value(ms, extract_ids(&copy)));
	prefix = copy;
	*token = copy;
	*pre = prefix;
}

void	expander(t_minishell *ms, char **token)
{
	char	*copy;
	char	*prefix;
	char	*str;

	copy = *token;
	str = NULL;
	prefix = copy;
	while (*copy != '\0')
	{
		if (*copy == '$' || *copy == '\'' || *copy == '"')
		{
			expander_process(ms, &str, &copy, &prefix);
			continue ;
		}
		copy++;
	}
	if (str == NULL)
		return ;
	*token = ft_strjoin_free(str, ft_strndup(prefix, copy - prefix));
}
