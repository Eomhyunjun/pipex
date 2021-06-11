/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:00:26 by heom              #+#    #+#             */
/*   Updated: 2021/06/11 20:30:35 by heom             ###   ########.fr       */
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
	check_cmd(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '/')
			return (0);
		cmd++;
	}
	return (1);
}

char
	*try_execve_loop(char *raw_cmd)
{
	int		ret;
	char	*exec_path;
	int		i;

	ret = -1;
	// i = 0;
	all()->new_argv = px_split(raw_cmd, ' ');
	if (!(check_cmd(all()->new_argv[0])))
		return ("Invalid command");
	if (!(all()->paths = get_paths()))
		return ("PATH not specified");
	// while (all()->new_argv[i])
	// 	i++;
	i = 0;
	while (ret == -1 && all()->paths[i])
	{
		exec_path = px_strjoin(all()->paths[i], "/", all()->new_argv[0]);
		ret = execve(exec_path, all()->new_argv, all()->env);
		i++;
	}
	return ("Invalid command");
}

void
	do_child(int id, char *raw_cmd)
{
	int		i;
	char	*msg;
	if (id >= 0 && id < all()->proc_num - 1)
	{
		dup2(all()->fd[id][0], STDIN_FILENO);
		dup2(all()->fd[id + 1][1], STDOUT_FILENO);
	}
	else
	{
		dup2(all()->fd[id][0], STDIN_FILENO);
		dup2(all()->wfd, STDOUT_FILENO);
	}
	i = 0;
	while (i < all()->proc_num)
	{
		close(all()->fd[i][0]);
		close(all()->fd[i][1]);
		i++;
	}
	msg = try_execve_loop(raw_cmd);
	write(1, "", 1);
	safe_exit(1, msg);
}

void
	fork_loop()
{
	int		i;

	i = 0;
	while (i < all()->proc_num)
	{
		// printf("fork_loop");
		all()->pid[i] = fork();
		if (all()->pid[i] == -1)
			safe_exit(1, "fork error!\n");
		if (all()->pid[i] == 0)
			do_child(i, all()->argv[i + 2]);
		i++;
	}
}
