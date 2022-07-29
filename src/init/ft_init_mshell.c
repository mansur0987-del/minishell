/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:01:18 by armaxima          #+#    #+#             */
/*   Updated: 2022/03/16 15:32:44 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_read_env(t_shell *shell, char **env)
{
	int		i;
	t_var	*tmp;
	char	**str;

	i = -1;
	while (env[++i])
	{
		str = ft_split(env[i], '=');
		if (str == NULL)
			return (0);
		tmp = malloc(sizeof(t_var));
		if (tmp == NULL)
			return (ft_free_line(str));
		tmp->var_name = str[0];
		tmp->value = str[1];
		free(str);
		if (i == 0)
			shell->exp = ft_lstnew(tmp);
		else
			ft_lstadd_front(&shell->exp, ft_lstnew(tmp));
		if (shell->exp == NULL)
			return (ft_free_line(str));
	}
	shell->len_exp = i;
	return (1);
}

int	ft_init_mshell(t_shell *shell, char **env)
{
	if (!(ft_read_env(shell, env)))
		return (0);
	shell->exit = 1;
	shell->prev_err_cod = 0;
	return (1);
}
