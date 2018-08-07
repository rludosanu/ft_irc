/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 17:20:43 by rludosan          #+#    #+#             */
/*   Updated: 2015/11/28 18:47:38 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int					ft_strcmp(const char *s1, const char *s2)
{
	int				x;
	unsigned char	*t1;
	unsigned char	*t2;

	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	x = 0;
	while (t1[x] != '\0' && t2[x] != '\0' && t1[x] == t2[x])
		x++;
	return (t1[x] - t2[x]);
}
