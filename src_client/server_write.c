/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2016/07/18 18:10:13 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "utils.h"

/*
** Send message to server
*/

static int		msg_send(t_client *clt, char *msg)
{
	ssize_t		ret;
	int			head;
	size_t		shift;

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

void			server_write(t_client *clt)
{
	msgq_dequeue(clt, clt->msgq_write, msg_send);
}
