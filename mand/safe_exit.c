/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:49:42 by heom              #+#    #+#             */
/*   Updated: 2021/06/10 20:17:57 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void
	put_str(int	fd, const char* s)
{
	while (s)
	{
		write(fd, s, 1);
		s++;
	}
}

void
	safe_exit(int code, const char *msg)
{
	int	i;
	int	**fd;

	fd = all()->fd;
	if (fd)
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
	if (msg && msg[0])
		put_str(2, msg);
	exit(code);
}
