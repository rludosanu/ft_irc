/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 11:16:16 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

int				msg_read(t_server *srv, t_client *clt)
{
	char		buf[MSGQ_SZ];
	int			ret;

	ret = recv(clt->sockfd, buf, MSGQ_SZ - 1, 0);
	if (ret <= 0)
	{
		channel_remove_client_all(&(srv->channels), clt->sockfd);
		client_ofree(&(srv->clients), clt->sockfd);
	}
	else
	{
		buf[ret] = '\0';
		msgq_enqueue(clt->msgq_read, buf);
		msgq_dequeue(srv, clt, clt->msgq_read, msg_parse);
	}
	return (ret);
}

static int		msg_send(t_server *srv, t_client *clt, char *msg)
{
	ssize_t		ret;
	int			head;
	size_t		shift;

	(void)srv;
	ret = send(clt->sockfd, msg, ft_strlen(msg), 0);
	head = clt->msgq_write->head;
	shift = 0;
	if ((size_t)ret != ft_strlen(msg))
	{
		while (shift++ < ft_strlen(msg) - (size_t)ret)
			head = (head - 1 < 0) ? MSGQ_SZ - 1 : head - 1;
		clt->msgq_write->head = head;
	}
	return (0);
}

void			msg_write(t_server *srv, t_client *clt)
{
	msgq_dequeue(srv, clt, clt->msgq_write, msg_send);
}
