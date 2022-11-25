/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brook <brook@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:14:02 by brook             #+#    #+#             */
/*   Updated: 2022/11/24 22:17:59 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CLOSE	"\001\033[0m\002"
# define BOLD	"\001\033[1m\002"
# define BEGIN(x,y)	"\001\033["#x";"#y"m\002]"

#include <stdlib.h>
#include <readline/history.h>

#endif
