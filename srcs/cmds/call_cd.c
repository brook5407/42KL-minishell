/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:11:18 by chchin            #+#    #+#             */
/*   Updated: 2022/12/07 16:54:39 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



int call_cd(t_list *envp, char *args)
{
	char	cur_path[BUFFSIZE];
	t_env	*env_var;

	if (!args)
	{
		env_var = load_env_var(envp, "HOME");
		args = env_var->value;
	}
	else if (args[0] == '-')
	{
		env_var = load_env_var(envp, "OLDPWD");
		args = env_var->value;
	}
	getcwd(cur_path, BUFFSIZE);
	edit_env_val(envp, "OLDPWD", cur_path);
	if(chdir(args) != 0)
		perror("cd");
	if (getcwd(cur_path, BUFFSIZE) == NULL)
		perror("cd");
	// if (strncmp(args, "-", 1))
		printf("%s\n", cur_path);
	return (0);
}