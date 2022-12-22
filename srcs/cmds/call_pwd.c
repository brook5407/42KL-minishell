/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:18:37 by chchin            #+#    #+#             */
/*   Updated: 2022/12/22 18:16:08 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	call_pwd(t_minishell *ms)
{
	char	cwd[FILE_MAX];

	(void)ms;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("pwd");
	ft_putendl_fd(cwd, 1);
	return (0);
}
