/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_who.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 11:10:55 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

static void		channel_list_clients(t_server *srv, t_client *clt, \
	t_channel *ch)
{
	t_client	*c;
	int			i;

	i = 0;
	msgq_enqueue_s(clt->msgq_write, ch->name, " ");
	while (i < CHAN_CLTMAX)
	{
		if (ch->clients[i] != -1)
		{
			c = srv->clients;
			while (c != NULL)
			{
				if (ch->clients[i] == c->sockfd)
				{
					if (channel_is_admin(ch, c->sockfd))
						msgq_enqueue(clt->msgq_write, "@");
					msgq_enqueue_s(clt->msgq_write, c->nick, " ");
				}
				c = c->next;
			}
		}
		i++;
	}
	msgq_enqueue(clt->msgq_write, "\n");
}

char			*cmd_who(t_server *srv, t_client *clt)
{
	t_channel	*ch;

	ch = srv->channels;
	while (ch != NULL)
	{
		if (channel_find_client(ch, clt->sockfd))
			channel_list_clients(srv, clt, ch);
		ch = ch->next;
	}
	return (NULL);
}
