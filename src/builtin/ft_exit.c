/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 09:28:17 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/30 12:27:31 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	check_chars(char *str)
{
	int	i;

	if (((str[0] == '-' || str[0] == '+') && str[1]) || ft_isdigit(str[0]))
	{
		i = 1;
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

static int	get_ll(unsigned long long *num, int *sign, char *str)
{
	if (!check_chars(str) || ft_strlen(str) > 20)
		return (0);
	*num = ft_atoull(str, sign);
	if ((*num > MAX_LL_INT && *sign == 1) || \
		(*num - 1 > MAX_LL_INT && *sign == -1))
		return (0);
	return (1);
}

static void	exit_process(long long err_exit)
{
	ft_putstr_fd("exit\n", 1);
	exit((unsigned int)err_exit % 256);
}

void	ft_exit(char **args)
{
	unsigned long long	num;
	int					sign;

	if (!args[1])
		exit_process(g_exit);
	sign = 1;
	if (!get_ll(&num, &sign, args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(args[1], 1);
		ft_putendl_fd(": numeric argument required", 1);
		exit_process(255);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 1);
		g_exit = 1;
		return ;
	}
	exit_process(num * sign);
}
