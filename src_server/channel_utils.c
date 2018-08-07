/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 12:28:36 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

int				channel_remove_client(t_channel *ch, int sockfd)
{
	int			i;
	int			r;

	r = -1;
	i = 0;
	while (i < CHAN_CLTMAX)
	{
		if (ch->clients[i] == sockfd)
		{
			ch->clients[i] = -1;
			r = 0;
		}
		i++;
	}
	i = 0;
	while (i < CHAN_ADMMAX)
	{
		if (ch->admins[i] == sockfd)
		{
			ch->admins[i] = -1;
			r = 0;
		}
		i++;
	}
	return (r);
}

int				channel_count_clients(t_channel *ch)
{
	int			i;
	int			c;

	if (ch == NULL)
		return (0);
	i = 0;
	c = 0;
	while (i < CHAN_CLTMAX)
	{
		if (ch->clients[i] != -1)
			c++;
		i++;
	}
	return (c);
}

int				channel_find_client(t_channel *ch, int sockfd)
{
	int			i;

	if (ch == NULL)
		return (1);
	i = 0;
	while (i < CHAN_CLTMAX)
		if (ch->clients[i++] == sockfd)
			return (1);
	return (0);
}

t_channel		*channel_find(t_channel *head, char *name)
{
	t_channel	*ch;

	ch = head;
	while (ch != NULL)
	{
		if (ft_strequ(ch->name, name))
			return (ch);
		ch = ch->next;
	}
	return (NULL);
}
