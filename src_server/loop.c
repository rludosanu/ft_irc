/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 12:34:02 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

static void				client_loop(t_server *srv)
{
	t_client			*clt;
	t_client			*next;
	int					status;

	clt = srv->clients;
	while (clt != NULL)
	{
		next = clt->next;
		if (FD_ISSET(clt->sockfd, &(srv->readfs)))
			status = msg_read(srv, clt);
		if (status > 0 && FD_ISSET(clt->sockfd, &(srv->writefs)))
			msg_write(srv, clt);
		clt = next;
	}
}

static int				accept_client(t_server *srv)
{
	t_client			*clt;
	int					fd;
	struct sockaddr_in	sin;
	unsigned int		size;

	ft_memset(&sin, '0', sizeof(struct sockaddr_in));
	if ((fd = accept(srv->sockfd, (struct sockaddr *)&sin, &size)) < 0)
		return (-1);
	srv->maxfd = (fd > srv->maxfd) ? fd : srv->maxfd;
	if (!(clt = client_new(fd)))
	{
		close(fd);
		return (-1);
	}
	client_add(&(srv->clients), clt);
	return (fd);
}

static void				set_sockfd(t_server *srv)
{
	t_client			*clt;

	FD_ZERO(&(srv->readfs));
	FD_ZERO(&(srv->writefs));
	FD_SET(srv->sockfd, &(srv->readfs));
	FD_SET(srv->sockfd, &(srv->writefs));
	clt = srv->clients;
	while (clt != NULL)
	{
		FD_SET(clt->sockfd, &(srv->readfs));
		FD_SET(clt->sockfd, &(srv->writefs));
		clt = clt->next;
	}
}

void					server_loop(t_server *srv)
{
	struct timeval		timeout;

	timeout.tv_sec = 2;
	timeout.tv_usec = 0;
	while (1)
	{
		set_sockfd(srv);
		if (select(srv->maxfd + 1, &(srv->readfs), &(srv->writefs), \
		NULL, &timeout) < 0)
			break ;
		if (FD_ISSET(srv->sockfd, &(srv->readfs)))
			accept_client(srv);
		else
			client_loop(srv);
	}
}
