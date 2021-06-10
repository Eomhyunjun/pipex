/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:00:26 by heom              #+#    #+#             */
/*   Updated: 2021/06/10 19:11:17 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void
	do_child(int id, char *argv, char **env)
{
	(void)	argv;
	if (id >= 0 && id < all()->proc_num - 1)
	{
		dup2(all()->fd[id][0], STDIN_FILENO);
		dup2(all()->fd[id + 1][1], STDOUT_FILENO);
		close(all()->fd[id][1]);
		close(all()->fd[id + 1][0]);
	}
	else
	{
		dup2(all()->fd[id][0], STDIN_FILENO);
		close(all()->fd[id][1]);
	}
	char *argva[3];
	argva[0] = "cat";
	argva[1] = "test.c";
	argva[2] = NULL;
	execve("/bin/cat", argva, env);
	exit(0);
}

void
	fork_loop(char **argv, char **env)
{
	int	i;

	i = 0;
	while (i < all()->proc_num)
	{
		pid_t pid;
		pid = fork();
		if (pid == -1)
		{
			safe_exit(1, "fork error!\n");
		}
		if (pid == 0)
		{
			do_child(i, argv[i + 2], env);
		}
		i++;
	}
}
