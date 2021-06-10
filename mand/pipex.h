/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 12:45:50 by heom              #+#    #+#             */
/*   Updated: 2021/06/10 19:10:41 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> // should delete!
# include "types.h"

t_all
*all(void);

void
malloc_fd(void);

void
make_pipe(void);

void
fork_loop(char **argv, char **env);

void
do_child(int id, char *argv, char **env);

void
safe_exit(int code, const char *msg);


#endif
