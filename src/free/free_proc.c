/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:10:07 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/30 15:11:55 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_proc *proc)
{
	int		i;
	char	**cmd;

	cmd = proc->cmd;
	if (cmd == NULL)
		return ;
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
	cmd = NULL;
	return ;
}

void	free_proc(t_proc *proc)
{
	free_cmd(proc);
	free(proc);
}
