/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_topic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2016/07/18 18:10:13 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

/*
** Check topic characters
*/

static int		is_topic_valid(char *topic)
{
	size_t		x;

	x = 0;
	while (x < ft_strlen(topic))
	{
		if (topic[x] < 32 || topic[x] > 126)
			return (0);
		x++;
	}
	return (1);
}

/*
** Send topic
*/

static char		*topic_send(t_channel *ch, t_client *clt)
{
	msgq_enqueue(clt->msgq_write, ch->name);
	msgq_enqueue(clt->msgq_write, " <");
	msgq_enqueue(clt->msgq_write, ch->topic);
	msgq_enqueue(clt->msgq_write, ">\n");
	return (NULL);
}

/*
** Update topic
*/

static char		*topic_update(t_channel *ch, t_client *clt, char *topic)
{
	if (ft_strlen(topic) > CHAN_TOPICSZ)
		return (ERR_TOPICTOOLONG);
	else if (!is_topic_valid(topic))
		return (ERR_ERRONEUSTOPIC);
	else if (!channel_is_admin(ch, clt->sockfd))
		return (ERR_CHANOPRIVSNEEDED);
	ft_memset(ch->topic, '\0', CHAN_TOPICSZ);
	ft_memcpy(ch->topic, topic, ft_strlen(topic));
	return (NULL);
}

/*
** Update / Send channel topic
*/

char			*cmd_topic(t_server *srv, t_client *clt, \
	char *channel, char *topic)
{
	t_channel	*ch;

	if (!channel || !ft_strlen(channel))
		return (ERR_NOCHANNELGIVEN);
	else
	{
		if (!(ch = channel_find(srv->channels, channel)))
			return (ERR_NOSUCHCHANNEL);
		if (!topic || !ft_strlen(topic))
			return (topic_send(ch, clt));
		else
			return (topic_update(ch, clt, topic));
	}
	return (NULL);
}
