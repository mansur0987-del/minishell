/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:18:21 by nmordeka          #+#    #+#             */
/*   Updated: 2022/04/01 13:38:26 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	ft_memory_err(void *check)
{
	if (!check)
	{
		ft_putendl_fd("Error!\nOut of memory", 2);
		exit (2);
	}
}

void	ft_pipe_err(t_pipe_coms *cur_pipe)
{
	ft_putendl_fd("minishell: Error with creating pipe", 2);
	ft_close_all_fds(cur_pipe);
	g_exit = 1;
}

int	ft_fork_err(int pid, t_pipe_coms *cur_pipe, int max_i)
{
	int		i;
	t_proc	*proc;
	t_dlist	*cur_com;

	if (pid != -1)
		return (0);
	ft_putendl_fd("minishell: Error with creating fork", 2);
	cur_com = cur_pipe->proc_cmd;
	i = -1;
	while (cur_com && ++i < max_i)
	{
		proc = cur_com->content;
		ft_close_fds(proc);
		if (proc->pid > 0)
		{
			kill(proc->pid, 9);
			waitpid(proc->pid, &proc->status, 0);
		}
		cur_com = cur_com->next;
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_parent_signal);
	g_exit = 1;
	return (1);
}
