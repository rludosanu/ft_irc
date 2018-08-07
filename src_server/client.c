/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 11:20:19 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

void			client_free(t_client **clt)
{
	if (clt && *clt)
	{
		close((*clt)->sockfd);
		msgq_free((*clt)->msgq_read);
		msgq_free((*clt)->msgq_write);
		free(*clt);
		*clt = NULL;
	}
}

void			client_lfree(t_client **clt)
{
	t_client	*curr;
	t_client	*save;

	if (*clt == NULL)
		return ;
	curr = *clt;
	while (curr != NULL)
	{
		save = curr->next;
		client_free(&curr);
		curr = save;
	}
}

void			client_ofree(t_client **head, int sockfd)
{
	t_client	*curr;
	t_client	*save;

	if ((curr = *head) == NULL)
		return ;
	if ((*head)->sockfd == sockfd)
	{
		save = (*head)->next;
		client_free(head);
		*head = save;
	}
	else
	{
		while (curr->next != NULL)
		{
			if (curr->next->sockfd == sockfd)
			{
				save = curr->next->next;
				client_free(&(curr->next));
				curr->next = save;
			}
			else
				curr = curr->next;
		}
	}
}

void			client_add(t_client **clts, t_client *clt)
{
	t_client	*curr;

	if (*clts == NULL)
		*clts = clt;
	else
	{
		curr = *clts;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = clt;
	}
}

t_client		*client_new(int sockfd)
{
	t_client	*clt;

	if (!(clt = (t_client *)malloc(sizeof(t_client))))
		return (NULL);
	clt->sockfd = sockfd;
	ft_memset(clt->nick, '\0', CLT_NICKSZ + 1);
	if (!(clt->msgq_read = msgq_new(MSGQ_SZ)))
	{
		free(clt);
		return (NULL);
	}
	if (!(clt->msgq_write = msgq_new(MSGQ_SZ)))
	{
		free(clt);
		return (NULL);
	}
	clt->next = NULL;
	return (clt);
}
