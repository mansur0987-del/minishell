/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:51:03 by armaxima          #+#    #+#             */
/*   Updated: 2022/03/16 16:24:33 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_puterror_1(char *str, t_shell *shell)
{
	shell->err_cod = 258;
	g_exit = 258;
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	ft_putstr_fd(str, 1);
	free(str);
	ft_putstr_fd("'\n", 1);
	return (2);
}
