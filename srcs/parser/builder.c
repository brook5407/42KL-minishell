/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:53:38 by wricky-t          #+#    #+#             */
/*   Updated: 2023/01/12 16:27:54 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Add input as a cmd name
 * 
 * 1. If the token type is EXT_CMD, get the full executable path
 * 	  else the value will be token->value
 * 2. Set cmd_name to value
 * 3. Add cmd_name as one of the argument as well
 */
void	add_as_cmd(t_minishell *ms, t_parser *hlpr, t_token *token)
{
	char	*value;
	char	*ext_path;

	if (token->type == EXT_CMD)
	{
		ext_path = get_ext_full_path(ms, token->value);
		value = ft_strdup(ext_path);
		free(ext_path);
	}
	else
		value = ft_strdup(token->value);
	hlpr->cmd.cmd_name = value;
	ft_lstadd_back(&hlpr->cmd.args, ft_lstnew(ft_strdup(value)));
}

/**
 * @brief Add as redirection, create a node for the file name
 * 
 * 1. Create a iofile node
 * 2. HEREDOC or RDRIN => infile
 *    APPEND or RDROUT => outfile
 * 3. Add the newly created node to the iofile list
 * 4. Set the rdr_mode to the rdr type so that add_as_file
 *    will know where to put the file name
*/
void	add_as_redirection(t_parser *hlpr, t_token_type type)
{
	t_file	*iofile;
	t_list	**iolst;

	iolst = NULL;
	iofile = malloc(sizeof(t_file));
	if (iofile == NULL)
	{
		perror("Initialize iofile failed!\n");
		return ;
	}
	iofile->rdr_type = type;
	iofile->name = NULL;
	if (type == HEREDOC || type == RDRIN)
		iolst = &hlpr->cmd.infile;
	else if (type == APPEND || type == RDROUT)
		iolst = &hlpr->cmd.outfile;
	ft_lstadd_back(iolst, ft_lstnew(iofile));
	hlpr->rdr_mode = type;
}

/**
 * @brief Add as input as file name
 * 
 * 1. Check the rdr_mode
 * 2. HEREDOC or RDRIN => infile
 *    APPEND or RDROUT => outfile
 * 3. Get the last added node
 * 4. If the last added node is NULL (which is impossible), return
 * 5. Set the content of the last node to the file name.
 */
void	add_as_file(t_parser *hlpr, char *value)
{
	t_list	*last_added;
	t_list	*iolst;
	t_file	*iofile;

	iolst = NULL;
	if (hlpr->rdr_mode == HEREDOC || hlpr->rdr_mode == RDRIN)
		iolst = hlpr->cmd.infile;
	else if (hlpr->rdr_mode == APPEND || hlpr->rdr_mode == RDROUT)
		iolst = hlpr->cmd.outfile;
	last_added = ft_lstlast(iolst);
	if (last_added == NULL)
		return ;
	iofile = last_added->content;
	iofile->name = ft_strdup(value);
}

/**
 * @brief Add the processed cmd block to the cmd list
 * 
 * 1. Create a new cmd block
 * 2. Set the properties of the new cmd block by pointing the pointers
 * 	  to the respective address
 * 3. Add as a node to the cmd list
 * 4. Reset the parser by letting all the pointer variable points to NULL
 */
void	add_as_cmd_block(t_minishell *ms, t_parser *hlpr)
{
	t_cmd	*cmd;

	if (hlpr->cmd.cmd_name == NULL && hlpr->cmd.args == NULL
		&& hlpr->cmd.infile == NULL && hlpr->cmd.outfile == NULL)
		return ;
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return ;
	cmd->cmd_name = hlpr->cmd.cmd_name;
	cmd->args = hlpr->cmd.args;
	cmd->infile = hlpr->cmd.infile;
	cmd->outfile = hlpr->cmd.outfile;
	ft_lstadd_back(&ms->cmds, ft_lstnew(cmd));
	init_parser(hlpr);
}

/**
 * @brief Help building the cmd_list by checking the current grammar and token
 */
void	builder(t_minishell *ms, t_parser *hlpr, t_token *token)
{
	t_grammar		gram;
	t_token_type	type;

	gram = hlpr->curr_grammar;
	type = token->type;
	if (gram == FREE_FORM && type == PIPE)
		add_as_cmd_block(ms, hlpr);
	if ((gram == START || gram == FREE_FORM) && (type == CMD || type == EXT_CMD)
		&& hlpr->cmd.cmd_name == NULL)
		add_as_cmd(ms, hlpr, token);
	else if ((gram == START || gram == FREE_FORM)
		&& (type == CMD || type == EXT_CMD || type == STR))
		ft_lstadd_back(&hlpr->cmd.args, ft_lstnew(ft_strdup(token->value)));
	else if ((gram == START || gram == FREE_FORM)
		&& (type == RDRIN || type == RDROUT
			|| type == HEREDOC || type == APPEND))
		add_as_redirection(hlpr, token->type);
	else if (gram == POST_RDR)
		add_as_file(hlpr, token->value);
}
