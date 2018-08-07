/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_read.c                                      :+:      :+:    :+:   */
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
** Read message from server
*/

static int		msg_print(t_client *clt, char *msg)
{
	(void)clt;
	return (printf("%s", msg));
}

int				server_read(t_client *clt)
{
	char		buf[MSGQ_SZ];
	int			ret;

	ret = recv(clt->sockfd, buf, MSGQ_SZ - 1, 0);
	if (ret <= 0)
		return (-1);
	else
	{
		buf[ret] = '\0';
		msgq_enqueue(clt->msgq_read, buf);
		msgq_dequeue(clt, clt->msgq_read, msg_print);
	}
	return (ret);
}
