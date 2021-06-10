/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 12:49:27 by heom              #+#    #+#             */
/*   Updated: 2021/06/10 19:09:38 by heom             ###   ########.fr       */
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
	malloc_fd();
	// heom todo: argc num check
	make_pipe();
	fork_loop(argv, env);
	char buf[1024] = "버프 한바퀴";
	// int readed = read(0, buf, 1024);
	i = 0;
	while (i < all()->proc_num)
	{
		printf("%d %d\n", all()->fd[i][0], all()->fd[i][1]);
		i++;
	}


	write(all()->fd[0][1], buf, 10);
	read(all()->fd[all()->proc_num - 1][0], buf, 1024);
	printf("%s", buf);
	safe_exit(0, NULL);
	return (0);
}
