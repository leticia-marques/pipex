/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 00:49:01 by lemarque          #+#    #+#             */
/*   Updated: 2022/01/09 10:08:50 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include"utils.h"

typedef struct s_args
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**path;
}				t_args;

void	errors(t_args *args, int code);
void	errors_append(t_args *args, char **cmd_args, char *path, int code);
char	*find_command_path(char **path, char *cmd);
char	**get_path(char **envp);
void	check_arguments(char **argv);

#endif
