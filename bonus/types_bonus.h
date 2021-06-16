/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 12:46:17 by heom              #+#    #+#             */
/*   Updated: 2021/06/16 13:24:50 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_BONUS_H
# define TYPES_BONUS_H

typedef struct	s_all
{
	int		**fd;
	long	proc_num;
	char	**env;
	char	**argv;
	int		rfd;
	int		wfd;
	char	**paths;
	char	**new_argv;
	pid_t	*pid;
}				t_all;

#endif
