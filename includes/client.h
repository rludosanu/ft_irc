/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 11:24:49 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/select.h>
# include <arpa/inet.h>
# include <netdb.h>

# define MSGQ_SZ		512

typedef struct		s_msgq
{
	char			*buffer;
	int				head;
	int				tail;
}					t_msgq;

typedef struct		s_client
{
	int				sockfd;
	fd_set			readfs;
	fd_set			writefs;
	t_msgq			*msgq_read;
	t_msgq			*msgq_write;
}					t_client;

/*
** Message queue
*/

void				msgq_free(t_msgq *mq);
t_msgq				*msgq_new(int sz);
int					msgq_dequeue(t_client *clt, t_msgq *mq, \
		int (*msg_handler)(t_client *clt, char *msg));
void				msgq_enqueue(t_msgq *mq, char *msg);

/*
** Client
*/

t_client			*client_create(const char *machine, char *port);
void				client_destroy(t_client **clt);
int					client_connect(const char *machine, int port);

/*
** Utils
*/

int					loop(t_client *clt);

/*
** Commands
*/

int					cmd_help(void);
int					cmd_connect(t_client *clt, const char *machine, char *port);

/*
** IO
*/

int					server_read(t_client *clt);
void				server_write(t_client *clt);
int					stdin_read(t_client *clt);
int					msg_parse(t_client *clt, char *msg);

#endif
