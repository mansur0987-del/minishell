/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_com.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:45:33 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/18 10:31:04 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_com(t_com **com)
{
	t_com	*cur_com;

	cur_com = *com;
	while (cur_com)
	{
		if (cur_com->content)
			free(cur_com->content);
		if (cur_com->next == NULL)
		{
			free(cur_com);
			break ;
		}
		else
		{
			cur_com = cur_com->next;
			free(cur_com->prev);
		}
	}
}

static void	free_pipe(t_dlist **pipe)
{
	t_dlist	*cur_pipe;
	t_com	*command;

	cur_pipe = *pipe;
	while (cur_pipe)
	{
		command = (t_com *)cur_pipe->content;
		free_com(&command);
		if (cur_pipe->next == NULL)
		{
			free(cur_pipe);
			break ;
		}
		else
		{
			cur_pipe = cur_pipe->next;
			free(cur_pipe->prev);
		}
	}
}

void	ft_free_com(t_dlist **com)
{
	t_dlist	*semi;
	t_dlist	*pipe;

	semi = *com;
	while (semi)
	{
		pipe = semi->content;
		free_pipe(&pipe);
		if (semi->next == NULL)
		{
			free(semi);
			break ;
		}
		else
		{
			semi = semi->next;
			free(semi->prev);
		}
	}
}
