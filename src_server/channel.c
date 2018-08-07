/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 11:20:27 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 12:33:29 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

void			channel_free(t_channel **node)
{
	if (*node == NULL)
		return ;
	free(*node);
	*node = NULL;
}

void			channel_lfree(t_channel **head)
{
	t_channel	*curr;
	t_channel	*save;

	if (*head == NULL)
		return ;
	curr = *head;
	while (curr != NULL)
	{
		save = curr->next;
		channel_free(&curr);
		curr = save;
	}
}

void			channel_ofree(t_channel **head, char *name)
{
	t_channel	*curr;
	t_channel	*save;

	if ((curr = *head) == NULL)
		return ;
	if (ft_strequ((*head)->name, name))
	{
		save = (*head)->next;
		channel_free(head);
		*head = save;
	}
	else
	{
		while (curr->next != NULL)
		{
			if (ft_strequ(curr->next->name, name))
			{
				save = curr->next->next;
				channel_free(&(curr->next));
				curr->next = save;
			}
			else
				curr = curr->next;
		}
	}
}

void			channel_add(t_channel **head, t_channel *node)
{
	t_channel	*curr;

	if (*head == NULL)
		*head = node;
	else
	{
		curr = *head;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = node;
	}
}

t_channel		*channel_create(char *name, int sockfd)
{
	t_channel	*ch;
	int			csz;
	int			isz;

	csz = sizeof(char);
	isz = sizeof(int);
	if (!(ch = (t_channel *)malloc(sizeof(t_channel))))
		return (NULL);
	ft_memset((char *)ch->name, 0, CHAN_NAMESZ * csz);
	ft_memset((char *)ch->topic, 0, CHAN_TOPICSZ * csz);
	ft_memset((int *)ch->clients, -1, CHAN_CLTMAX * isz);
	ft_memset((int *)ch->admins, -1, CHAN_ADMMAX * isz);
	ft_memset((int *)ch->bans, -1, CHAN_BANMAX * isz);
	ft_strcpy(ch->name, name);
	ch->clients[0] = sockfd;
	ch->admins[0] = sockfd;
	ch->next = NULL;
	return (ch);
}
