/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:01:07 by armaxima          #+#    #+#             */
/*   Updated: 2022/03/12 21:23:00 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_shiel(char *line, int len, char c)
{
	int	i;
	int	g;

	g = 0;
	i = 0;
	while (i < len)
	{
		if (line[i] == c)
			g++;
		else
			g = 0;
		i++;
	}
	return (g % 2);
}

int	ft_check_quotes(char *line, char qu, char quotes)
{
	int	i;
	int	g;

	i = 0;
	g = 0;
	while (line[i])
	{
		if (line[i] == quotes && !(g % 2) && !(ft_shiel(line, i, '\\')))
		{
			i++;
			while (line[i] && (line[i] != quotes || \
			ft_shiel(line, i, '\\')))
				i++;
		}
		if (line[i] == qu && ((qu == '\'' && (!(ft_shiel(line, i, '\\')) \
		|| (g % 2))) || (qu == '\"' && !(ft_shiel(line, i, '\\')))))
			g++;
		i++;
	}
	return (g);
}

static void	ft_change_char(char *line, int i)
{
	if (ft_shiel(line, i, OFF))
		return ;
	else if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		line[i] = SP;
	else if (line[i] == ';')
		line[i] = END;
	else if (line[i] == '|')
		line[i] = PIP;
	else if (line[i] == '>' && line[i + 1] && line[i + 1] == '>')
	{
		line[i + 1] = OUTOUT;
		line[i] = OFF;
	}
	else if (line[i] == '>')
		line[i] = OUT;
	else if (line[i] == '<' && line[i + 1] && line[i + 1] == '<')
	{
		line[i + 1] = ININ;
		line[i] = OFF;
	}
	else if (line[i] == '<')
		line[i] = IN;
}

void	ft_remove_quotes(char *line, char qu, char quotes)
{
	int	i;
	int	g;

	i = 0;
	g = 0;
	while (line[i])
	{
		if (line[i] == quotes && !(g % 2) && !(ft_shiel(line, i, OFF)))
		{
			i++;
			while (line[i] && (line[i] != quotes || ft_shiel(line, i, OFF)))
				i++;
		}
		if (line[i] == qu && ((qu == '\'' && (!(ft_shiel(line, i, OFF)) || \
		(g % 2))) || (qu == '\"' && !(ft_shiel(line, i, OFF)))))
		{
			g++;
			line[i] = QUOT;
		}
		if (!(g % 2) && qu == '\"')
			ft_change_char(line, i);
		i++;
	}
}
