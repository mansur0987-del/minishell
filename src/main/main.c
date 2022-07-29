/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:47:07 by armaxima          #+#    #+#             */
/*   Updated: 2022/03/30 11:32:36 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long long	g_exit = 0;

static void	ft_process(t_shell *shell)
{
	t_dlist		*cur_semi;
	t_dlist		*cur_pipe;
	t_pipe_coms	*pipe_coms;

	cur_semi = shell->command;
	while (cur_semi)
	{
		shell->bp = 0;
		cur_pipe = cur_semi->content;
		if (cur_pipe->content)
		{
			pipe_coms = ft_get_pipe(cur_pipe, shell);
			if (pipe_coms && pipe_coms->cmd_total > 0)
			{
				if (pipe_coms->cmd_total == 1)
					ft_proceed_one(pipe_coms->proc_cmd, shell);
				else
					ft_proceed(pipe_coms, shell);
			}
			ft_free_pipe(pipe_coms);
		}
		cur_semi = cur_semi->next;
	}
	free_tmp_file(shell);
}

static void	ft_save_prev(t_shell *shell)
{
	shell->prev_err_cod = shell->err_cod;
	if (g_exit != 0)
	{
		shell->prev_err_cod = g_exit;
	}
}

static int	ft_go(t_shell *shell)
{
	int	check;

	while (shell->exit)
	{
		if (!(ft_init_base(shell)))
			return (0);
		check = ft_read_line(shell);
		if (!check)
			exit(0);
		if (check == 2)
			continue ;
		if (!ft_put_comand(shell))
			return (0);
		ft_process(shell);
		ft_save_prev(shell);
		ft_free_read(shell);
	}
	ft_free_all(shell);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void) argc;
	(void) argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_parent_signal);
	if (!(ft_init_mshell(&shell, env)))
		return (0);
	if (!(ft_go(&shell)))
		return (0);
	return (1);
}
