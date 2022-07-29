/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reading.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:14:50 by armaxima          #+#    #+#             */
/*   Updated: 2022/03/23 10:15:25 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_put_n(char *join, char *line, char *tmp)
{
	free(line);
	free(tmp);
	if (join == NULL)
		return (NULL);
	tmp = ft_strdup(join);
	free(join);
	if (tmp == NULL)
		return (NULL);
	join = ft_strjoin(tmp, "\n");
	free(tmp);
	return (join);
}

char	*ft_reading(char *str)
{
	char	*line;
	char	*tmp;
	char	*join;

	join = strdup("");
	while (1)
	{
		tmp = ft_strdup(join);
		free(join);
		line = readline("> ");
		if (line == NULL)
			break ;
		if (!(strcmp(line, str)))
			break ;
		join = ft_strjoin(tmp, line);
		join = ft_put_n(join, line, tmp);
		if (join == NULL)
			break ;
	}
	free(line);
	return (tmp);
}
