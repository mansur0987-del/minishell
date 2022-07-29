/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:51:39 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/24 20:13:50 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_redirect(char *str)
{
	if (!(ft_strcmp(">>", str)) || !(ft_strcmp(">", str)) || \
		!(ft_strcmp("<", str)) || !(ft_strcmp("<<", str)))
		return (TRUE);
	return (FALSE);
}

static int	open_for_redir(char *redir, char *file)
{
	int	fd;

	fd = -1;
	if (redir)
	{
		if (!ft_strcmp(redir, ">"))
			fd = open(file, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | \
			S_IWUSR | S_IRGRP | S_IROTH);
		else if (!ft_strcmp(redir, "<"))
			fd = open(file, O_RDONLY);
		else
			fd = open(file, O_APPEND | O_WRONLY | O_CREAT, S_IRUSR | \
			S_IWUSR | S_IRGRP | S_IROTH);
	}
	return (fd);
}

static void	handle_double(t_proc *proc, t_com *com, t_shell *shell)
{
	char	*str;
	char	*path;

	str = ft_reading(com->next->content);
	ft_remove_shiel(str);
	ft_put_doll(str, 0);
	str = ft_clear_superfluous(str, OFF);
	str = ft_put_var(str, shell);
	if (com->prev)
	{
		if (proc->fdl != -2)
			close(proc->fdl);
		path = make_home_path(shell);
		proc->fdl = open(path, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | \
			S_IWUSR | S_IRGRP | S_IROTH);
		write(proc->fdl, str, ft_strlen(str));
		close(proc->fdl);
		proc->fdl = open(path, O_RDONLY);
		free(path);
	}
	free (str);
}

void	handle_redirect(t_proc *proc, t_com *com, t_shell *shell)
{
	if (com->content[0] == '>')
	{
		if (proc->fdr != -2)
			close(proc->fdr);
		proc->fdr = open_for_redir(com->content, com->next->content);
	}
	else if (!(ft_strcmp(com->content, "<")))
	{
		if (proc->fdl != -2)
			close(proc->fdl);
		proc->fdl = open_for_redir(com->content, com->next->content);
	}
	else
		handle_double(proc, com, shell);
}
