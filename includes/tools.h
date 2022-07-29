/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:57:29 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/29 08:14:46 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "../libft/libft.h"
# include "minishell.h"

# ifndef MAX_LL_INT
#  define MAX_LL_INT 9223372036854775807
# endif

unsigned long long	ft_atoull(char *str, int *sign);
t_list				*ft_lst_copy(t_list *src_list);
void				ft_lst_sort(t_list *list);

void				ft_add_front_com(t_com **lst, t_com *new);
void				ft_add_front_dlst(t_dlist **lst, t_dlist *new);

char				**ft_extract_env(t_shell *shell);
char				*make_full_path(char *cmd, char *path);
char				*make_home_path(t_shell *shell);

char				*get_env_var(char *var_name, t_shell *shell);
void				add_env_var(char *var_name, char *value, t_shell *shell);
int					reset_var(char *var_name, char *value, t_list **lst);
void				remove_env_var(char *var_name, t_shell *shell);

void				free_env_var(void *var);
void				free_shell(t_shell *shell);
void				free_env(t_proc *proc);
void				free_tmp_file(t_shell *shell);
void				ft_free_pipe(t_pipe_coms *pipe);

void				ft_reset_fds(t_proc *proc);
void				ft_close_fds(t_proc *proc);
void				ft_close_fd_std(t_proc *proc);
void				ft_close_all_fds(t_pipe_coms *cur_pipe);

int					valid_arg(char *arg);
void				arg_error(char *command, char *param);

#endif