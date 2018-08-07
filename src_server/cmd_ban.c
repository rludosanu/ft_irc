/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ban.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 11:02:19 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

static int		channel_ban_client(t_channel *ch, int sockfd)
{
	int			i;

	i = 0;
	while (i < CHAN_BANMAX)
	{
		if (ch->bans[i] == -1)
		{
			ch->bans[i] = sockfd;
			return (0);
		}
		i++;
	}
	return (-1);
}

static char		*ban_send(t_channel *ch, t_client *clt, t_client *tgt)
{
	if (clt->sockfd == tgt->sockfd)
		return (ERR_UNAUTHSELFKICK);
	if (channel_is_banned(ch, tgt->sockfd))
		return (ERR_ALREADYBANNED);
	if (channel_ban_client(ch, tgt->sockfd) == -1)
		return (ERR_CANNOTBEBANNED);
	if (channel_remove_client(ch, tgt->sockfd) == -1)
		return (ERR_NOTONCHANNEL);
	msgq_enqueue(tgt->msgq_write, "@");
	msgq_enqueue(tgt->msgq_write, clt->nick);
	msgq_enqueue(tgt->msgq_write, " banned you from channel ");
	msgq_enqueue(tgt->msgq_write, ch->name);
	msgq_enqueue(tgt->msgq_write, "\n");
	return (NULL);
}

char			*cmd_ban(t_server *srv, t_client *clt, \
		char *channel, char *nickname)
{
	t_channel	*ch;
	t_client	*cl;

	if (!channel || !ft_strlen(channel))
		return (ERR_NOCHANNELGIVEN);
	else if (!nickname || !ft_strlen(nickname))
		return (ERR_NONICKNAMEGIVEN);
	else
	{
		if (!(ch = channel_find(srv->channels, channel)))
			return (ERR_NOSUCHCHANNEL);
		if (!(cl = client_find(srv->clients, nickname)))
			return (ERR_NOSUCHNICK);
		if (!channel_is_admin(ch, clt->sockfd))
			return (ERR_CHANOPRIVSNEEDED);
		return (ban_send(ch, clt, cl));
	}
}
