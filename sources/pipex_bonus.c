/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:26:09 by lemarque          #+#    #+#             */
/*   Updated: 2022/01/12 10:53:59 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

static void	open_files(t_args *args, int type, int *outfile, int *infile)
{
	if (type == 1)
	{
		*outfile = open(args->argv[args->argc - 1], O_CREAT | O_WRONLY
				| O_APPEND, 0664);
		if (*outfile == -1)
			errors(args, 1);
	}
	else if (type == 2)
	{
		*infile = open(args->argv[1], O_RDONLY);
		*outfile = open(args->argv[args->argc - 1], O_CREAT | O_WRONLY
				| O_TRUNC, 0664);
		if (*outfile == -1 || *infile == -1)
			errors(args, 1);
	}
}

static void	here_doc(t_args *args)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		errors(args, 1);
	line = get_next_line(0);
	while (line != NULL && ft_strcmp(line, args->argv[2]) != 0)
	{
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	if (line)
		free(line);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

static void	set_index(int argc, char **argv, t_args *args)
{
	int		index;
	int		outfile;
	int		infile;

	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		index = 3;
		here_doc(args);
		open_files(args, 1, &outfile, &infile);
	}
	else
	{
		index = 2;
		open_files(args, 2, &outfile, &infile);
		dup2(infile, STDIN_FILENO);
	}
	while (++index <= (argc - 2))
		pipex_bonus(args, index, outfile);
}

int	main(int argc, char **argv, char **envp)
{
	t_args	args;

	check_arguments(argv);
	args.argv = argv;
	args.argc = argc;
	args.envp = envp;
	args.path = get_path(envp);
	if (argc >= 5)
		set_index(argc, argv, &args);
	else
		errors(&args, 3);
}
