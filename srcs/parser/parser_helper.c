/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:45:50 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/27 21:32:50 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Heredoc will be evaluated first no matter what.
 * 
 * It's safe to say that when it's Heredoc, insert it at the start of the list.
 * Let's say the command is:
 * cat | ls -la << eof
 * 
 * The list should be:
 * 1. Heredoc
 *    delimiter: eof
 * 2. cat
 * 3. ls
 *    args: -la
 */

/**
 * GRAMMAR
 * 1. After a string, can be anything
 *    CODE:
 *    reset_all_type(), status = 1
 * 
 * 2. At the start of a grammar, the acceptable tokens are:
 *      i.	 Redirection (Append, in, out)
 *      ii.	 Heredoc
 *      iii. CMD / EXT_CMD
 * 	  turn off PIPE & STR
 *    If it's a str at the very first, error: invalid command
 *    If it's a |, error: parse error
 *    CODE:
 *    reset_all_type(), status = 1
 *    toggle_type(PIPE) // should be 0
 *    toggle_type(STR) // should be 0 
 * 
 * 3. After a pipe, reset the grammar
 *    CODE:
 *    reset_all_type(), status = 1
 *    toggle_type(PIPE) // should be 0
 *    toggle_type(STR) // should be 0
 * 
 * 4. After a redirection must be a filename
 *      i.   Redirection out/append -> outfile
 *      ii.  Redirection in-> infile
 *    Don't care it's a CMD, EXT_CMD, or STR. Treat that as a file.
 *    CODE:
 *    reset_all_type(), status = 0
 *    toggle_type(CMD) // should be 1 
 *    toggle_type(EXT_CMD) // should be 1 
 *    toggle_type(STR) // should be 1
 * 
 * 5. After a file could be anything.
 *    CODE:
 *    if cmd_name == NULL
 *          reset_all_type(), status = 0
 *          toggle_type(CMD) // should be 1
 *          toggle_type(EXT_CMD) // should be 1
 *    else
 *          reset_all_type(), status = 1.
 * 
 * 6. In the case where redirection go first, the following must be a
 *    file. If the next token of file is a CMD or EXT_CMD, then it's valid.
 *    If it's a string, error: invalid command.
 *    CODE:
 *    if cmd_name == NULL
 *          reset_all_type(), status = 0
 *          toggle_type(CMD) // should be 1
 *          toggle_type(EXT_CMD) // should be 1
 *    else
 *          reset_all_type(), status = 1.   
 * 
 * 7. After a CMD or EXT_CMD, whatever behind it will be valid.
 *    CODE:
 *    reset_all_type(), status = 1
*/
