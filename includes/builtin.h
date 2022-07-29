/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 09:11:08 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/05 15:36:23 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libft/libft.h"
# include "minishell.h"

void	ft_cd(char *str, t_shell *shell);
void	ft_pwd(t_shell *shell);
void	ft_echo(char **str);
void	ft_env(t_shell *shell);
void	ft_exit(char **args);
void	ft_export(char **arg, t_shell *shell);
void	ft_unset(char **args, t_shell *shell);
void	refresh_env(t_shell *shell);
void	handle_cmd(t_proc *proc, t_shell *shell);
void	execute_slash(t_proc *proc);

#endif