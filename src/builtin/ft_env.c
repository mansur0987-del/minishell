/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 20:45:01 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/18 08:04:19 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_env(t_shell *shell)
{
	t_list	*env_list;
	t_var	*var;
	int		i;

	if (!shell)
		return ;
	i = 0;
	env_list = shell->exp;
	while (env_list && i < shell->len_exp)
	{
		var = env_list->content;
		if (var->value)
		{
			ft_putstr_fd(var->var_name, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(var->value, 1);
		}
		env_list = env_list->next;
		i++;
	}
	g_exit = 0;
}
