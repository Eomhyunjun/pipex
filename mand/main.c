/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 12:49:27 by heom              #+#    #+#             */
/*   Updated: 2021/06/10 20:23:32 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int
	main(int argc, char **argv, char **env)
{
	int	i;
	(void) argv;
	(void) env;

	i = 0;
	all()->proc_num = argc - 3;
	all()->argv = argv;
	all()->env = env;
	malloc_fd();
	// heom todo: argc num check
	make_pipe();
	fork_loop(argv);
	char buf[1024] = "buff one loop man!";
	char buf2[1024];
	i = 0;
	while (i < all()->proc_num)
	{
		printf("%d %d\n", all()->fd[i][0], all()->fd[i][1]);
		i++;
	}
	write(all()->fd[0][1], buf, 1024);
	read(all()->fd[all()->proc_num - 1][0], buf2, 1024);
	printf("%s\n", buf2);
	safe_exit(0, NULL);
	return (0);
}
