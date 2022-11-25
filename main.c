/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brook <brook@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:20:47 by brook             #+#    #+#             */
/*   Updated: 2022/11/24 22:26:06 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline(BEGIN(49, 34)"Minishell $ "CLOSE);
		if (!line)
		{
			printf("allocation error\n");
			exit(1);
		}
		add_history(line);
		free(line);
	}
}