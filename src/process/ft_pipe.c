/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:39:00 by nmordeka          #+#    #+#             */
/*   Updated: 2022/04/01 13:39:32 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_pipes_open(t_pipe_coms *cur_pipe)
{
	int		i;
	t_proc	*proc;
	t_dlist	*cur_com;

	i = -1;
	cur_com = cur_pipe->proc_cmd;
	while (cur_com && (++i < cur_pipe->cmd_total))
	{
		proc = cur_com->content;
		if (pipe(proc->fds) == -1)
		{
			ft_pipe_err(cur_pipe);
			return (1);
		}
		cur_com = cur_com->next;
	}
	return (0);
}

static void	ft_set_bp(t_dlist *cur_com, t_shell *shell)
{
	t_proc	*proc;

	proc = cur_com->content;
	if (proc->cmd && proc->cmd[0])
		shell->bp = 1;
	else
		shell->bp = 0;
}

static void	ft_child(int i, t_dlist *com, t_pipe_coms *pipe, t_shell *shell)
{
	t_proc	*proc;
	t_proc	*next_proc;
	t_dlist	*next_com;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	proc = com->content;
	if (i != 0)
		dup2(proc->fds[0], 0);
	if (i != (pipe->cmd_total - 1))
	{
		next_com = com->next;
		next_proc = next_com->content;
		dup2(next_proc->fds[1], 1);
	}
	ft_close_all_fds(pipe);
	execute_command(proc, shell);
	exit((int)g_exit % 256);
}

static void	ft_parent(t_proc *proc)
{
	int	status;

	status = proc->status;
	g_exit = WEXITSTATUS(status);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_parent_signal);
	proc->fdr = -2;
	proc->fdl = -2;
}

void	ft_proceed(t_pipe_coms *cur_pipe, t_shell *shell)
{
	int		counter;
	t_proc	*proc;
	t_dlist	*cur_com;

	if (ft_pipes_open(cur_pipe))
		return ;
	cur_com = cur_pipe->proc_cmd;
	ft_set_bp(cur_com, shell);
	counter = -1;
	while (cur_com && ++counter < cur_pipe->cmd_total)
	{
		proc = cur_com->content;
		proc->pid = fork();
		if (ft_fork_err(proc->pid, cur_pipe, counter))
			return ;
		if (!proc->pid)
			ft_child(counter, cur_com, cur_pipe, shell);
		cur_com = cur_com->next;
	}
	ft_close_all_fds(cur_pipe);
	counter = -1;
	while (++counter < cur_pipe->cmd_total)
		wait(&proc->status);
	ft_parent(proc);
}
