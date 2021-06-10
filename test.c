/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 19:35:59 by heom              #+#    #+#             */
/*   Updated: 2021/06/10 15:23:14 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "mand/pipex.h"

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

	int pc = 3;


}
