/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 22:42:26 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/16 16:28:39 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	no_file_dir_err(char *str)
{
	ft_putstr_fd("minishell: ", 0);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	handle_err(t_proc *proc, struct stat buffer)
{
	ft_putstr_fd("minishell: ", 0);
	ft_putstr_fd(proc->full_path, 2);
	if (proc->status == 0 && (buffer.st_mode & S_IXUSR) == 0)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		g_exit = 126;
	}
	else if (proc->status == 1)
	{
		ft_putstr_fd(": is a directory\n", 2);
		g_exit = 126;
	}
	else
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit = 127;
	}
	free(proc->full_path);
	free_env(proc);
}
