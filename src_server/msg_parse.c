/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 11:36:54 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

static void		msg_free(char **cmd)
{
	int			x;

	if (cmd)
	{
		x = 0;
		while (x < 3)
		{
			if (cmd[x] != NULL)
				free(cmd[x]);
			x++;
		}
		free(cmd);
	}
}

static char		**msg_clean(char **cmd)
{
	int			i;
	size_t		l;

	i = 0;
	while (i < 3)
	{
		if (cmd[i] != NULL)
		{
			l = ft_strlen(cmd[i]);
			if (cmd[i][l - 1] == '\n')
				cmd[i][l - 1] = '\0';
		}
		i++;
	}
	return (cmd);
}

static char		**msg_split(char **cmd, char *msg)
{
	int			x;
	int			y;
	int			z;

	x = 0;
	y = 0;
	z = 0;
	while (z < 3)
	{
		if (msg[x] == '\0')
			break ;
		while (msg[x] != '\0' && msg[x] == ' ')
			y = ++x;
		while (msg[y] != '\0')
		{
			if (z != 2 && msg[y] == ' ')
				break ;
			y++;
		}
		cmd[z++] = ft_strsub(msg, x, y);
		x = y;
	}
	return (cmd);
}

static char		*msg_exec(t_server *srv, t_client *clt, char **cmd)
{
	if (ft_strequ(cmd[0], "/nick"))
		return (cmd_nick(srv, clt, cmd[1]));
	else if (ft_strequ(cmd[0], "/msg"))
		return (cmd_privmsg(srv, clt, cmd[1], cmd[2]));
	else if (ft_strequ(cmd[0], "/join"))
		return (cmd_join(srv, clt, cmd[1]));
	else if (ft_strequ(cmd[0], "/leave"))
		return (cmd_leave(srv, clt, cmd[1]));
	else if (ft_strequ(cmd[0], "/who"))
		return (cmd_who(srv, clt));
	else if (ft_strequ(cmd[0], "/list"))
		return (cmd_list(srv, clt));
	else if (ft_strequ(cmd[0], "/topic"))
		return (cmd_topic(srv, clt, cmd[1], cmd[2]));
	else if (ft_strequ(cmd[0], "/kick"))
		return (cmd_kick(srv, clt, cmd[1], cmd[2]));
	else if (ft_strequ(cmd[0], "/ban"))
		return (cmd_ban(srv, clt, cmd[1], cmd[2]));
	return (NULL);
}

int				msg_parse(t_server *srv, t_client *clt, char *msg)
{
	char		**cmd;
	char		*rpl;
	int			i;

	if (msg == NULL)
		return (1);
	if ((cmd = (char **)malloc(sizeof(char *) * 3)) == NULL)
		return (1);
	i = 0;
	while (i < 3)
		cmd[i++] = NULL;
	cmd = msg_split(cmd, msg);
	cmd = msg_clean(cmd);
	if ((rpl = msg_exec(srv, clt, cmd)))
		msgq_enqueue(clt->msgq_write, rpl);
	msg_free(cmd);
	return (0);
}
