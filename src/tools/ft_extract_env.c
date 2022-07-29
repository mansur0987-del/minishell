/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:28:50 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/21 10:41:55 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

static int	get_lstsize(t_list *ls)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = ls;
	while (lst)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}

static char	*get_str_from_nvar(t_var *var)
{
	char	*result;
	char	*tmp_str;

	tmp_str = ft_strjoin(var->var_name, "=");
	if (!tmp_str)
		return (tmp_str);
	result = ft_strjoin(tmp_str, var->value);
	free (tmp_str);
	return (result);
}

char	**ft_extract_env(t_shell *shell)
{
	int		i;
	int		size;
	char	**result;
	t_list	*tmp_env;

	if (!shell && !(shell->exp))
		return (NULL);
	tmp_env = shell->exp;
	size = get_lstsize(tmp_env);
	result = (char **)malloc((sizeof(char *) * (size + 1)));
	ft_memory_err(result);
	i = -1;
	while (++i < size)
	{
		result[i] = get_str_from_nvar(tmp_env->content);
		tmp_env = tmp_env->next;
	}
	result[i] = NULL;
	return (result);
}
