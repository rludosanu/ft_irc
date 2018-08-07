/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 12:39:19 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "utils.h"

int				main(int argc, char **argv)
{
	t_client	*clt;

	if (argc == 1)
	{
		if (!(clt = client_create(NULL, NULL)))
			return (printf("Error: Unable to create client\n"));
		loop(clt);
		client_destroy(&clt);
	}
	else if (argc == 3)
	{
		if (!(clt = client_create(argv[1], argv[2])))
			return (printf("Error: Unable to create client\n"));
		loop(clt);
		client_destroy(&clt);
	}
	else
		return (printf("Usage: ./client <machine> <port>\n"));
	return (0);
}
