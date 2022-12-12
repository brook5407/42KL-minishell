/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:57:16 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/12 20:52:31 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief To recognize if the token is a external command or not.
 * 
 * External command can be executed in two ways:
 * 1. [EXT_CMD] args
 * 2. /full/path/to/[EXT_CMD] args
*/
int	recognize_external1(t_minishell *ms, char *token)
{
	char			*path;
	char			**paths;
	char			**temp_paths;
	DIR				*dir;
	struct dirent	*entity;

	path = get_env_value(ms, "PATH");
	paths = ft_split(path, ':');
	temp_paths = paths;
	while (*paths != NULL)
	{
		 // try open the directory
		dir = opendir(*paths);
		// if directory not exist, go to the next PATH
		if (dir == NULL)
			continue ;
		// compare each file in the directory see if one match
		while (1)
		{
			// read the directory
			entity = readdir(dir);
			// if reach the end of the directory
			if (entity == NULL)
				break ;
			// compare the file with the command name
			if (entity->d_type == DT_REG && !ft_strcmp(token, entity->d_name))
			{
				printf("[EXT_CMD]: %s\n", entity->d_name);
				return (1);	
			}
		}
		paths++;
	}
	ft_freestrarr(temp_paths);
	return (0);
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
 * 
 * TODO: To handle this: ./, ../, ../../../
*/
char	*join_path(t_minishell *ms, char *path, char *token)
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
	if (occurrence == start)
		return (ft_strdup(token));
	else if (occurrence > start)
	{
		joined = ft_strjoin(get_env_value(ms, "PWD"), "/");
		return (ft_strjoin_free(joined, token));
	}
	return (NULL);
}

/**
 * @brief To recognize if the token is a external command or not.
 * 
 * External command can be executed in two ways:
 * 1. [EXT_CMD] args
 * 2. /full/path/to/[EXT_CMD] args
 * 3. path/to/[EXT_CMD] args (part of the path, if the user is at the
 *    directory, then the command can be executed)
 * 
 * To be safe, it's better to get the full path of the command before
 * checking if the file exists and can be executed.
 * After that, just check if the file exists and can be executed. If so,
 * store it into command list as a EXT_CMD and return 1.
 * 
 * The return value indicates whether a token has been recognized or not.
 * 1 = Yes, 0 = No
*/
int	recognize_external(t_minishell *ms, char *token)
{
	int		i;
	char	**paths;
	char	*extcmd;

	i = -1;
	paths = ft_split(get_env_value(ms, "PATH"), ':');
	while (paths[++i] != NULL)
	{
		extcmd = join_path(ms, paths[i], token);
		if (access(extcmd, F_OK | X_OK) == 0)
		{
			printf("[EXT_CMD]: %s\n", extcmd);
			free(extcmd);
			return (1);
		}
		free(extcmd);
	}
	ft_freestrarr(paths);
	system("leaks -q minishell");
	return (0);
}

/**
 * Recognize cmd
 * @brief Identify whether the token is a cmd
 * 
 * The priority will be like this:
 * 1. Check if the cmd is a minishell built-ins command
 * 2. Check if the cmd is a program and can be found on the system
 * 
 * 1. Check if the token is inside a set of quote. If yes, when strdup, don't
 *    duplicate the quotes. If no, do normal strdup.
 * 2. To make minishell to accept uppercase command, we need to convert it
 *    into lowercase first. Then use the lowercase version to check if it's a
 *    built-in or external command.
 * 3. To check if it's a builtin, strcmp with each of the builtins command name
 *    in the list. If yes, add to data structure.
 * 4. 
 */
int	recognize_cmd(t_minishell *ms, char *token)
{
	int		i;
	char	*token_copy;

	i = -1;
	if (token_in_quote(token) == 1)
		token_copy = ft_strndup(token + 1, ft_strlen(token + 1) - 1);
	else
		token_copy = ft_strdup(token);
	token_copy = ft_strlower(token_copy);
	while (ms->builtins[++i] != NULL)
	{
		if (ft_strcmp(ms->builtins[i], token_copy) == 0)
		{
			printf("[CMD]: %s\n", token);
			free(token_copy); // might not need to free this
			return (1);
		}
	}
	if (recognize_external(ms, token_copy) == 1)
	{
		free(token_copy); // might not need to free this
		return (1);
	}
	free(token_copy);
	return (0);
}

/**
 * Operators are: | (Pipes), < (Redirect input), > (Redirect output),
 * 				  << (Heredoc) & >> (Append)
*/
int	recognize_operator(t_minishell *ms, char *token)
{
	int	i;

	i = -1;
	(void)ms;
	if (only_contain_operator(token) == 0)
		return (0);
	printf("token OP: %s\n", token);
	if (ft_strcmp(token, "|")) // PIPE
	{
		printf("[PIPE]: %s\n", token);
		return (1);
	}
	else if (ft_strcmp(token, ">")) // Redirect output
	{
		printf("[RDROUT]: %s\n", token);
		return (1);
	}
	else if (ft_strcmp(token, "<")) // Redirect input
	{
		printf("[RDRIN]: %s\n", token);
		return (1);
	}
	else if (ft_strcmp(token, ">>")) // Append
	{
		printf("[APPEND]: lalalalalal%s\n", token);
		return (1);
	}
	else if (ft_strcmp(token, "<<")) // Heredoc
	{
		printf("[HEREDOC]: %s\n", token);
		return (1);
	}
	printf("INVALID OPERATOR!\n");
	return (0);
	// printf("i: %d\n", i);
	// must be the first character, because tokenizer stops at operator
}

void	recognize_token(t_minishell *ms, char *token)
{
	// Recognize command (Built-ins & External)
	if (recognize_cmd(ms, token) == 0)
	{
		if (recognize_operator(ms, token) == 0)
		{
			// is a string literal, directly store as string
		}
		// an operator has been recognized
	}
	// a command has been recognized
	
	// at this point, the token has been recognized and store inside the linked list
	// nothing to do after this point forward
}
