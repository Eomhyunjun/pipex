/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:00:26 by heom              #+#    #+#             */
/*   Updated: 2021/06/11 16:38:58 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char
	**get_paths(void)
{
	int		i;
	char	*s;

	i = 0;
	while (all()->env[i])
	{
		s = all()->env[i];
		if (s[0] == 'P' && s[1] == 'A' &&
			s[2] == 'T' && s[3] == 'H' &&
			s[4] == '=')
			return (px_split(&s[5], ':'));
		i++;
	}
	return (NULL);
}

int
	try_execve_loop(char *raw_cmd)
{
	char	**new_argv;
	int		ret;
	char	*exec_path;
	char	**paths;
	int		i;

	ret = -1;
	i = 0;
	new_argv = px_split(raw_cmd, ' ');
	paths = get_paths(); // need free
	while (new_argv[i])
	{
		printf("new_argv: %s\n", new_argv[i]);
		i++;
	}
	i = 0;
	while (ret == -1 && paths[i])
	{
		exec_path = px_strjoin(paths[i], "/", new_argv[0]);
		ret = execve(exec_path, new_argv, all()->env);
		i++;
	}
	if (all()->rfd != 0)
		close(all()->rfd);
	if (all()->wfd != 0)
		close(all()->wfd);
	dprintf(2, "%d\n", ret); // should delete!
	return (ret);
}

void
	do_child(int id, char *raw_cmd)
{
	if (id == 0)
	{
		// dup2(all()->rfd, STDIN_FILENO);
		dup2(all()->fd[id][0], STDIN_FILENO);
		dup2(all()->fd[id + 1][1], STDOUT_FILENO);
		close(all()->fd[id][1]);
		close(all()->fd[id + 1][0]);
	}
	if (id > 0 && id < all()->proc_num - 1)
	{
		dup2(all()->fd[id][0], STDIN_FILENO);
		dup2(all()->fd[id + 1][1], STDOUT_FILENO);
		close(all()->fd[id][1]);
		close(all()->fd[id + 1][0]);
	}
	else
	{
		dup2(all()->fd[id][0], STDIN_FILENO);
		// dup2(all()->wfd, STDOUT_FILENO);
		printf("last\n");
		close(all()->fd[id][1]);
	}
	if (!try_execve_loop(raw_cmd))
	{
		write(1, "", 1);
		safe_exit(1, "file not found");
	}
	printf("heom no one left\n");
}

void
	fork_loop()
{
	int		i;

	i = 0;
	while (i < all()->proc_num)
	{
		all()->pid[i] = fork();
		if (all()->pid[i] == -1)
			safe_exit(1, "fork error!\n");
		if (all()->pid[i] == 0)
			do_child(i, all()->argv[i + 2]);
		i++;
		printf("heom hello2\n");
	}
}
