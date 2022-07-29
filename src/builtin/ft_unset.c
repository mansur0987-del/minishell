/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:01:39 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/28 23:07:23 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_unset(char **args, t_shell *shell)
{
	char	**keys;
	int		i;

	g_exit = 0;
	if (!args || !args[1] || !shell)
		return ;
	keys = args;
	i = 1;
	while (keys[i])
	{
		keys[i] = ft_put_var(keys[i], shell);
		if (!valid_arg(keys[i]))
		{
			arg_error(keys[0], keys[i]);
			g_exit = 1;
		}
		else
			remove_env_var(keys[i], shell);
		i++;
	}
}
