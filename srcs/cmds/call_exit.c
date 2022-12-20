/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:32:50 by chchin            #+#    #+#             */
/*   Updated: 2022/12/20 20:57:42 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	call_exit(t_minishell *ms, char *cmds)
{
	free(cmds);
	free_env(ms->envp);
	system("leaks -q minishell");
	exit(0);
}
