/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:38:49 by chchin            #+#    #+#             */
/*   Updated: 2023/01/09 14:54:13 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**lst_to_array(t_list *lst)
{
	int		i;
	int		size;
	char	**array;

	size = ft_lstsize(lst);
	array = malloc(sizeof(char *) * size);
	if (!array)
		return (NULL);
	i = 0;
	while (lst)
	{
		array[i++] = lst->content;
		lst = lst->next;
	}
	array[i] = NULL;
	return (array);
}
