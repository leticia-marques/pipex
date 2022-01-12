/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 00:48:54 by lemarque          #+#    #+#             */
/*   Updated: 2022/01/09 10:08:13 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include"shared.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

int		main(int argc, char **argv, char **envp);
char	*get_next_line(int fd);
void	pipex_bonus(t_args *args, int index, int outfile);
#endif
