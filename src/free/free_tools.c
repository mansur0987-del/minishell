/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:28:36 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/27 23:28:45 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	free_env_var(void *var)
{
	t_var	*content;

	if (!var)
		return ;
	content = (t_var *) var;
	free(content->var_name);
	if (content->value != NULL)
		free(content->value);
	free(content);
}

void	free_env(t_proc *proc)
{
	int	i;

	if (proc->env == NULL)
		return ;
	i = 0;
	while (proc->env[i])
	{
		free(proc->env[i]);
		i++;
	}
	free(proc->env);
}

void	free_shell(t_shell *shell)
{
	t_list	*env_list;
	t_list	*tmp_env_var;

	if (shell->exp)
	{
		env_list = shell->exp;
		while (env_list)
		{
			tmp_env_var = env_list;
			env_list = env_list->next;
			ft_lstdelone(tmp_env_var, &free_env_var);
		}
	}
	free(shell);
}

void	free_tmp_file(t_shell *shell)
{
	char	*path;

	path = make_home_path(shell);
	unlink(path);
	free(path);
}

void	ft_free_pipe(t_pipe_coms *cur_pipe)
{
	t_dlist	*cur_com;

	if (!cur_pipe)
		return ;
	cur_com = cur_pipe->proc_cmd;
	ft_dlstclear(&cur_com, (void *)&free_proc);
	free(cur_pipe);
	return ;
}
