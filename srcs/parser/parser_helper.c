/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:45:50 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/28 13:14:02 by wricky-t         ###   ########.fr       */
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
