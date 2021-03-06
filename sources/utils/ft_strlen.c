/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 01:09:20 by lemarque          #+#    #+#             */
/*   Updated: 2021/12/24 21:38:53 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	s;

	s = 0;
	while (*str)
	{
		str++;
		s++;
	}
	return (s);
}
