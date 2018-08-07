/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_is.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 11:18:04 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

int			channel_is_banned(t_channel *ch, int sockfd)
{
	int		i;

	i = 0;
	while (i < CHAN_BANMAX)
	{
		if (ch->bans[i] == sockfd)
			return (1);
		i++;
	}
	return (0);
}

int			channel_is_admin(t_channel *ch, int sockfd)
{
	int		i;

	i = 0;
	while (i < CHAN_ADMMAX)
	{
		if (ch->admins[i] == sockfd)
			return (1);
		i++;
	}
	return (0);
}
