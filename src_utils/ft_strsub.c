/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2016/07/18 18:10:13 by abossi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strsub(char *src, int head, int tail)
{
	char	*dst;
	int		i;

	if (head > tail)
		return (NULL);
	if (!(dst = (char *)malloc(sizeof(char) * (tail - head + 1))))
		return (NULL);
	i = 0;
	while (head != tail)
		dst[i++] = src[head++];
	dst[i] = '\0';
	return (dst);
}
