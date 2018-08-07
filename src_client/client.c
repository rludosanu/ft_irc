/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 10:59:14 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "utils.h"

static void				client_resolve(const char *machine, \
		struct sockaddr_in *addr, struct addrinfo *tmp)
{
	struct addrinfo		*res;
	struct addrinfo		hints;

	hints.ai_flags = 0;
	hints.ai_family = AF_INET;
	hints.ai_socktype = 0;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_addrlen = 0;
	hints.ai_addr = NULL;
	hints.ai_canonname = NULL;
	hints.ai_next = NULL;
	if (getaddrinfo(machine, NULL, &hints, &res) == 0)
	{
		tmp = res;
		while (tmp != NULL)
		{
			if (tmp->ai_family == AF_INET)
			{
				ft_memcpy(addr, tmp->ai_addr, sizeof(struct sockaddr_in));
				break ;
			}
			tmp = tmp->ai_next;
		}
		freeaddrinfo(res);
	}
}

int						client_connect(const char *machine, int port)
{
	int					sockfd;
	struct sockaddr_in	sockin;
	struct addrinfo		tmp;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		return (-1);
	client_resolve(machine, &sockin, &tmp);
	sockin.sin_family = AF_INET;
	sockin.sin_port = htons(port);
	if (connect(sockfd, (struct sockaddr *)&sockin, sizeof(sockin)) < 0)
	{
		close(sockfd);
		return (-1);
	}
	return (sockfd);
}

void					client_destroy(t_client **clt)
{
	if (!clt || !(*clt))
		return ;
	close((*clt)->sockfd);
	msgq_free((*clt)->msgq_read);
	msgq_free((*clt)->msgq_write);
	free(*clt);
	*clt = NULL;
}

t_client				*client_create(const char *machine, char *port)
{
	t_client			*clt;

	if (!(clt = (t_client *)malloc(sizeof(t_client))))
		return (NULL);
	if (!machine || !port)
		clt->sockfd = -1;
	else if ((clt->sockfd = client_connect(machine, ft_atoi(port))) == -1)
	{
		free(clt);
		return (NULL);
	}
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
	return (clt);
}
