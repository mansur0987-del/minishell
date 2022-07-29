/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 07:57:43 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/29 08:15:13 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	ft_add_front_com(t_com **lst, t_com *new)
{
	t_com	*last;

	last = (*lst);
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
}

void	ft_add_front_dlst(t_dlist **lst, t_dlist *new)
{
	t_dlist	*last;

	last = (*lst);
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
}
