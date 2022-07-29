/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_ret.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:28:46 by nmordeka          #+#    #+#             */
/*   Updated: 2022/02/24 21:34:35 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_ret(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			write(1, "\n", 1);
			return (130);
		}
		if (WTERMSIG(status) == 3)
		{
			write(1, "Quit: 3\n", ft_strlen("Quit: 3\n"));
			return (131);
		}
		if (WTERMSIG(status) == 15)
			return (143);
	}
	return (WEXITSTATUS(status));
}
