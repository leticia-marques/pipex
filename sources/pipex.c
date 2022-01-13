/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 21:57:58 by lemarque          #+#    #+#             */
/*   Updated: 2022/01/13 13:55:26 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

static void	child_process(t_args *args, int fd[2])
{
	int		file;
	char	**cmd_args;
	char	*cmd_path;

	file = open(args->argv[1], O_RDONLY);
	if (file == -1)
		errors(args, 1);
	dup2(file, 0);
	dup2(fd[1], 1);
	close(file);
	close(fd[0]);
	close(fd[1]);
	cmd_args = ft_split(args->argv[2], ' ');
	if (cmd_args == NULL)
		errors(args, 2);
	cmd_path = find_command_path(args->path, cmd_args[0]);
	if (cmd_path == NULL)
		errors_append(args, cmd_args, cmd_path, 1);
	if (execve(cmd_path, cmd_args, args->envp) == -1)
		errors_append(args, cmd_args, cmd_path, 2);
}

static void	parent_process(t_args *args, int fd[2])
{
	int		file;
	char	**cmd_args;
	char	*cmd_path;

	file = open(args->argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file == -1)
		errors(args, 1);
	dup2(fd[0], 0);
	dup2(file, 1);
	close(fd[0]);
	close(fd[1]);
	close(file);
	cmd_args = ft_split(args->argv[3], ' ');
	if (cmd_args == NULL)
		errors(args, 2);
	cmd_path = find_command_path(args->path, cmd_args[0]);
	if (cmd_path == NULL)
		errors_append(args, cmd_args, cmd_path, 1);
	if (execve(cmd_path, cmd_args, args->envp) == -1)
		errors_append(args, cmd_args, cmd_path, 2);
}

static void	pipex(t_args *args)
{
	int	fd[2];
	int	id;

	if (pipe(fd) == -1)
		errors(args, 1);
	id = fork();
	if (id == -1)
		errors(args, 1);
	if (id == 0)
		child_process(args, fd);
	else
	{
		waitpid(-1, NULL, WNOHANG);
		parent_process(args, fd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_args	args;

	if (argc < 5)
	{
		ft_putendl_fd("Wrong number of arguments", 2);
		return (1);
	}
	check_arguments(argv);
	args.argc = argc;
	args.argv = argv;
	args.envp = envp;
	args.path = get_path(envp);
	if (args.path == NULL)
	{
		ft_putendl_fd("Error: Path not found.", 2);
		return (1);
	}
	pipex(&args);
	ft_split_free(args.path);
	return (0);
}
