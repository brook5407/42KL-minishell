/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:45:50 by wricky-t          #+#    #+#             */
/*   Updated: 2023/02/07 19:09:17 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Utils to free iofile struct
 * 
 * 1. Free the file name
 * 2. Free the iofile struct
 */
void	free_iofile(void *content)
{
	t_file	*iofile;

	iofile = content;
	free(iofile->name);
	free(iofile);
}

/**
 * @brief Free the cmd block
 *
 * 1. Free the cmd name
 * 2. Free the args list
 * 3. Free the infile list
 * 4. Free the outfile list
 */
void	free_cmd_block(void *content)
{
	t_cmd	*cmd;

	cmd = content;
	free(cmd->cmd_name);
	ft_lstclear(&cmd->args, free);
	ft_lstclear(&cmd->infile, free_iofile);
	ft_lstclear(&cmd->outfile, free_iofile);
	free(cmd);
}

/**
 * @brief Free the parser
 * 
 * 1. Free the cmd name
 * 2. Free the args list
 * 3. Free the infile list
 * 4. Free the outfile list
 */
void	free_parser(t_parser *hlpr)
{
	free(hlpr->cmd.cmd_name);
	ft_lstclear(&hlpr->cmd.args, free);
	ft_lstclear(&hlpr->cmd.infile, free_iofile);
	ft_lstclear(&hlpr->cmd.outfile, free_iofile);
}

/**
 * @brief Initialize parser helper
 *
 * @param hlpr pointer to parser helper
 */
void	init_parser(t_parser *hlpr)
{
	hlpr->curr_grammar = START;
	hlpr->cmd.cmd_name = NULL;
	hlpr->cmd.args = NULL;
	hlpr->cmd.infile = NULL;
	hlpr->cmd.outfile = NULL;
	apply_grammar(hlpr, START);
}

void	free_cmd_data(t_cmd *cmd)
{
	free(cmd->cmd_name);
	ft_lstclear(&cmd->args, free);
	ft_lstclear(&cmd->infile, free_iofile);
	ft_lstclear(&cmd->outfile, free_iofile);
}
