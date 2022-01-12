/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:26:21 by lemarque          #+#    #+#             */
/*   Updated: 2022/01/12 10:54:22 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

static void	clear_args(t_args *args, char *cmd_path, char **cmd_args)
{
	free(cmd_path);
	ft_split_free(cmd_args);
	ft_split_free(args->path);
}

static void	child_process(t_args *args, char *cmd_path, char **cmd_args)
{
	int	id;
	int	fd[2];

	if (pipe(fd) == -1)
		errors(args, 1);
	id = fork();
	if (id == -1)
		errors(args, 1);
	if (id == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execve(cmd_path, cmd_args, args->envp);
		clear_args(args, cmd_path, cmd_args);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(-1, NULL, WNOHANG);
	}
}

void	pipex_bonus(t_args *args, int index, int outfile)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(args->argv[index], ' ');
	cmd_path = find_command_path(args->path, cmd_args[0]);
	if (index < (args->argc - 2))
		child_process(args, cmd_path, cmd_args);
	else
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		execve(cmd_path, cmd_args, args->envp);
		clear_args(args, cmd_path, cmd_args);
	}
}
