/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_com.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:48:39 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/27 23:11:44 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_comm(t_proc *proc, t_com *com)
{
	proc->cmd[proc->i] = ft_strdup(com->content);
	ft_memory_err(proc->cmd[proc->i]);
	proc->i++;
	proc->cmd[proc->i] = NULL;
}

static void	put_vars_tocom(t_com *com, t_shell *shell)
{
	t_com	*tmp_com;

	tmp_com = com;
	while (tmp_com)
	{
		tmp_com->content = ft_put_var(tmp_com->content, shell);
		tmp_com = tmp_com -> next;
	}
}

int	ft_process_com(t_com *com, t_proc *proc, t_shell *shell)
{
	put_vars_tocom(com, shell);
	while (com)
	{
		if ((ft_check_redirect(com->content) && com->booling && \
			com->next && (!ft_check_redirect(com->next->content))))
		{
			handle_redirect(proc, com, shell);
			if (proc->fdr == -1 || proc->fdl == -1)
			{
				no_file_dir_err(com->next->content);
				free_proc(proc);
				return (0);
			}
			com = com->next;
		}
		else
			add_comm(proc, com);
		com = com->next;
	}
	return (1);
}
