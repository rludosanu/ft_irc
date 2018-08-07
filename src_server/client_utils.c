/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2016/07/18 18:10:13 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

/*
** Find the user by nickname
*/

t_client		*client_find(t_client *clts, char *nick)
{
	t_client	*clt;

	clt = clts;
	while (clt != NULL)
	{
		if (ft_strequ(clt->nick, nick))
			return (clt);
		clt = clt->next;
	}
	return (NULL);
}
