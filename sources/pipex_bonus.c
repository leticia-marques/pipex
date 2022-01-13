/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:26:21 by lemarque          #+#    #+#             */
/*   Updated: 2022/01/13 12:01:48 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

static void	child_process(t_args *args, char *cmd_path, char **cmd_args, \
			int fd[2])
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (!cmd_path)
	{
		ft_putendl_fd("error: command not found", 2);
		errors_append(args, cmd_args, cmd_path, 3);
	}
	execve(cmd_path, cmd_args, args->envp);
	errors_append(args, cmd_args, cmd_path, 3);
}

void	parent_process(char *cmd_path, char **cmd_args, int fd[2])
{
	waitpid(-1, NULL, WNOHANG);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(cmd_path);
	ft_split_free(cmd_args);
}

void	exec_last_cmd(char *cmd_path, char **cmd_args, t_args *args, \
		int outfile)
{
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	if (!cmd_path)
	{
		ft_putendl_fd("error: command not found", 2);
		errors_append(args, cmd_args, cmd_path, 3);
	}
	execve(cmd_path, cmd_args, args->envp);
	errors_append(args, cmd_args, cmd_path, 3);
}

static void	call_processes(t_args *args, char *cmd_path, char **cmd_args)
{
	int	fd[2];
	int	id;

	if (pipe(fd) == -1)
	{
		free(cmd_path);
		ft_split_free(cmd_args);
		errors(args, 1);
	}
	id = fork();
	if (id == -1)
	{
		free(cmd_path);
		ft_split_free(cmd_args);
		errors(args, 1);
	}
	if (id == 0)
		child_process(args, cmd_path, cmd_args, fd);
	else
		parent_process(cmd_path, cmd_args, fd);
}

void	pipex_bonus(t_args *args, int index, int outfile)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(args->argv[index], ' ');
	if (!cmd_args)
	{
		ft_putendl_fd("error: Command failed", 2);
		if (index >= args->argc - 2)
		{
			ft_split_free(args->path);
			exit(EXIT_FAILURE);
		}
		return ;
	}
	cmd_path = find_command_path(args->path, cmd_args[0]);
	if (index < (args->argc - 2))
		call_processes(args, cmd_path, cmd_args);
	else
		exec_last_cmd(cmd_path, cmd_args, args, outfile);
}
