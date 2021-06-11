/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 12:49:27 by heom              #+#    #+#             */
/*   Updated: 2021/06/11 19:46:01 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h> // should delete!
#include <errno.h>
#include <string.h>

void
	validate(int argc, char **argv)
{
	(void)argv;
	if (argc != 5)
		exit_code_msg(1, "invalid arg");
}

void
	all_init(int argc, char **argv, char **env)
{
	all()->proc_num = argc - 3;
	all()->argv = argv;
	all()->env = env;
	all()->pid = malloc(sizeof(pid_t) * all()->proc_num);
	if ((all()->rfd = open(argv[1], O_RDWR, 0664)) == -1)
		safe_exit(1, "file1 name is invalid");
	if ((all()->wfd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0664)) == -1) //bonus O_APPEND
	{
		printf("%s\n", strerror(errno));
		safe_exit(1, "file2 name is invalid");
	}
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
	while(read_size > 0)
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
	read_file();
	fork_loop(argv);
	i = 0;
	while (i < all()->proc_num)
	{
		close(all()->fd[i][0]);
		close(all()->fd[i][1]);
		i++;
	}
	close(all()->wfd);
	// char buf[1024] = "buff one loop man!\n";
	// write(all()->fd[0][1], buf, 19);
	// char c = 26;
	// write(all()->fd[0][1], &c, 1);
	// close(all()->fd[0][1]);
	wait_subprocess();

	// usleep(1000 * 1000);
	// while (i < all()->proc_num)
	// {
	// 	printf("killing! %d\n", all()->pid[i]);
	// 	kill(all()->pid[i], SIGINT);
	// 	i++;
	// }

	// char buf[1024] = "buff one loop man!";
	// char buf2[1024];
	// i = 0;
	// while (i < all()->proc_num)
	// {
	// 	printf("pipe_num : %d %d\n", all()->fd[i][0], all()->fd[i][1]);
	// 	i++;
	// }
	// // write(all()->fd[0][1], buf, 1024);
	// // read(all()->fd[all()->proc_num - 1][0], buf2, 1024);
	// printf("%s\n", buf2);

	// safe_exit(0, NULL);

	return (0);
}
