/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 21:57:53 by lemarque          #+#    #+#             */
/*   Updated: 2021/12/24 21:35:11 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

char	*find_command_path(char **path, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/') != NULL && access(cmd, F_OK | X_OK) == 0)
	{
		cmd_path = ft_strdup(cmd);
		return (cmd_path);
	}
	while (path[i] != NULL)
	{
		cmd_path = ft_strjoin(path[i], cmd);
		if (cmd_path == NULL)
		{
			i++;
			continue ;
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}
