/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:18:37 by chchin            #+#    #+#             */
/*   Updated: 2022/12/20 19:31:36 by brook            ###   ########.fr       */
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
