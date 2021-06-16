/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:49:42 by heom              #+#    #+#             */
/*   Updated: 2021/06/16 12:51:28 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void
	put_str(int fd, const char *s)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}

void
	exit_code_msg(int code, const char *msg)
{
	if (msg && msg[0])
		put_str(2, msg);
	exit(code);
}

void
	free_fd(void)
{
	int	**fd;
	int	i;

	if ((fd = all()->fd))
	{
		i = 0;
		while (i < all()->proc_num)
		{
			if (fd[i])
			{
				free(fd[i]);
				fd[i] = 0;
			}
			i++;
		}
		free(fd);
		all()->fd = 0;
	}
}

void
	safe_exit(int code, const char *msg)
{
	free_fd();
	free_px_split(all()->new_argv);
	free_px_split(all()->paths);
	if (all()->rfd != 0)
		close(all()->rfd);
	if (all()->wfd != 0)
		close(all()->wfd);
	if (all()->pid != 0)
	{
		free(all()->pid);
		all()->pid = 0;
	}
	exit_code_msg(code, msg);
}
