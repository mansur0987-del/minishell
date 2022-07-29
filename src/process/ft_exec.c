/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 12:12:26 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/30 14:11:02 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_to_lower(char *cmd)
{
	int	symb;

	symb = -1;
	while (cmd[++symb])
		cmd[symb] = ft_tolower(cmd[symb]);
}

static void	exec_other_cmd(t_proc *proc, t_shell *shell)
{
	cmd_to_lower(proc->cmd[0]);
	proc->env = ft_extract_env(shell);
	if (ft_strchr(proc->cmd[0], '/'))
	{
		execute_slash(proc);
		return ;
	}
	handle_cmd(proc, shell);
}

static void	execute(t_proc *proc, t_shell *shell)
{
	char	**cmd;

	cmd = proc->cmd;
	if (!cmd[0])
		return ;
	if (!(ft_strcmp(cmd[0], "export")))
		ft_export(cmd, shell);
	else if (!(ft_strcmp(cmd[0], "env")))
		ft_env(shell);
	else if (!(ft_strcmp(cmd[0], "pwd")))
		ft_pwd(shell);
	else if (!(ft_strcmp(cmd[0], "echo")))
		ft_echo(cmd);
	else if (!(ft_strcmp(cmd[0], "exit")))
	{
		if (!(shell->bp))
			ft_exit(cmd);
		return ;
	}
	else if (!(ft_strcmp(cmd[0], "cd")))
		ft_cd(cmd[1], shell);
	else if (!(ft_strcmp(cmd[0], "unset")))
		ft_unset(cmd, shell);
	else
		exec_other_cmd(proc, shell);
}

void	execute_command(t_proc *proc, t_shell *shell)
{
	int	savestdout;
	int	savestdin;

	savestdout = dup(1);
	savestdin = dup(0);
	if (proc->fdr != -2)
		dup2(proc->fdr, 1);
	if (proc->fdl != -2)
		dup2(proc->fdl, 0);
	execute(proc, shell);
	if (proc->fdr != -2)
	{
		close(proc->fdr);
		proc->fdr = -2;
		dup2(savestdout, 1);
	}
	if (proc->fdl != -2)
	{
		close(proc->fdl);
		proc->fdl = -2;
		dup2(savestdin, 0);
	}
}

void	ft_proceed_one(t_dlist *com, t_shell *shell)
{
	t_proc	*proc;

	proc = com->content;
	execute_command(proc, shell);
	ft_close_fds(proc);
	dup2(proc->savestdin, 0);
	dup2(proc->savestdout, 1);
}
