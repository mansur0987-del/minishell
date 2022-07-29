/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:46:17 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/24 16:03:54 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

char	*get_env_var(char *var_name, t_shell *shell)
{
	char		*result;
	t_list		*env_list;
	t_var		*var;
	int			i;

	result = NULL;
	i = 0;
	env_list = shell->exp;
	while ((i < shell->len_exp) && env_list)
	{
		var = env_list->content;
		if (!(ft_strcmp(var_name, var->var_name)))
		{
			if (var->value)
				result = ft_strdup(var->value);
			break ;
		}
		env_list = env_list->next;
		i++;
	}
	return (result);
}

void	add_env_var(char *var_name, char *value, t_shell *shell)
{
	t_var	*var;
	t_list	*node;

	if (!shell)
		return ;
	var = malloc(sizeof(t_var));
	if (!var)
		return ;
	if (!var_name)
		var_name = ft_strdup("");
	if (!value)
		value = ft_strdup("");
	var->var_name = var_name;
	var->value = value;
	node = ft_lstnew(var);
	if (shell->len_exp == 0)
		shell->exp = node;
	else
		ft_lstadd_back(&shell->exp, node);
	shell->len_exp++;
}

int	reset_var(char *var_name, char *value, t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (!ft_strncmp(((t_var *)tmp->content)->var_name, var_name, \
			ft_strlen(var_name)))
		{
			if (value)
			{
				free(((t_var *) tmp->content)->value);
				((t_var *) tmp->content)->value = ft_strdup(value);
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	remove_env_var(char *var_name, t_shell *shell)
{
	t_list	*cur_node;
	t_list	*prev_node;
	t_var	*var;

	prev_node = NULL;
	cur_node = shell->exp;
	while (cur_node)
	{
		var = cur_node->content;
		if (!ft_strncmp(var_name, var->var_name, ft_strlen(var_name)))
		{
			if (!prev_node)
				shell->exp = cur_node->next;
			else if (cur_node->next == NULL)
				prev_node->next = NULL;
			else
				prev_node->next = cur_node->next;
			ft_lstdelone(cur_node, &free_env_var);
			shell->len_exp--;
			break ;
		}
		prev_node = cur_node;
		cur_node = cur_node->next;
	}
}
