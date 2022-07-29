/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:25:00 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/30 15:31:51 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_cmd(t_proc *proc, t_com *com)
{
	int		i;
	t_com	*cur_com;

	if (!com)
		return ;
	free_cmd(proc);
	i = 0;
	cur_com = com;
	while (cur_com)
	{
		i++;
		cur_com = cur_com->next;
	}
	proc->cmd = (char **)malloc((sizeof(char *) * (i + 1)));
	proc->cmd[0] = NULL;
	ft_memory_err(proc->cmd);
	proc->i = 0;
}

static	t_proc	*init_proc(void)
{
	t_proc	*proc;

	proc = malloc(sizeof(t_proc));
	ft_memory_err(proc);
	proc->cmd = NULL;
	proc->fdl = -2;
	proc->fdr = -2;
	proc->savestdin = dup(0);
	proc->savestdout = dup(1);
	ft_reset_fds(proc);
	return (proc);
}

static void	add_com_pipe(t_proc *proc, t_pipe_coms *res_pipe)
{
	t_dlist		*new_com;

	new_com = ft_dlstnew(proc);
	ft_memory_err(new_com);
	ft_dlstadd_back(&res_pipe->proc_cmd, new_com);
}

t_pipe_coms	*ft_get_pipe(t_dlist *cur_pipe, t_shell *shell)
{
	t_dlist		*cur_com;
	t_proc		*proc;
	t_com		*cmd;
	t_pipe_coms	*res_pipe;

	cur_com = cur_pipe;
	res_pipe = malloc(sizeof(t_pipe_coms));
	ft_memory_err(res_pipe);
	res_pipe->cmd_total = 0;
	res_pipe->proc_cmd = NULL;
	while (cur_com)
	{
		proc = init_proc();
		cmd = (t_com *)cur_com->content;
		set_cmd(proc, cmd);
		if (!ft_process_com(cmd, proc, shell))
		{
			ft_free_pipe(res_pipe);
			return (NULL);
		}
		add_com_pipe(proc, res_pipe);
		res_pipe->cmd_total++;
		cur_com = cur_com->next;
	}
	return (res_pipe);
}
