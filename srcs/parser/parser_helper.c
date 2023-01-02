/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:45:50 by wricky-t          #+#    #+#             */
/*   Updated: 2023/01/02 13:46:52 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * TODO:
 * 1. Grammar checker
 * 		- check if the token is expected.
 * 			- if it's expected, store to cmd_list
 *          - if not expected, free the current node, move on to the next
 *            command block (look for pipe if have)
 * 2. Builder functions - help building the cmd_list, based on the current
 *    grammar.
 * 	  START: if it's redirection / heredoc, do what POST_RDR do.
 *           if command name, store to cmd name
 *    FREE_FORM: if string, store to argument
 * 				 if it's redirection do what POST_RDR do
 *               if it's cmd/ext cmd, store to argument as well. this is
 *               because it's impossible for the builder to store as cmd name
 *               when in free form.
 *    POST_RDR: if it's heredoc / append mode, need to specify
 *    CMD_ONLY: store to cmd name
*/

// void	builder_helper(t_minishell *ms){}
