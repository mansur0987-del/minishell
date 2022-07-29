/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_comand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:54:28 by armaxima          #+#    #+#             */
/*   Updated: 2022/03/21 18:09:20 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_find_content(char *str, int *i)
{
	int		end;
	char	*content;

	content = NULL;
	*i = ft_skip_sp(str, *i, SP);
	if (!(str[*i]))
		return (NULL);
	if (str[*i] == ININ || str[*i] == IN || \
	str[*i] == OUTOUT || str[*i] == OUT)
		return (ft_change(str[*i], 0));
	end = *i;
	while (str[end] && str[end] != SP && str[end] != ININ && \
	str[end] != IN && str[end] != OUTOUT && str[end] != OUT)
		end++;
	content = ft_strdup_len(str, *i, end);
	*i = end;
	return (content);
}

static t_com	*ft_add_content(char *str, int *i)
{
	t_com	*new;
	char	*content;

	new = malloc(sizeof(t_com));
	if (new == NULL)
		return (NULL);
	content = ft_find_content(str, i);
	if (content == NULL)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	new->prev = NULL;
	new->booling = FALSE;
	new->content = content;
	if (new->content[0] == '>' || new->content[0] == '<')
	{
		(*i)++;
		new->booling = TRUE;
	}
	return (new);
}

static t_com	*ft_add_command(char	*str)
{
	t_com	*new;
	t_com	*check;
	int		i;

	i = 0;
	while (str[i])
	{
		if (!i)
			new = ft_add_content(str, &i);
		else
		{
			check = ft_add_content(str, &i);
			if (check == NULL)
				break ;
			ft_add_front_com(&new, check);
		}
		if (new == NULL)
			return (NULL);
	}
	return (new);
}

static t_dlist	*ft_spl_pip(char *line)
{
	char	**spl_line_pip;
	int		i;
	t_dlist	*new;

	spl_line_pip = ft_split(line, PIP);
	if (spl_line_pip == NULL)
		return (NULL);
	i = 0;
	while (spl_line_pip[i])
	{
		if (i == 0)
			new = ft_dlstnew(ft_add_command(spl_line_pip[i]));
		else
			ft_add_front_dlst(&new, \
			ft_dlstnew(ft_add_command(spl_line_pip[i])));
		i++;
	}
	ft_free_path (&spl_line_pip);
	return (new);
}

int	ft_put_comand(t_shell *shell)
{
	char	**spl_line;
	int		i;

	spl_line = ft_split(shell->line, END);
	if (spl_line == NULL)
		return (0);
	i = 0;
	while (spl_line[i])
	{
		if (i == 0)
			shell->command = ft_dlstnew(ft_spl_pip(spl_line[i]));
		else
			ft_add_front_dlst(&shell->command, \
			ft_dlstnew(ft_spl_pip(spl_line[i])));
		i++;
	}
	ft_free_path(&spl_line);
	return (1);
}
