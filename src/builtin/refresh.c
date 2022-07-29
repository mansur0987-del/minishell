/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:30:01 by nmordeka          #+#    #+#             */
/*   Updated: 2022/02/10 20:57:59 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	refresh_old_pwd(char *pwd, char **arg, t_shell *shell)
{
	t_list	*env;
	char	*prev_old;
	int		flag;

	env = shell->exp;
	flag = 0;
	while (env)
	{
		if (!ft_strncmp(((t_var *)(env->content))->var_name, "OLDPWD", 6))
		{
			prev_old = ((t_var *)(env->content))->value;
			((t_var *)(env->content))->value = ft_strdup(pwd);
			free(prev_old);
			flag = 1;
		}
		env = env->next;
	}
	if (!flag)
	{
		arg[1] = ft_strjoin("OLDPWD=", pwd);
		ft_export(arg, shell);
		free(arg[1]);
	}
	free(pwd);
}

static void	set_new_pwd(t_shell *shell)
{
	t_list	*env;
	char	*prev_pwd;

	env = shell->exp;
	while (env)
	{
		if (!ft_strncmp(((t_var *)(env->content))->var_name, "PWD", 3))
		{
			prev_pwd = ((t_var *)(env->content))->value;
			free(prev_pwd);
			((t_var *)(env->content))->value = getcwd(NULL, MAXPATHLEN);
		}
		env = env->next;
	}
}

void	refresh_env(t_shell *shell)
{
	char	*pwd;
	char	*old;
	char	*arg[3];

	old = NULL;
	arg[0] = "com";
	arg[1] = "OLDPWD";
	arg[2] = NULL;
	pwd = get_env_var("PWD", shell);
	if (!pwd)
		pwd = ft_strdup("");
	refresh_old_pwd(pwd, arg, shell);
	set_new_pwd(shell);
}
