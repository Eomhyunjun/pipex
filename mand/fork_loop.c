/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:00:26 by heom              #+#    #+#             */
/*   Updated: 2021/06/10 20:32:15 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char
	**get_paths(void)
{
	int		i;
	int		j;
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

	ret = -1;
	new_argv = px_split(raw_cmd, ' ');
	paths = get_paths(); // need free
	while (ret == -1)
	{

		exec_path = px_strjoin(_____, raw_cmd);
		ret = execve(exec_path, new_argv, all()->env);
	}
	dprintf(2, "%d\n", ret);
	return (ret);
}

void
	do_child(int id, char *raw_cmd)
{
	char	**new_argv;
	int		size;

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
	if (!try_execev_loop())
	{
		write(1, "", 1);
		safe_exit(1, "file not found");
	}
}

void
	fork_loop()
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < all()->proc_num)
	{
		pid = fork();
		if (pid == -1)
			safe_exit(1, "fork error!\n");
		if (pid == 0)
			do_child(i, all()->argv[i + 2]);
		i++;
	}
}
