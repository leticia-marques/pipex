/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:52:26 by lemarque          #+#    #+#             */
/*   Updated: 2022/01/12 10:52:27 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

int	ft_strcmp(char *str, char *str2)
{
	while (*str && *str2)
	{
		if (*str != *str2)
			return (-1);
		str++;
		str2++;
	}
	return (0);
}
