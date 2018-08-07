/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgq.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 10:57:06 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "utils.h"

/*
** Frees a message queue
*/

void		msgq_free(t_msgq *mq)
{
	if (mq == NULL)
		return ;
	free(mq->buffer);
	free(mq);
	mq = NULL;
}

/*
** Create a new message queue
*/

t_msgq		*msgq_new(int sz)
{
	t_msgq	*mq;

	if ((mq = (t_msgq *)malloc(sizeof(t_msgq))) == NULL)
		return (NULL);
	if ((mq->buffer = (char *)malloc(sizeof(char) * sz)) == NULL)
	{
		free(mq);
		return (NULL);
	}
	mq->head = 0;
	mq->tail = 0;
	return (mq);
}

/*
** Search for valid messages to be dequeued and sends them to
** the message handler
*/

int			msgq_dequeue(t_client *clt, t_msgq *mq, \
		int (*msg_handler)(t_client *clt, char *msg))
{
	int		head;
	int		tail;
	int		i;
	char	tmp[MSGQ_SZ];

	head = mq->head;
	tail = mq->tail;
	i = 0;
	while (head != tail)
	{
		tmp[i++] = mq->buffer[head];
		if (mq->buffer[head] == '\n')
		{
			mq->head = (head == MSGQ_SZ - 1) ? 0 : head + 1;
			tmp[i] = '\0';
			i = 0;
			if (msg_handler(clt, tmp) == -1)
				return (-1);
		}
		head = (head == MSGQ_SZ - 1) ? 0 : head + 1;
	}
	return (0);
}

/*
** Enqueue a new message
*/

void		msgq_enqueue(t_msgq *mq, char *msg)
{
	int		tail;
	int		i;

	tail = mq->tail;
	i = 0;
	while (msg[i] != '\0')
	{
		mq->buffer[tail] = msg[i++];
		tail = (tail == MSGQ_SZ - 1) ? 0 : tail + 1;
	}
	mq->tail = tail;
}
