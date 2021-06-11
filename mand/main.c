/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 12:49:27 by heom              #+#    #+#             */
/*   Updated: 2021/06/11 16:44:15 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h> // should delete!

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

	// if ((all()->rfd = open(argv[1], O_RDONLY)) == -1)
	// 	safe_exit(1, "file1 name is invalid");
	// if ((all()->wfd = open(argv[argc - 1], O_WRONLY | O_CREAT)) == -1) //bonus O_APPEND
	// 	safe_exit(1, "file2 name is invalid");
}

void
	wait_subprocess(void)
{
	int	i;
	// int	res;

	i = 0;
	while (i < all()->proc_num)
	{
		printf("waiting! %d\n", all()->pid[i]);

		// if ((all()->pid[i], &res, 0) == -1)
		// 	safe_exit(1, "waitpid error");
		i++;
	}
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
	char buf[1024] = "buff one loop man!\n";
	write(all()->fd[0][1], buf, 19);
	char c = 26;
	write(all()->fd[0][1], &c, 1);
	close(all()->fd[0][1]);
	wait_subprocess();

	usleep(1000 * 1000);
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
