/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 10:41:52 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/16 16:00:21 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_pwd(t_shell *shell)
{
	char	*path;

	path = get_env_var("PWD", shell);
	if (path)
	{
		ft_putendl_fd(path, 1);
		free(path);
	}
	g_exit = 0;
}
