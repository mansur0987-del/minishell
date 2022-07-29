/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:04:04 by armaxima          #+#    #+#             */
/*   Updated: 2022/03/07 20:58:42 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup_len(char *str, int start, int end)
{
	int		i;
	int		save_start;
	char	*dup_str;

	save_start = start;
	dup_str = malloc(sizeof(char) * (end - start + 1));
	if (dup_str != NULL)
	{
		i = -1;
		while (++i < (end - save_start))
			dup_str[i] = str[start++];
		dup_str[i] = '\0';
	}
	return (dup_str);
}

int	ft_skip_quot(char *str, int i, char c)
{
	i++;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	ft_skip_sp(char *str, int i, char c)
{
	while (str[i] && str[i] == c)
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return (s1[i] - s2[i]);
}
