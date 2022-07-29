/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:57:09 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/29 08:01:21 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	command_found(t_proc *proc)
{	
	int	pid;

	pid = fork();
	if (pid)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &proc->status, WUNTRACED);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_parent_signal);
		g_exit = ft_exit_ret(proc->status);
	}
	else
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		proc->status = execve(proc->full_path, proc->cmd, proc->env);
	}
	free(proc->full_path);
	free_env(proc);
}

static void	cmd_not_found(t_proc *proc)
{
	free_env(proc);
	ft_putstr_fd("minishell: ", 0);
	ft_putstr_fd(proc->cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	g_exit = 127;
}

static char	*extract_cmd(char *path)
{
	int		len;
	int		i;
	char	*res_cmd;

	len = ft_strlen(path);
	i = len;
	while (len > 0 && path[len] != '/')
		len--;
	i = i - len;
	res_cmd = malloc(i);
	if (res_cmd)
		ft_memcpy(res_cmd, &path[++len], i);
	return (res_cmd);
}

void	execute_slash(t_proc *proc)
{
	struct stat		buffer;

	proc->full_path = ft_strdup(proc->cmd[0]);
	if (!(ft_strchr(proc->cmd[0], ' ')))
	{
		free(proc->cmd[0]);
		proc->cmd[0] = extract_cmd(proc->full_path);
	}
	proc->status = stat(proc->full_path, &buffer);
	proc->dir = opendir(proc->full_path);
	if (proc->dir)
	{
		closedir(proc->dir);
		proc->status = 1;
	}
	if (proc->status == 0 && (buffer.st_mode & S_IXUSR) != 0)
		command_found(proc);
	else
		handle_err(proc, buffer);
}

void	handle_cmd(t_proc *proc, t_shell *shell)
{
	int				i;
	struct dirent	*ent;

	i = -1;
	while (shell->path && shell->path[++i])
	{
		proc->dir = opendir(shell->path[i]);
		if (proc->dir)
			ent = readdir(proc->dir);
		while (ent)
		{
			if (!ft_strcmp(proc->cmd[0], ent->d_name))
			{
				proc->full_path = make_full_path(shell->path[i], proc->cmd[0]);
				command_found(proc);
				closedir(proc->dir);
				return ;
			}
			ent = readdir(proc->dir);
		}
		closedir(proc->dir);
	}
	cmd_not_found(proc);
}
