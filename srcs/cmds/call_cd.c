/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:11:18 by chchin            #+#    #+#             */
/*   Updated: 2022/12/07 11:00:55 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int call_cd(char *args)
{
	char	cur_path[BUFFSIZE];

	if (!args)
		args = getenv("HOME");
	else if (args[0] == '-')
		args = getenv("OLDPWD");
	if(chdir(args) != 0)
		perror("cd");
	if (getcwd(cur_path, BUFFSIZE) == NULL)
		perror("cd");
	// if (strncmp(args, "-", 1))
		printf("%s\n", cur_path);
	return (0);
}