/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:56:45 by armaxima          #+#    #+#             */
/*   Updated: 2022/03/30 15:11:47 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <dirent.h>
# include "structs.h"

# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <sys/param.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <strings.h>
# include <stdio.h>
# include <readline/readline.h>

# include "errors.h"
# include "tools.h"
# include "builtin.h"

# define TRUE 1
# define FALSE 0

# define QUOT 1
# define SP 2
# define END 3
# define PIP 4
# define OUTOUT 5
# define OUT 6
# define ININ 7
# define IN 8
# define OFF 17
# define DOLL 16

# define PROMPT "minishell > "

extern long long	g_exit;

int			add_history(const char *str);
int			ft_init_mshell(t_shell *shell, char **env);
int			ft_read_line(t_shell *shell);
int			ft_check_quotes(char *line, char quot, char quotes);
int			ft_init_base(t_shell *shell);
char		*ft_clear_quotes(char *line, t_shell *shell);
void		ft_remove_quotes(char *line, char quot, char quotes);
int			ft_shiel(char *line, int len, char c);
int			ft_check_comand(char *str, t_shell *shell);
int			ft_skip_quot(char *str, int i, char c);
int			ft_skip_sp(char *str, int i, char c);
int			ft_puterror_1(char *str, t_shell *shell);
int			ft_free_all(t_shell *shell);
void		ft_free_com(t_dlist **com);
void		free_cmd(t_proc *proc);
void		free_proc(t_proc *proc);
int			ft_free_read(t_shell *shell);
int			ft_free_line(char **str);
int			ft_free_path(char ***str);
char		*ft_change(char c, int i);
char		*ft_strdup_len(char *str, int start, int end);
char		*ft_find_env(char *str, int *i, t_shell *shell);
t_com		*ft_last(t_com *lst);
int			ft_put_comand(t_shell *shell);
char		*ft_check_char(char *str, int i);
int			ft_check_redirect(char *str);
void		handle_redirect(t_proc *proc, t_com *com, t_shell *shell);
char		*ft_change_1(char c, char d);
int			ft_strcmp(char *s1, char *s2);
char		*ft_put_var(char *line, t_shell *shell);
int			ft_process_com(t_com *com, t_proc *proc, t_shell *shell);
int			ft_exit_ret(int status);
void		handle_parent_signal(int signal);
char		*ft_clear_superfluous(char *line, char c);
char		*ft_reading(char *str);
void		ft_remove_shiel(char *line);
void		ft_put_doll(char *line, int i);

t_pipe_coms	*ft_get_pipe(t_dlist *cur_pipe, t_shell *shell);
void		ft_proceed(t_pipe_coms *pipe, t_shell *shell);
void		ft_proceed_one(t_dlist *com, t_shell *shell);
void		ft_close_all_fds(t_pipe_coms *cur_pipe);
void		cmds_to_lower(char **cmds);
void		execute_command(t_proc *proc, t_shell *shell);

#endif
