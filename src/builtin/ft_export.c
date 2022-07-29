/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:17:11 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/30 13:26:17 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	display_sort_env(t_shell *shell)
{
	t_list	*list;
	t_list	*start;
	t_var	*var;

	list = ft_lst_copy(shell->exp);
	ft_lst_sort(list);
	start = list;
	while (list)
	{
		var = (t_var *)list->content;
		if (ft_strcmp(var->var_name, "_"))
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(var->var_name, 1);
			if (var->value && var->value[0] != '\n')
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(var->value, 1);
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		list = list->next;
	}
	ft_lstclear(&start, &free_env_var);
}

static void	add_var_to_env(t_var *var, t_shell *shell)
{
	t_var	*tmp;

	tmp = var;
	if (shell->len_exp == 0)
	{
		shell->exp = ft_lstnew(tmp);
		shell->len_exp++;
	}
	else if (!reset_var(tmp->var_name, tmp->value, &shell->exp))
	{
		ft_lstadd_back(&shell->exp, ft_lstnew(tmp));
		shell->len_exp++;
	}
	else
		free_env_var(var);
}

static t_var	*get_var(char *arg)
{
	t_var	*var;
	char	*equal;

	var = malloc(sizeof(t_var));
	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		var->value = NULL;
		var->var_name = ft_strdup(arg);
	}
	else if (*(equal + 1) == '\0')
	{
		var->value = ft_strdup("");
		var->var_name = malloc(ft_strlen(arg) - 1);
		ft_strlcpy(var->var_name, arg, ft_strlen(arg));
	}
	else
	{
		var->value = ft_strdup(++equal);
		var->var_name = malloc(ft_strlen(arg) - ft_strlen(var->value));
		ft_strlcpy(var->var_name, arg, ft_strlen(arg) - ft_strlen(var->value));
	}
	return (var);
}

static int	is_valid(int i, t_var *var, t_shell *shell, char **arg)
{
	var->var_name = ft_put_var(var->var_name, shell);
	if (var->value)
		var->value = ft_put_var(var->value, shell);
	if (!valid_arg(var->var_name))
	{
		arg_error(arg[0], arg[i]);
		g_exit = 1;
		return (0);
	}
	else
		return (1);
}

void	ft_export(char **arg, t_shell *shell)
{
	int		i;
	char	**args;
	t_var	*var;

	g_exit = 0;
	if (!arg[1])
	{
		display_sort_env(shell);
		return ;
	}
	i = 0;
	args = arg;
	while (args[++i])
	{
		var = get_var(args[i]);
		if (args[i][0] == '=')
		{
			free(var->var_name);
			var->var_name = ft_strjoin("=", var->value);
		}
		if (!is_valid(i, var, shell, arg))
			free_env_var(var);
		else
			add_var_to_env(var, shell);
	}
}
