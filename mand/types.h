/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 12:46:17 by heom              #+#    #+#             */
/*   Updated: 2021/06/11 15:21:08 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct	s_all
{
	int		**fd;
	long	proc_num;
	char	**env;
	char	**argv;
	int		rfd;
	int		wfd;
	pid_t	*pid;
}				t_all;

#endif
