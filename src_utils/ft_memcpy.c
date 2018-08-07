/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2016/07/18 18:10:13 by abossi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*c1;
	const char	*c2;

	c1 = (char *)dst;
	c2 = (const char *)src;
	while (n)
	{
		*c1++ = *c2++;
		n--;
	}
	return (dst);
}
