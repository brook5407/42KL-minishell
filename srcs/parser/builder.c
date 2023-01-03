/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:53:38 by wricky-t          #+#    #+#             */
/*   Updated: 2023/01/03 13:46:58 by wricky-t         ###   ########.fr       */
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

void	print_grammar(t_grammar type)
{
	if (type == START)
		printf("[START]\n");
	else if (type == POST_RDR)
		printf("[POST_RDR]\n");
	else if (type == CMD_ONLY)
		printf("[CMD_ONLY]\n");
	else if (type == FREE_FORM)
		printf("[FREE_FORM]\n");
}

void	print_rdr_type(t_token_type type)
{
	if (type == HEREDOC)
		printf("[HEREDOC]: ");
	else if (type == APPEND)
		printf("[APPEND]: ");
	else if (type == RDRIN)
		printf("[RDRIN]: ");
	else if (type == RDROUT)
		printf("[RDROUT]: ");
}

void	show_cmd_block(void *content)
{
	t_cmd	*cmd;
	t_list	*args;
	t_file	*file;
	t_list	*infile;
	t_list	*outfile;
	
	cmd = content;
	printf("= = = = = = = = = =\n");
	printf("THIS CMD BLOCK AT: %p\n", cmd);
	printf("CMD: %s\n", cmd->cmd_name);
	printf("\n");
	printf("ARGS:\n");
	args = cmd->args;
	if (args == NULL)
		printf("%s\n\n", NULL);
	else
	{
		while (args != NULL)
		{
			printf(" | %s\n", (char *)args->content);
			args = args->next;
		}
	}
	printf("\n");
	printf("INFILE:\n");
	infile = cmd->infile;
	if (infile == NULL)
		printf("%s\n", NULL);
	else
	{
		while (infile != NULL)
		{
			file = infile->content;
			printf(" | ");
			print_rdr_type(file->rdr_type);
			printf("%s\n", file->name);
			infile = infile->next;
		}
	}
	printf("\n");
	printf("OUTFILE:\n");
	outfile = cmd->outfile;
	if (outfile == NULL)
		printf("%s\n", NULL);
	else
	{
		while (outfile != NULL)
		{
			file = outfile->content;
			printf(" | ");
			print_rdr_type(file->rdr_type);
			printf("%s\n", file->name);
			outfile = outfile->next;
		}
	}
	printf("= = = = = = = = = =\n");
}

void	add_as_args(t_parser *hlpr, char *value)
{
	ft_lstadd_back(&hlpr->cmd->args, ft_lstnew(ft_strdup(value)));
}

void	add_as_cmd(t_minishell *ms, t_parser *hlpr, t_token *token)
{
	char	*value;

	if (token->type == EXT_CMD)
		value = ft_strdup(get_ext_full_path(ms, token->value));
	else
		value = ft_strdup(token->value);
	hlpr->cmd->cmd_name = value;
	add_as_args(hlpr, value);
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

void	add_as_cmd_block(t_minishell *ms, t_parser *hlpr)
{
	ft_lstadd_back(&ms->cmds, ft_lstnew(hlpr->cmd));
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
		add_as_args(hlpr, token->value);
	else if ((gram == START || gram == FREE_FORM)
		&& (type == RDRIN || type == RDROUT
			|| type == HEREDOC || type == APPEND))
		add_as_redirection(hlpr, token->type);
	else if (gram == POST_RDR)
		add_as_file(hlpr, token->value);
	if (gram == FREE_FORM && type == PIPE)
		add_as_cmd_block(ms, hlpr);
}
