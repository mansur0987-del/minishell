/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:26:34 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/21 11:33:29 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	pwd_err(void)
{
	ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	g_exit = 1;
}

static void	pwd_dir_err(char *str)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	g_exit = 1;
}

static void	change_dir(DIR *dir, char *str, int minus_flag, t_shell *shell)
{
	closedir(dir);
	chdir(str);
	refresh_env(shell);
	if (minus_flag)
		ft_pwd(shell);
	else
		g_exit = 0;
}

void	ch_dir(char *strn, char *new, int minus_flag, t_shell *shell)
{
	DIR		*dir;
	char	*str;

	if (new)
		str = new;
	else
		str = strn;
	dir = opendir(str);
	if (!dir)
		pwd_dir_err(str);
	else
		change_dir(dir, str, minus_flag, shell);
	if (new)
		free(new);
}

void	ft_cd(char *str, t_shell *shell)
{
	int			minus_flag;
	char		*new_str;

	if (shell->bp)
		return ;
	new_str = NULL;
	minus_flag = 0;
	if (!str || !ft_strncmp(str, "~", 1))
		new_str = get_env_var("HOME", shell);
	else if (!ft_strcmp(str, "-"))
	{
		new_str = get_env_var("OLDPWD", shell);
		if (!new_str)
		{
			pwd_err();
			return ;
		}
		minus_flag = 1;
	}
	ch_dir(str, new_str, minus_flag, shell);
}
