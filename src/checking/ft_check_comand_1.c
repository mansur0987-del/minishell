/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_comand_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 20:54:04 by armaxima          #+#    #+#             */
/*   Updated: 2022/03/16 10:02:16 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_change(char c, int i)
{
	char	*str;

	if (i)
		return (ft_strdup("newline"));
	if (c == OUTOUT)
		return (ft_strdup(">>"));
	if (c == OUT)
		return (ft_strdup(">"));
	if (c == ININ)
		return (ft_strdup("<<"));
	if (c == IN)
		return (ft_strdup("<"));
	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_change_1(char c, char d)
{
	if (c == END && d == END)
		return (ft_strdup(";;"));
	if (c == END)
		return (ft_strdup(";"));
	if (c == PIP && d == PIP)
		return (ft_strdup("||"));
	if (c == PIP)
		return (ft_strdup("|"));
	return (NULL);
}
