/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:53:38 by wricky-t          #+#    #+#             */
/*   Updated: 2023/01/10 19:41:01 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * DRAFT
 * What to do when grammar is,
 * 1. START
 *    Acceptable tokens:
 * 			- CMD 	: as cmd, and args
 * 			- E_CMD : as cmd, and args
 * 			- STR 	: as args
 * 			- RIN 	: as rdr
 * 			- ROUT 	: as rdr
 * 			- HDOC 	: as rdr
 * 			- APPD 	: as rdr
 * 2. FREE_FORM
 * 	  Acceptable tokens:
 * 			- CMD 	: as args
 * 			- E_CMD : as args
 * 			- STR 	: as args
 * 			- RIN 	: as rdr
 * 			- ROUT 	: as rdr
 * 			- HDOC 	: as rdr
 * 			- APPD 	: as rdr
 * 			- PIPE 	: mark the end of one cmd block
 * 3. POST_RDR
 * 	  Acceptable tokens:
 * 			- CMD 	: as file
 * 			- E_CMD : as file
 * 			- STR 	: as file
 * 4. CMD_ONLY
 * 	  Acceptable tokens:
 * 			- CMD 	: as cmd
 * 			- E_CMD : as cmd
 */

/**
 * REFACTORED VERSION
 * What to do when grammar is,
 * 1. ADD AS CMD
 *    GRAMMAR: START, CMD_ONLY
 *    TOKEN_TYPE: CMD, E_CMD
 * 2. Add as args
 * 	  GRAMMAR: START, FREE_FORM
 * 	  TOKEN_TYPE: (STR)-START, (CMD, E_CMD, STR)-FREE_FORM
 * 3. Add as file
 * 	  GRAMMAR: POST_RDR
 * 	  TOKEN_TYPE: CMD, E_CMD, STR
 * 4. Add as rdr
 * 	  GRAMMAR: START, FREE_FORM
 * 	  TOKEN_TYPE: RIN, ROUT, HDOC, APPD
 * 5. Mark the end of a command block
 *    GRAMMAR: FREE_FORM
 *    TOKEN_TYPE: PIPE
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
	hlpr->cmd->cmd_name = value; // this is as cmd name
	ft_lstadd_back(&hlpr->cmd->args, ft_lstnew(ft_strdup(value)));
	// this is as args, strdup another one is because to prevent double free
}

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
		iolst = &hlpr->cmd->infile;
	else if (type == APPEND || type == RDROUT)
		iolst = &hlpr->cmd->outfile;
	ft_lstadd_back(iolst, ft_lstnew(iofile));
	hlpr->rdr_mode = type;
}

void	add_as_file(t_parser *hlpr, char *value)
{
	t_list	*last_added;
	t_list	*iolst;
	t_file	*iofile;

	iolst = NULL;
	if (hlpr->rdr_mode == HEREDOC || hlpr->rdr_mode == RDRIN)
		iolst = hlpr->cmd->infile;
	else if (hlpr->rdr_mode == APPEND || hlpr->rdr_mode == RDROUT)
		iolst = hlpr->cmd->outfile;
	last_added = ft_lstlast(iolst);
	if (last_added == NULL)
		return ;
	iofile = last_added->content;
	iofile->name = ft_strdup(value);
}

void	add_as_cmd_block(t_minishell *ms, t_parser *hlpr, int reset)
{
	t_cmd	*copy;

	copy = copy_cmd_block(hlpr->cmd);
	// printf("COPY\n");
	// show_cmd_block(copy); /** TESTING: check if copy is successful and is at different address */
	// printf("ORI\n");
	// show_cmd_block(hlpr->cmd); /** TESTING: original cmd block */
	ft_lstadd_back(&ms->cmds, ft_lstnew(copy));
	if (reset == 1)
		init_parser(hlpr);
}

/**
 * @brief Help building the cmd_list by checking the current grammar and token
 */
void	builder_helper(t_minishell *ms, t_parser *hlpr, t_token *token)
{
	t_grammar		gram;
	t_token_type	type;

	gram = hlpr->curr_grammar;
	type = token->type;
	if ((gram == START || gram == CMD_ONLY) && (type == CMD || type == EXT_CMD)
		&& hlpr->cmd->cmd_name == NULL)
		add_as_cmd(ms, hlpr, token);
	else if ((gram == START || gram == FREE_FORM)
		&& (type == CMD || type == EXT_CMD || type == STR))
		ft_lstadd_back(&hlpr->cmd->args, ft_lstnew(ft_strdup(token->value)));
	else if ((gram == START || gram == FREE_FORM)
		&& (type == RDRIN || type == RDROUT
			|| type == HEREDOC || type == APPEND))
		add_as_redirection(hlpr, token->type);
	else if (gram == POST_RDR)
		add_as_file(hlpr, token->value);
	if (gram == FREE_FORM && type == PIPE)
		add_as_cmd_block(ms, hlpr, 1);
}
