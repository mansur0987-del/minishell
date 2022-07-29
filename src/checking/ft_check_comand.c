/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_comand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:48:48 by armaxima          #+#    #+#             */
/*   Updated: 2022/03/12 21:23:45 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_check_char_2(char *str, int i)
{
	int	g;

	g = ft_skip_sp(str, i + 1, SP);
	if (str[i] == PIP && !(str[g]))
		return (ft_change_1(str[i], 0));
	if ((str[i] == END || str[i] == PIP) && \
	(str[i + 1] == END || str[i + 1] == PIP))
		return (ft_change_1(str[i], str[i + 1]));
	if ((str[i] == END || str[i] == PIP) && \
	(str[g] == END || str[g] == PIP))
		return (ft_change_1(str[g], str[g + 1]));
	if (str[i] == OUTOUT || str[i] == OUT || \
	str[i] == ININ || str[i] == IN)
	{
		g = i++;
		i = ft_skip_sp(str, i, SP);
		if (!str[i])
			return (ft_change(str[g], 1));
		if (str[i] == END || str[i] == PIP)
			return (ft_change_1(str[i], str[i + 1]));
	}
	if (str[i] == OUTOUT || str[i] == OUT \
	|| str[i] == ININ || str[i] == IN)
		return (ft_change(str[i], 0));
	return (NULL);
}

static char	*ft_check_char_1(char *str, int i)
{
	if (str[i] == END && str[i + 1] == END)
		return (ft_strdup(";;"));
	if (str[i] == PIP && str[i + 1] == PIP)
		return (ft_strdup("||"));
	i = ft_skip_sp(str, i + 1, SP);
	if (str[i] == END && str[i + 1] == END)
		return (ft_strdup(";;"));
	if (str[i] == PIP && str[i + 1] == PIP)
		return (ft_strdup("||"));
	if (str[i] == END)
		return (ft_strdup(";"));
	if (str[i] == PIP)
		return (ft_strdup("|"));
	return (NULL);
}

static int	ft_find_to(char *str, int i)
{
	int	g;

	g = i;
	while (str[i] && str[i] != OUTOUT && str[i] != OUT && \
	str[i] != ININ && str[i] != IN && str[i] != END && str[i] != PIP)
		i++;
	if (!str[i])
		return (g);
	return (i);
}

static int	ft_check_first(char *str, t_shell *shell)
{
	int		i;
	char	*g;

	i = ft_skip_sp(str, 0, SP);
	if (str[i] == END || str[i] == PIP)
		return (ft_puterror_1(ft_change_1(str[i], str[i + 1]), shell));
	while (str[i])
	{
		i = ft_skip_sp(str, i, SP);
		i = ft_find_to(str, i);
		if (str[i] == END || str[i] == PIP)
			g = ft_check_char_1(str, i);
		else
			g = ft_check_char_2(str, i);
		if (g != NULL)
			return (ft_puterror_1(g, shell));
		if (!str[i])
			break ;
		i++;
	}
	return (1);
}

int	ft_check_comand(char *str, t_shell *shell)
{
	int	check;

	check = ft_check_first(str, shell);
	if (check != 1)
		return (check);
	return (1);
}
