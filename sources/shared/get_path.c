/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 21:57:55 by lemarque          #+#    #+#             */
/*   Updated: 2021/12/24 21:36:32 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

static int	add_slash(char **splitted_path)
{
	char	*tmp;
	int		i;

	i = 0;
	while (splitted_path[i] != NULL)
	{
		tmp = splitted_path[i];
		splitted_path[i] = ft_strjoin(tmp, "/");
		if (splitted_path == NULL)
		{
			splitted_path[i] = tmp;
			return (-1);
		}
		free (tmp);
		i++;
	}
	return (0);
}

static char	**split_path(char *path)
{
	char	**splitted_path;

	splitted_path = ft_split(path, ':');
	return (splitted_path);
}

static char	*extract_path(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			path = ft_strdup(&envp[i][5]);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	**get_path(char **envp)
{
	char	*path;
	char	**splitted_path;

	if (envp == NULL)
		return (NULL);
	path = extract_path(envp);
	if (path != NULL)
	{
		splitted_path = split_path(path);
		free(path);
		if (add_slash(splitted_path) == -1)
		{
			ft_split_free(splitted_path);
			return (NULL);
		}
		return (splitted_path);
	}
	return (NULL);
}
