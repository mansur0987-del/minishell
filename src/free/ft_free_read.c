/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:20:34 by armaxima          #+#    #+#             */
/*   Updated: 2022/03/25 12:40:26 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_free_line(char **str)
{
	free(*str);
	*str = NULL;
	return (0);
}

int	ft_free_path(char ***str)
{
	int	i;

	if (!(*str) || (*str) == NULL)
		return (0);
	i = 0;
	while ((*str)[i])
	{
		free((*str)[i]);
		i++;
	}
	free((*str));
	(*str) = NULL;
	return (0);
}

int	ft_free_exp(t_list **exp, int len)
{
	int		i;
	t_var	*var;

	i = 0;
	while (i < len)
	{
		var = (*exp)->content;
		free(var->var_name);
		free(var->value);
		*exp = (*exp)->next;
		i++;
	}
	ft_lstclear(exp, &free);
	exp = NULL;
	return (0);
}

int	ft_free_read(t_shell *shell)
{
	if (shell->path && shell->path != NULL)
		ft_free_path(&shell->path);
	if (shell->line && shell->line != NULL)
		free(shell->line);
	if (shell->command != NULL)
		ft_free_com(&shell->command);
	return (0);
}

int	ft_free_all(t_shell *shell)
{
	ft_free_read(shell);
	if (shell->exp != NULL)
		ft_free_exp(&shell->exp, shell->len_exp);
	return (0);
}
