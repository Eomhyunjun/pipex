/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 20:12:17 by heom              #+#    #+#             */
/*   Updated: 2021/06/10 20:37:28 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int
	px_strlen(char const *s)
{
	int	i;

	if (s == 0)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char
	*px_strjoin(char const *s1, char const *mid, char const *s2)
{
	char	*bottle;
	int		i;

	i = 0;
	if ((s1 == 0) || (s2 == 0) || (mid == 0))
		return (0);
	if (!(bottle = (char *)malloc(sizeof(char) *
					(px_strlen(s1) + px_strlen(s2) + px_strlen(mid) + 1))))
		return (NULL);
	while (*s1)
		bottle[i++] = *s1++;
	while (*mid)
		bottle[i++] = *mid++;
	while (*s2)
		bottle[i++] = *s2++;
	bottle[i] = '\0';
	return (bottle);
}
