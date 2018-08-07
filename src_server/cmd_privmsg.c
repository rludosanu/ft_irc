/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_privmsg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2016/07/18 18:10:13 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

static void		send_privmsg_client(t_client *from, t_client *to, char *msg)
{
	msgq_enqueue(to->msgq_write, "<");
	msgq_enqueue(to->msgq_write, from->nick);
	msgq_enqueue(to->msgq_write, "> ");
	msgq_enqueue(to->msgq_write, msg);
	msgq_enqueue(to->msgq_write, "\n");
}

static void		send_privmsg_channel(t_server *srv, t_client *clt, \
	t_channel *ch, char *msg)
{
	int			i;
	t_client	*c;

	i = 0;
	while (i < CHAN_CLTMAX)
	{
		if (ch->clients[i] != -1 && ch->clients[i] != clt->sockfd)
		{
			c = srv->clients;
			while (c != NULL)
			{
				if (c->sockfd == ch->clients[i])
					send_privmsg_client(clt, c, msg);
				c = c->next;
			}
		}
		i++;
	}
}

char			*cmd_privmsg(t_server *srv, t_client *clt, \
	char *dst, char *msg)
{
	t_channel	*ch;
	t_client	*cl;

	if (!dst || !ft_strlen(dst))
		return (ERR_NORECIPIENT);
	else if (!msg || !ft_strlen(msg))
		return (ERR_NOMESSAGE);
	else if (dst[0] == '#')
	{
		if (!(ch = channel_find(srv->channels, dst)))
			return (ERR_NOSUCHCHANNEL);
		else if (!channel_find_client(ch, clt->sockfd))
			return (ERR_NOTONCHANNEL);
		send_privmsg_channel(srv, clt, ch, msg);
	}
	else
	{
		if (!(cl = client_find(srv->clients, dst)))
			return (ERR_NOSUCHNICK);
		send_privmsg_client(clt, cl, msg);
	}
	return (NULL);
}
