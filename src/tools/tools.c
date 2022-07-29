/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:31:22 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/24 20:09:18 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

char	*make_full_path(char *path, char *cmd)
{
	char	*full_path;
	char	*tmp_str;

	tmp_str = ft_strjoin(path, "/");
	if (!tmp_str)
		return (tmp_str);
	full_path = ft_strjoin(tmp_str, cmd);
	free (tmp_str);
	return (full_path);
}

char	*make_home_path(t_shell *shell)
{
	char	*home;
	char	*full_path;

	home = get_env_var("HOME", shell);
	full_path = ft_strjoin(home, "/tmp.tpm");
	free(home);
	return (full_path);
}
