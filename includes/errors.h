/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:23:45 by nmordeka          #+#    #+#             */
/*   Updated: 2022/04/01 13:06:05 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "minishell.h"

void	ft_memory_err(void *check);
void	no_file_dir_err(char *str);
void	handle_err(t_proc *proc, struct stat buffer);
void	ft_pipe_err(t_pipe_coms *cur_pipe);
int		ft_fork_err(int pid, t_pipe_coms *cur_pipe, int max_i);

#endif