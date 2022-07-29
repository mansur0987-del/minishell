/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:30:38 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/28 23:42:50 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int	valid_arg(char *arg)
{
	char	*invalid_chars;
	int		len;
	int		i;

	i = 0;
	invalid_chars = ".~,@#%^-+={}[]";
	len = ft_strlen(invalid_chars);
	while (i < len)
	{
		if (ft_strchr(arg, invalid_chars[i]))
			return (0);
		i++;
	}
	if (ft_isdigit(arg[0]))
		return (0);
	len = ft_strlen(arg);
	i = -1;
	while (++i < len)
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
	return (1);
}

void	arg_error(char *command, char *param)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(param, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
	g_exit = 1;
}
