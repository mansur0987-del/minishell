/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:52:45 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/17 20:26:48 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

t_list	*ft_lst_copy(t_list *src_list)
{
	t_list	*source;
	t_list	*result;
	t_var	*tmp_cont;

	if (!src_list)
		return (NULL);
	source = src_list;
	result = NULL;
	while (source)
	{
		tmp_cont = malloc(sizeof(t_var));
		tmp_cont->var_name = ft_strdup(((t_var *)(source->content))->var_name);
		if (((t_var *)(source->content))->value)
			tmp_cont->value = ft_strdup(((t_var *)(source->content))->value);
		else
			tmp_cont->value = NULL;
		if (!result)
			result = ft_lstnew(tmp_cont);
		else
			ft_lstadd_back(&result, ft_lstnew(tmp_cont));
		source = source->next;
	}
	return (result);
}
