/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 19:35:59 by heom              #+#    #+#             */
/*   Updated: 2021/06/10 19:55:43 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "mand/pipex.h"
#include <errno.h>
#include <string.h>

void print_fd()
{
	int i;
	i = 0;
	while (i++ < all()->proc_num)
	{
		printf("%d %d\n", all()->fd[i][0], all()->fd[i][1]);
	}
}
int	main(void)
{
	int size;
	char **o;
	int res;

	o = px_split("~/pipex/test.sh", ' ', &size);

	res = execve("~/pipex/test.sh", o, o);
	printf("%d %s\n", res, strerror(errno));
	return (0);
}
