/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgq.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 11:11:10 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

void	msgq_free(t_msgq *mq)
{
	if (mq)
	{
		free(mq->buffer);
		free(mq);
		mq = NULL;
	}
}

t_msgq	*msgq_new(int sz)
{
	t_msgq	*mq;

	if (!(mq = (t_msgq *)malloc(sizeof(t_msgq))))
		return (NULL);
	if (!(mq->buffer = (char *)malloc(sizeof(char) * sz)))
	{
		free(mq);
		return (NULL);
	}
	mq->head = 0;
	mq->tail = 0;
	return (mq);
}

void	msgq_dequeue(t_server *srv, t_client *clt, t_msgq *mq, \
	int (*msg_handler)(t_server *srv, t_client *clt, char *msg))
{
	int		head;
	int		tail;
	int		i;
	char	msg[MSGQ_SZ];

	head = mq->head;
	tail = mq->tail;
	i = 0;
	while (head != tail)
	{
		msg[i++] = mq->buffer[head];
		if (mq->buffer[head] == '\n')
		{
			mq->head = (head == MSGQ_SZ - 1) ? 0 : head + 1;
			msg[i] = '\0';
			i = 0;
			msg_handler(srv, clt, msg);
		}
		head = (head == MSGQ_SZ - 1) ? 0 : head + 1;
	}
}

void	msgq_enqueue_s(t_msgq *mq, char *msg, char *rnd)
{
	msgq_enqueue(mq, msg);
	msgq_enqueue(mq, rnd);
}

void	msgq_enqueue(t_msgq *mq, char *msg)
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
