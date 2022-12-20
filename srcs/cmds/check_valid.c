/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:03:25 by chchin            #+#    #+#             */
/*   Updated: 2022/12/14 12:36:26 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_valid(char *cmds, char *args)
{
	int	i;

	i = 0;
	if (!ft_isalpha(*args) && *args != '_')
	{
		printf("%s: '%s': not a valid identifier\n", cmds, args);
		return (1);
	}
	while (args[i])
	{
		if (ft_isalnum(args[i]) || args[i] == '_')
			i++;
		else
		{
			printf("%s: '%s': not a valid identifier\n", cmds, args);
			return (1);
		}
	}
	return (0);
}
