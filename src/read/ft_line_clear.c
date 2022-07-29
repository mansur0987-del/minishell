/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:19:05 by armaxima          #+#    #+#             */
/*   Updated: 2022/03/24 14:57:15 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_clear_superfluous(char *line, char c)
{
	int		i;
	int		g;
	char	*tmp;

	i = 0;
	g = 0;
	while (line[i])
		if (line[i++] == c)
			g++;
	tmp = malloc(sizeof(char) * (i - g) + 1);
	if (tmp == NULL)
		return (NULL);
	i = -1;
	g = 0;
	while (line[++i])
	{
		if (line[i] == c)
			continue ;
		tmp[g++] = line[i];
	}
	tmp[g] = '\0';
	free(line);
	return (tmp);
}

void	ft_remove_shiel(char *line)
{
	int	i;
	int	g;

	i = 0;
	g = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		if (line[i] == '\"' && !(ft_shiel(line, i, '\\')))
		{
			i++;
			g++;
		}
		if (i != 0 && line[i - 1] == OFF)
			i++;
		if (line[i] == '\\' && (!(g % 2) || \
		(g % 2 && (line[i + 1] == '\\' || line[i + 1] == '\"'))))
			line[i] = OFF;
		i++;
	}
}

void	ft_put_doll(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == QUOT && !(ft_shiel(line, i, '\\')))
		{
			i++;
			while (line[i] && (line[i] != QUOT || ft_shiel(line, i, '\\')))
				i++;
		}
		if (line[i] == '$' && ((ft_shiel(line, i, '\\') && \
		line[i - 2] != OFF) || ft_shiel(line, i, OFF)))
			line[i - 1] = OFF;
		else if (line[i] == '$' && line[i + 1] != '=')
			line[i] = DOLL;
		if (line[i])
			i++;
	}
}

char	*ft_clear_quotes(char *line, t_shell *shell)
{
	(void) shell;
	ft_remove_shiel(line);
	ft_remove_quotes(line, '\'', '\"');
	ft_put_doll(line, 0);
	ft_remove_quotes(line, '\"', QUOT);
	line = ft_clear_superfluous(line, OFF);
	return (line);
}
