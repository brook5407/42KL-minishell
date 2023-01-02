/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:53:38 by wricky-t          #+#    #+#             */
/*   Updated: 2023/01/02 14:54:37 by wricky-t         ###   ########.fr       */
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

// void	add_as_redirection(t_parser *hlpr, t_token_type type)
// {
// 	if (type == APPEND || type == HEREDOC)
// 		hlpr->cmd->rdr_mode = type;
// 	hlpr->rdr_mode = type;
// }

/**
 * TODO: Need to discuss with Brook
 */
// void	add_as_file(t_parser *hlpr, char *value)
// {
// 	t_token_type	rdr;

// 	// rdr = hlpr->cmd->rdr_mode;
// 	if (rdr == RDROUT || rdr == APPEND)
// 		ft_lstadd_back(hlpr->cmd->outfile, ft_lstnew(value));
// 	else if (rdr == RDRIN || rdr == HEREDOC)
// 		ft_lstadd_back(hlpr->cmd->infile, ft_lstnew(value));
// }

// void	add_as_args(t_parser *hlpr, char *value)
// {
// 	ft_lstadd_back(hlpr->cmd->args, ft_lstnew(value));
// }

/**
 * @brief Help building the cmd_list by checking the current grammar and token
 */
void	builder_helper(t_minishell *ms, t_parser *hlpr, t_token *token)
{
	t_grammar		gram;
	t_token_type	type;

	gram = hlpr->curr_grammar;
	type = token->type;
	(void)ms;
	if ((gram == START || gram == CMD_ONLY) && (type == CMD || type == EXT_CMD))
	{
		hlpr->has_cmd_name = 1;
		hlpr->cmd->cmd_name = token->value;
	}
	if (gram == POST_RDR)
		printf("add as file\n");
	if ((gram == START || gram == FREE_FORM)
		&& (type == RDRIN || type == RDROUT
			|| type == HEREDOC || type == APPEND))
		printf("add as rdr\n");
	if ((gram == START || gram == FREE_FORM)
		&& (type == CMD || type == EXT_CMD || type == STR))
		printf("add as args\n");
	if (gram == FREE_FORM && type == PIPE)
		printf("marks the end of one command block\n");
}
