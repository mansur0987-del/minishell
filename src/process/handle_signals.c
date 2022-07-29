/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:58:00 by nmordeka          #+#    #+#             */
/*   Updated: 2022/04/03 18:50:06 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parent_signal(int signal)
{
	char	*str;

	str = NULL;
	if (signal == SIGINT)
	{
		str = ft_strdup(rl_line_buffer);
		rl_replace_line("", 1);
		rl_redisplay();
		write(0, PROMPT, ft_strlen(PROMPT));
		write(0, "  \b\b", 4);
		write(0, str, ft_strlen(str));
		free(str);
		write(0, "\n", 1);
		write(0, PROMPT, ft_strlen(PROMPT));
		g_exit = 1;
	}
}
