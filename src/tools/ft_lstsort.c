/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 20:29:53 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/17 12:37:50 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

static int	comp_env_vars(t_list *var1, t_list *var2)
{
	char	*var_name1;
	char	*var_name2;

	if (!var1)
		return (-1);
	if (!var2)
		return (1);
	var_name1 = ((t_var *)(var1->content))->var_name;
	var_name2 = ((t_var *)(var2->content))->var_name;
	return (ft_strcmp(var_name1, var_name2));
}

static void	ft_lst_swap(t_list *node1, t_list *node2)
{
	t_var	*tmp;

	tmp = node1->content;
	node1->content = node2->content;
	node2->content = tmp;
}

void	ft_lst_sort(t_list *list)
{
	int		i;
	int		j;
	t_list	*list_i;
	t_list	*list_j;

	if (ft_lstsize(list) < 2)
		return ;
	else
	{
		i = -1;
		list_i = list;
		while (++i < ft_lstsize(list) - 1)
		{
			j = i;
			list_j = list_i->next;
			while (++j < ft_lstsize(list))
			{
				if (comp_env_vars(list_i, list_j) > 0)
					ft_lst_swap(list_i, list_j);
				list_j = list_j->next;
			}
			list_i = list_i->next;
		}
	}
}
