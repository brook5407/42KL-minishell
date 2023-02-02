/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:32:50 by chchin            #+#    #+#             */
/*   Updated: 2023/02/02 17:57:33 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	call_exit(t_minishell *ms, char **cmds)
{
	(void)cmds;
	free(ms->prompt);
	free_env(ms->envp);
	exit(0);
}
