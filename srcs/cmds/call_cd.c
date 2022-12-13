/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:11:18 by chchin            #+#    #+#             */
/*   Updated: 2022/12/13 11:26:45 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *check_path(t_minishell *ms, char *path)
{
	t_env	*env_var;

	if (!path || !ft_strcmp(path, "~"))
	{
		env_var = load_env_var(ms->envp, "HOME");
		if (env_var == NULL)
		{
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
			return (NULL);
		}
		return(ft_strdup(env_var->value));
	}
	else if (!ft_strcmp(path, "-"))
	{
		env_var = load_env_var(ms->envp, "OLDPWD");
		if (env_var == NULL)
		{
			ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO);
			return (NULL);
		}
		ft_putendl_fd(env_var->value, 1);
		return(ft_strdup(env_var->value));
	}
	else
	{
		return(ft_strdup(path));
	}
}

static void	edit_oldpwd(t_minishell *ms)
{
	t_env	*pwd;
	
	pwd = load_env_var(ms->envp, "PWD");
	if (pwd == NULL)
		edit_env_val(ms, "OLDPWD", NULL);
	else
		edit_env_val(ms, "OLDPWD", pwd->value);
}

int call_cd(t_minishell *ms, char *path)
{
	char	*cur_path;

	cur_path = check_path(ms, path);
	if (cur_path == NULL)
		return (0);
	if(chdir(cur_path) != 0)
		perror("cd");
	else
	{
		edit_oldpwd(ms);
		free(cur_path);
		cur_path = getcwd(NULL, 0);
		edit_env_val(ms, "PWD", cur_path);
	}
	free(cur_path);
	return (0);
}