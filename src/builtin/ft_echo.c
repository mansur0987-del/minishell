/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:22:27 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/16 20:51:39 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

static int	set_n_flag(char **arg)
{
	int	i;

	i = 0;
	while (arg[i + 1] && !(ft_strcmp(arg[i + 1], "-n")))
		i++;
	return (i);
}

void	ft_echo(char **str)
{
	int	n_flag;
	int	i;

	n_flag = set_n_flag(str);
	i = 1 + n_flag;
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		if (str[i + 1] && str[i][0] != '\0' && str[i + 1][0] != '\0')
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	g_exit = 0;
}
