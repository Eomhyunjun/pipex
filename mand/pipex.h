/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 12:45:50 by heom              #+#    #+#             */
/*   Updated: 2021/06/10 20:36:21 by heom             ###   ########.fr       */
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
fork_loop();

void
safe_exit(int code, const char *msg);

/*
**-----------------split
*/
char
**px_split(char const *s, char c);

char
*px_strjoin(char const *s1, char const *mid, char const *s2);

unsigned int
px_strlcpy(char *dest, char *src, unsigned int size);

#endif
