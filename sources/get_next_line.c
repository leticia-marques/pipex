/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:26:18 by lemarque          #+#    #+#             */
/*   Updated: 2022/01/12 10:54:51 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	free_ptr(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

static char	*gets_the_crumbs(char **crumbs)
{
	char	*line;
	size_t	buffer_len;
	char	*temp_crumbs;

	buffer_len = 0;
	while ((*crumbs)[buffer_len] != '\n')
		buffer_len++;
	buffer_len++;
	line = ft_substr(*crumbs, 0, buffer_len);
	temp_crumbs = *crumbs;
	*crumbs = ft_strdup(&(*crumbs)[buffer_len]);
	free_ptr(&temp_crumbs);
	return (line);
}

static int	till_line_break(int fd, char **crumbs, char **buffer)
{
	int		i;
	char	*join_crumbs;

	i = 1;
	join_crumbs = NULL;
	while (!ft_strchr(*crumbs, '\n') && i)
	{
		i = read(fd, *buffer, BUFFER_SIZE);
		if (i <= 0)
			return (i);
		(*buffer)[i] = '\0';
		join_crumbs = *crumbs;
		*crumbs = ft_strjoin(join_crumbs, *buffer);
		free_ptr(&join_crumbs);
	}
	return (i);
}

static void	*get_each_line(int fd, char **buffer, char **crumbs)
{
	char	*join_crumbs;
	int		i;

	i = till_line_break(fd, crumbs, buffer);
	if (ft_strchr(*crumbs, '\n'))
		return (gets_the_crumbs(crumbs));
	if (i <= 0 && !**crumbs)
	{
		free_ptr(crumbs);
		return (NULL);
	}
	join_crumbs = ft_strdup(*crumbs);
	free_ptr(crumbs);
	return (join_crumbs);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*crumbs;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = (char *) malloc(BUFFER_SIZE + 1);
	if (!crumbs)
		crumbs = ft_strdup("");
	line = get_each_line(fd, &buffer, &crumbs);
	free_ptr(&buffer);
	free_ptr(&crumbs);
	return (line);
}
