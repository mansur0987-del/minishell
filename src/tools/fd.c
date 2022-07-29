/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:41:04 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/27 23:34:42 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	ft_reset_fds(t_proc *proc)
{
	proc->fds[0] = -2;
	proc->fds[1] = -2;
}

void	ft_close_fds(t_proc *proc)
{
	if (proc->fds[0] != -2)
		close(proc->fds[0]);
	if (proc->fds[1] != -2)
		close(proc->fds[1]);
}

void	ft_close_fd_std(t_proc *proc)
{
	if (proc->savestdin > 0)
		close(proc->savestdin);
	if (proc->savestdout > 0)
		close(proc->savestdout);
}

void	ft_close_all_fds(t_pipe_coms *cur_pipe)
{
	t_dlist	*cur_com;
	t_proc	*proc;

	cur_com = cur_pipe->proc_cmd;
	while (cur_com)
	{
		proc = cur_com->content;
		ft_close_fds(proc);
		cur_com = cur_com->next;
	}
}
