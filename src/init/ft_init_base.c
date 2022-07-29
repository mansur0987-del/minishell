/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armaxima <<armaxima@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:09:54 by armaxima          #+#    #+#             */
/*   Updated: 2022/03/17 17:09:32 by armaxima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_init_base(t_shell *shell)
{
	char	*str;

	str = get_env_var("SHLVL", shell);
	shell->shlvl = ft_atoi(str) + 1;
	free(str);
	shell->err_cod = 0;
	shell->path = NULL;
	str = get_env_var("PATH", shell);
	if (str != NULL)
	{
		shell->path = ft_split(str, ':');
		free(str);
		if (shell->path == NULL)
			return (0);
	}
	return (1);
}
