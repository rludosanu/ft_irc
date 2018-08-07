/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 11:52:34 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "utils.h"

static void			welcome(void)
{
	printf("Welcome ! ");
	printf("Use \x1b[33m/help\x1b[0m to list available commands or ");
	printf("\x1b[33m/quit\x1b[0m to exit program.\n");
}

static void			set_sockfd(t_client *clt)
{
	FD_ZERO(&(clt->readfs));
	FD_ZERO(&(clt->writefs));
	FD_SET(STDIN_FILENO, &(clt->readfs));
	if (clt->sockfd != -1)
		FD_SET(clt->sockfd, &(clt->readfs));
	if (clt->sockfd != -1)
		FD_SET(clt->sockfd, &(clt->writefs));
}

int					loop(t_client *clt)
{
	struct timeval	timeout;

	welcome();
	timeout.tv_sec = 2;
	timeout.tv_usec = 0;
	while (1)
	{
		set_sockfd(clt);
		if (select(clt->sockfd + 1, &(clt->readfs), \
					&(clt->writefs), NULL, &timeout) < 0)
			continue ;
		if (FD_ISSET(STDIN_FILENO, &(clt->readfs)))
		{
			if (stdin_read(clt) == -1)
				break ;
		}
		else if (FD_ISSET(clt->sockfd, &(clt->readfs)))
		{
			if (server_read(clt) == -1)
				break ;
		}
		else if (FD_ISSET(clt->sockfd, &(clt->writefs)))
			server_write(clt);
	}
	return (0);
}
