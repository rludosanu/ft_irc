/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 11:05:16 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

static int			is_channel_valid(char *name)
{
	if (name[0] != '#')
		return (0);
	else if (ft_strchr(name, ' '))
		return (0);
	else if (ft_strchr(name, ','))
		return (0);
	else if (ft_strchr(name, 7))
		return (0);
	else
		return (1);
}

static int			channel_add_client(t_channel *ch, int sockfd)
{
	int				i;

	i = 0;
	if (ch != NULL)
	{
		while (i < CHAN_CLTMAX)
		{
			if (ch->clients[i] == -1)
			{
				ch->clients[i] = sockfd;
				return (0);
			}
			i++;
		}
	}
	return (-1);
}

static char			*check_channel_name(char *name)
{
	if (!name || !ft_strlen(name))
		return (ERR_NOCHANNELGIVEN);
	else if (ft_strlen(name) > CHAN_NAMESZ)
		return (ERR_CHANNELTOOLONG);
	else if (!is_channel_valid(name))
		return (ERR_ERRCHANNELNAME);
	else
		return (NULL);
}

char				*cmd_join(t_server *srv, t_client *clt, char *name)
{
	t_channel		*ch;
	char			*ret;

	if ((ret = check_channel_name(name)))
		return (ret);
	if (!(ch = channel_find(srv->channels, name)))
	{
		if (!(ch = channel_create(name, clt->sockfd)))
			return (ERR_CHANNELNOTCREATED);
		channel_add(&(srv->channels), ch);
	}
	else
	{
		if (channel_is_banned(ch, clt->sockfd))
			return (ERR_BANNEDFROMCHAN);
		else if (channel_find_client(ch, clt->sockfd))
			return (ERR_USERONCHANNEL);
		else if (channel_add_client(ch, clt->sockfd) == -1)
			return (ERR_CHANNELISFULL);
	}
	return (NULL);
}
