/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 12:49:27 by heom              #+#    #+#             */
/*   Updated: 2021/06/14 19:30:09 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
#include <string.h>

void
	validate(int argc, char **argv)
{
	(void)argv;
	if (argc != 5)
		exit_code_msg(1, "Invalid arg");
}

void
	all_init(int argc, char **argv, char **env)
{
	all()->proc_num = argc - 3;
	all()->argv = argv;
	all()->env = env;
	all()->pid = malloc(sizeof(pid_t) * all()->proc_num);
	if ((all()->rfd = open(argv[1], O_RDWR, 0664)) == -1)
		safe_exit(1, "Invalid file1");
	if ((all()->wfd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0664)) \
		== -1)
		safe_exit(1, "Invalid file2");
}

void
	wait_subprocess(void)
{
	int	i;
	int	res;

	i = 0;
	while (i < all()->proc_num)
	{
		if (waitpid(all()->pid[i], &res, 0) == -1)
			safe_exit(1, "waitpid error");
		i++;
	}
}

void
	read_file(void)
{
	int		read_size;
	char	buf[1024];

	read_size = 1;
	while (read_size > 0)
	{
		read_size = read(all()->rfd, buf, 1024);
		write(all()->fd[0][1], buf, read_size);
	}
	close(all()->fd[0][1]);
	close(all()->rfd);
}

int
	main(int argc, char **argv, char **env)
{
	int		i;

	i = 0;
	validate(argc, argv);
	all_init(argc, argv, env);
	malloc_fd();
	make_pipe();
	fork_loop(argv);
	read_file();
	i = 0;
	while (i < all()->proc_num)
	{
		close(all()->fd[i][0]);
		close(all()->fd[i][1]);
		i++;
	}
	close(all()->wfd);
	wait_subprocess();
	safe_exit(0, NULL);
	
	return (0);
}
