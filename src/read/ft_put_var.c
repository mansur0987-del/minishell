/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:56:08 by armaxima          #+#    #+#             */
/*   Updated: 2022/03/24 16:09:35 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_val(char *last, t_shell *shell)
{
	char	*val;
	char	*tmp;

	if (last[0] == '\0')
		val = ft_strdup("$");
	else if (last[0] == '?')
	{
		tmp = ft_itoa((int) g_exit);
		if (!last[1])
			val = ft_strdup(tmp);
		else
			val = ft_strjoin(tmp, &last[1]);
		free(tmp);
	}
	else if (ft_isdigit(last[0]))
		val = ft_strdup(&last[1]);
	else
		val = get_env_var(last, shell);
	return (val);
}

static char	*ft_find_var_put(char *tmp, char *line, int *i, t_shell *shell)
{
	char	*val;
	char	*last;
	int		start;

	start = ++(*i);
	while (line[*i] && line[*i] != ' ' && line[*i] != SP && line[*i] != ININ && \
	line[*i] != IN && line[*i] != OUTOUT && line[*i] != OUT && \
	line[*i] != DOLL && line[*i] != PIP && line[*i] != END && line[*i] != QUOT \
	&& line[*i] != '\'' && line[*i] != '=' && line[*i] != '\n' && \
	line[*i] != '\"')
		(*i)++;
	last = ft_strdup_len(line, start, (*i));
	val = get_val(last, shell);
	free(last);
	last = tmp;
	if (val != NULL)
		tmp = ft_strjoin(last, val);
	else
		tmp = ft_strjoin(last, "");
	free(val);
	free(last);
	return (tmp);
}

static char	*ft_search_doll(char *tmp, char *line, int *i)
{
	int		start;
	char	*last;
	char	*new;

	start = (*i);
	while (line[*i] && line[*i] != DOLL)
		(*i)++;
	new = ft_strdup_len(line, start, (*i));
	last = tmp;
	tmp = ft_strjoin(last, new);
	free(new);
	free(last);
	(*i)--;
	return (tmp);
}

char	*ft_put_var(char *line, t_shell *shell)
{
	int		i;
	int		g;
	char	*tmp;

	tmp = ft_strdup("");
	i = 0;
	g = 0;
	while (line[i])
	{
		if (line[i] == DOLL)
		{
			tmp = ft_find_var_put(tmp, line, &i, shell);
			g = ft_strlen(tmp) - 1;
			i--;
		}
		else
			tmp = ft_search_doll(tmp, line, &i);
		i++;
		g++;
	}
	free(line);
	tmp = ft_clear_superfluous(tmp, QUOT);
	return (tmp);
}
