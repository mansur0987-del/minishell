/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoull.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:55:48 by nmordeka          #+#    #+#             */
/*   Updated: 2022/02/18 13:25:03 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

static int	is_space(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || \
		c == '\r' || c == '\v' || c == '\f')
		return (1);
	else
		return (0);
}

unsigned long long	ft_atoull(char *str, int *sign)
{
	int					i;
	unsigned long long	result;

	i = 0;
	result = 0;
	*sign = 1;
	while (is_space(str[i]))
		i = i + 1;
	if (str[i] == '-')
		*sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i = i + 1;
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - '0';
		i = i + 1;
	}
	return (result);
}
