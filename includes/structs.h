/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 10:56:57 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/30 09:30:59 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

typedef struct s_var
{
	char	*var_name;
	char	*value;
}			t_var;

typedef struct s_com
{
	char			*content;
	int				booling;
	struct s_com	*next;
	struct s_com	*prev;

}			t_com;

typedef struct s_shell
{
	char		*line;
	int			len_comand;
	int			exit;
	int			shlvl;
	int			err_cod;
	int			prev_err_cod;
	char		**path;
	t_list		*exp;
	t_dlist		*command;
	int			len_exp;
	int			bp;
}	t_shell;

typedef struct s_proc
{
	char	**cmd;
	char	*full_path;
	DIR		*dir;
	char	**env;
	int		fds[2];
	int		fdl;
	int		fdr;
	int		savestdout;
	int		savestdin;
	int		i;
	int		x;
	int		status;
	int		pid;
}	t_proc;

typedef struct s_pipe_coms
{
	t_dlist	*proc_cmd;
	int		cmd_total;
}	t_pipe_coms;

#endif
