/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:11:31 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/30 14:56:17 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Check if a token is in a set of quote
 * 
 * Return 1 if yes, 0 otherwise.
 * 
 * The reason to check this is because to make minishell to accept command
 * that is wrapped inside a set of quote like:
 * "echo" - Valid command (echo)
 * "EcHo" - Valid command (echo)
 * 'ECHo' - Valid command (echo)
 * "/bin/cat" - Valid external command (cat)
*/
int	token_in_quote(char *token)
{
	char	*quote;

	quote = ft_strchr(QUOTES, *token);
	if (quote == NULL)
		return (0);
	if (*(token + (ft_strlen(token) - 1)) == *quote)
		return (1);
	return (0);
}

/**
 * @brief Check if a token only consists of operators, so that
 * 		  won't mistakenly check string as operator
*/
int	only_contain_operator(char *token)
{
	while (*token != '\0')
	{
		if (ft_strchr(OPERATORS, *token) == NULL)
			return (0);
		token++;
	}
	return (1);
}

t_token_type	get_operator_type(char *opr)
{
	if (ft_strcmp(opr, ">>") == 0)
		return (APPEND);
	if (ft_strcmp(opr, "<<") == 0)
		return (HEREDOC);
	if (ft_strcmp(opr, ">") == 0)
		return (RDROUT);
	if (ft_strcmp(opr, "<") == 0)
		return (RDRIN);
	if (ft_strcmp(opr, "|") == 0)
		return (PIPE);
	return (UNKNOWN);
}

/**
 * @brief Join the path of the external command before comparing
 * 
 * As mentioned below, the user can have three way to execute an external
 * command:
 * 1. Just the name of the command (ex: cat)
 * 2. Fully specify the path to command (ex: /bin/cat)
 * 3. Partially specify the path to command but must in that directory
 *    (ex: munki/AppUsaged, but have to be at /usr/local/)
 * 
 * This function is to join the path based on the way the user specify.
 * For:
 * 1. Join the path of PATH to the token
 * 2. Assuming it's a valid executable path, so just strdup
 * 3. Append the value of PWD infront of token
*/
char	*get_extcmd_path(char *path, char *token)
{
	char	*joined;
	char	*start;
	char	*occurrence;

	joined = NULL;
	start = token;
	occurrence = ft_strchr(start, '/');
	if (occurrence == NULL)
	{
		joined = ft_strjoin(path, "/");
		return (ft_strjoin_free(joined, token));
	}
	return (ft_strdup(token));
}

char	*get_ext_full_path(t_minishell *ms, char *token)
{
	int			i;
	char		*path_value;
	char		**paths;
	char		*ext;
	struct stat	file_stat;

	path_value = get_env_value(ms, "PATH");
	if (path_value == NULL)
		return (NULL);
	i = -1;
	paths = ft_split(path_value, ':');
	while (paths[++i] != NULL)
	{
		ext = get_extcmd_path(paths[i], token);
		if (access(ext, X_OK) == 0
			&& stat(ext, &file_stat) == 0 && S_ISREG(file_stat.st_mode))
		{
			ft_freestrarr(paths);
			return (ext);
		}
		free(ext);
	}
	ft_freestrarr(paths);
	return (NULL);
}
