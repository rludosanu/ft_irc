/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2016/07/18 18:10:13 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

int				main(int argc, char **argv)
{
	t_server	*srv;

	if (argc != 2)
		return (printf("Usage: ./serveur <port>\n"));
	else
	{
		if ((srv = server_new(ft_atoi(argv[1]))))
		{
			server_loop(srv);
			server_free(&srv);
		}
		else
			return (printf("Error: Unable to create server\n"));
	}
	return (0);
}
