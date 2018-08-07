/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2016/07/18 18:10:13 by abossi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strcatnl(char *dst, char *src)
{
	char	*tmp;

	tmp = ft_strcat(dst, src);
	tmp[ft_strlen(tmp)] = '\n';
	tmp[ft_strlen(tmp) + 1] = '\0';
	return (tmp);
}

char	*ft_strcatsp(char *dst, char *src)
{
	char	*tmp;

	tmp = ft_strcat(dst, src);
	tmp[ft_strlen(tmp)] = ' ';
	tmp[ft_strlen(tmp) + 1] = '\0';
	return (tmp);
}

char	*ft_strcat(char *dst, char *src)
{
	char	*tmp;

	tmp = dst;
	while (*dst != '\0')
		dst++;
	while (src != '\0')
		*dst++ = *src++;
	*dst = '\0';
	return (tmp);
}
