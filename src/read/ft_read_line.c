/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:06:03 by armaxima          #+#    #+#             */
/*   Updated: 2022/04/01 22:05:07 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_read_all(char *line)
{
	char	*prev;
	char	*prev_ent;

	prev = ft_strdup(line);
	free(line);
	if (prev == NULL)
		return (NULL);
	prev_ent = ft_strjoin(prev, "\n");
	free(prev);
	if (prev_ent == NULL)
		return (NULL);
	line = readline("> ");
	prev = ft_strjoin(prev_ent, line);
	free(line);
	free(prev_ent);
	return (prev);
}

static int	ft_pr_pip(char *str, int g, char c)
{
	int	i;

	i = 0;
	while (i < g)
	{
		if (str[i] == c && !(ft_shiel(str, i, '\\')))
		{
			i++;
			if (str[i] == c)
				i++;
			while (i < g && (str[i] == ' ' || str[i] == '\t' \
			|| str[i] == '\n'))
				i++;
		}
		if (i == g)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_pip(char *str)
{
	int	i;
	int	g;

	i = ft_strlen(str) - 1;
	g = -1;
	while (str[++g] && (str[g] == ' ' || str[g] == '\t' || str[g] == '\n'))
		g++;
	if (str[g] == '|')
		return (0);
	while (i > 0 && (str[i] == ' ' || str[i] == '\t' \
		|| str[i] == '\n'))
		i--;
	if (ft_shiel(str, i, '\\') || str[i] != '|' || \
	ft_pr_pip(str, i, '>') || ft_pr_pip(str, i, '<'))
		return (0);
	while (i > 0)
	{
		if ((str[i] == '|' || str[i] == ';') && (!(ft_shiel(str, i--, '\\'))))
			while (i > 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
				i--;
		if (i == 0 || str[i - 1] == '|' || str[i--] == '|')
			return (0);
	}
	return (1);
}

static int	ft_close(void)
{
	rl_replace_line("", 1);
	rl_redisplay();
	write(0, "exit\n", ft_strlen("exit\n"));
	return (0);
}

int	ft_read_line(t_shell *shell)
{
	int	check;

	shell->line = readline("minishell > ");
	if (shell->line == NULL)
		return (ft_close() + ft_free_path(&shell->path));
	while (ft_check_quotes(shell->line, '\'', '\"') % 2 || \
	ft_check_quotes(shell->line, '\"', '\'') % 2 || ft_check_pip(shell->line))
	{
		shell->line = ft_read_all(shell->line);
		if (shell->line == NULL)
			return (ft_free_path(&shell->path));
	}
	if (!(ft_strcmp(shell->line, "")))
		return (ft_free_line(&shell->line) + ft_free_path(&shell->path) \
		+ 2);
	add_history(shell->line);
	shell->line = ft_clear_quotes(shell->line, shell);
	if (shell->line == NULL)
		return (ft_free_path(&shell->path));
	check = ft_check_comand(shell->line, shell);
	if (!check || check != 1)
		return ((ft_free_line(&shell->line) + ft_free_path(&shell->path)) \
		+ check);
	return (1);
}
