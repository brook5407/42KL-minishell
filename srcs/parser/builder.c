/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:53:38 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/30 18:16:36 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_as_redirection()
{}

void	add_as_file()
{}

void	add_as_args()
{}

void	builder_helper(t_minishell *ms, t_parse_hlpr *hlpr, t_token *token)
{
	t_grammar		gram;
	t_token_type	t_type;
	
	(void)ms;
	gram = hlpr->curr_grammar;
	t_type = token->type;
	if ((gram == CMD_ONLY || gram == START) && (t_type == CMD || t_type == EXT_CMD))
	{
		// add to args, set cmd_name to the value
		hlpr->has_cmd_name = 1;
	}
	if (gram == POST_RDR)
	{
		// need to check the redirection direction (in / out) and mode (append / heredoc)
		printf("Adding \"%s\" as file\n", token->value);
	}
	if (gram == FREE_FORM)
		printf("it is what it is\n");
		// it is what it is
}

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

/**
 * @brief Help building the cmd_list by checking the current grammar and token
 */
void	builder_helper(t_minishell *ms, t_parse_hlpr *hlpr, t_token *token)
{
	t_grammar		gram;
	t_token_type	type;

	gram = hlpr->curr_grammar;
	type = token->type;
	if ((gram == START || gram == CMD_ONLY) && (type == CMD || type == EXT_CMD))
	{
		hlpr->has_cmd_name = 1;
		hlpr->cmd->cmd_name = token->value;
	}
	if (gram == POST_RDR)
		add_as_file();
	if ((gram == START || gram == FREE_FORM)
		&& (type == RDRIN || type == RDROUT || type == HEREDOC || type == APPEND))
		add_as_redirection();
	if ((gram == START || gram == FREE_FORM)
		&& (type == CMD || type == EXT_CMD || type == STR))
		add_as_args();
	if (gram == FREE_FORM && type == PIPE)
		printf("marks the end of one command block\n");
}
