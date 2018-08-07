/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 11:06:27 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

static int		is_nick_ascii(char *nick)
{
	size_t		x;

	x = 0;
	while (x < ft_strlen(nick))
	{
		if (nick[x] < 32 || nick[x] > 126)
			return (0);
		x++;
	}
	return (1);
}

static int		is_nick_available(t_server *srv, char *nick)
{
	t_client	*clt;

	clt = srv->clients;
	while (clt != NULL)
	{
		if (ft_strequ(clt->nick, nick))
			return (0);
		clt = clt->next;
	}
	return (1);
}

char			*cmd_nick(t_server *srv, t_client *clt, char *nick)
{
	if (nick == NULL || ft_strlen(nick) == 0)
		return (ERR_NONICKNAMEGIVEN);
	else if (ft_strlen(nick) > CLT_NICKSZ)
		return (ERR_NICKNAMETOOLONG);
	else if (is_nick_ascii(nick) == 0)
		return (ERR_ERRONEUSNICKNAME);
	else if (is_nick_available(srv, nick) == 0)
		return (ERR_NICKNAMEINUSE);
	else
	{
		ft_strcpy(clt->nick, nick);
		clt->nick[ft_strlen(nick)] = '\0';
		return (NULL);
	}
}
