/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2016/07/18 18:10:13 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

static int	server_getsocket(int port)
{
	int					fd;
	int					opt;
	struct sockaddr_in	sin;

	fd = -1;
	opt = 1;
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (-1);
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		return (-1);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	ft_memset(&(sin.sin_zero), 0, 8);
	if (bind(fd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
	{
		close(fd);
		return (-1);
	}
	if (listen(fd, SRV_CONNMAX) < 0)
	{
		close(fd);
		return (-1);
	}
	return (fd);
}

void		server_free(t_server **srv)
{
	if (srv && *srv)
	{
		close((*srv)->sockfd);
		if ((*srv)->clients != NULL)
			client_lfree(&(*srv)->clients);
		if ((*srv)->channels != NULL)
			channel_lfree(&(*srv)->channels);
		free(srv);
	}
}

t_server	*server_new(int port)
{
	t_server	*srv;

	if (port <= 0)
		return (NULL);
	if (!(srv = (t_server *)malloc(sizeof(t_server))))
		return (NULL);
	if ((srv->sockfd = server_getsocket(port)) == -1)
	{
		free(srv);
		return (NULL);
	}
	srv->maxfd = srv->sockfd;
	srv->clients = NULL;
	srv->channels = NULL;
	return (srv);
}
