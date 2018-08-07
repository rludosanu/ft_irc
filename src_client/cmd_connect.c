/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_connect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2016/07/18 18:10:13 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "utils.h"

int		cmd_connect(t_client *clt, const char *machine, char *port)
{
	if (!clt || !machine || !port)
	{
		printf("550 Unable to connect to server\n");
		return (-1);
	}
	if (clt->sockfd != -1)
	{
		printf("200 Closing previous server connection...\n");
		close(clt->sockfd);
		clt->sockfd = -1;
	}
	if ((clt->sockfd = client_connect(machine, ft_atoi(port))) == -1)
	{
		printf("551 Unable to connect to server\n");
		return (-1);
	}
	return (0);
}
