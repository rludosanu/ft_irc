/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_leave.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 12:33:40 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

/*
** Remove a client from all existing channels
*/

void			channel_remove_client_all(t_channel **head, int sockfd)
{
	t_channel	*curr;
	t_channel	*next;

	curr = *head;
	while (curr != NULL)
	{
		next = curr->next;
		channel_remove_client(curr, sockfd);
		if (channel_count_clients(curr) == 0)
			channel_ofree(head, curr->name);
		curr = next;
	}
}

/*
** Leave a channel by name
*/

char			*cmd_leave(t_server *srv, t_client *clt, char *name)
{
	t_channel	*ch;

	if (!name || !ft_strlen(name))
		return (ERR_NOCHANNELGIVEN);
	else
	{
		if (!(ch = channel_find(srv->channels, name)))
			return (ERR_NOSUCHCHANNEL);
		if (channel_remove_client(ch, clt->sockfd) == -1)
			return (ERR_NOTONCHANNEL);
		if (channel_count_clients(ch) == 0)
			channel_ofree(&(srv->channels), name);
	}
	return (NULL);
}
