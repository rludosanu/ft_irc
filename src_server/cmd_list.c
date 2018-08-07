/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2016/07/18 18:10:13 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

char	*cmd_list(t_server *srv, t_client *clt)
{
	t_channel	*ch;

	ch = srv->channels;
	while (ch != NULL)
	{
		msgq_enqueue(clt->msgq_write, ch->name);
		if (ft_strlen(ch->topic))
		{
			msgq_enqueue(clt->msgq_write, " <");
			msgq_enqueue(clt->msgq_write, ch->topic);
			msgq_enqueue(clt->msgq_write, "> ");
		}
		else
			msgq_enqueue(clt->msgq_write, " ");
		ch = ch->next;
	}
	msgq_enqueue(clt->msgq_write, "\n");
	return (NULL);
}
