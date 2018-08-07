/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 10:57:55 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "utils.h"

/*
** Frees the command array
*/

void		msg_free(char **cmd)
{
	int		x;

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

/*
** Clean the command of trailing carriage return
*/

char		**msg_clean(char **cmd)
{
	int		i;
	size_t	l;

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

/*
** Split the message into a command
*/

char		**msg_split(char **cmd, char *msg)
{
	int		x;
	int		y;
	int		z;

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

/*
** Execute the command
** Returns 0 if internal execution or 1 if this is a message for the server
*/

static int	msg_exec(t_client *clt, char **cmd)
{
	if (ft_strequ(cmd[0], "/connect"))
	{
		cmd_connect(clt, cmd[1], cmd[2]);
		return (0);
	}
	else if (ft_strequ(cmd[0], "/help"))
		return (cmd_help());
	else if (ft_strequ(cmd[0], "/quit"))
		return (-1);
	else
		return (1);
}

/*
** Convert the message into a command and try to execute it
*/

int			msg_parse(t_client *clt, char *msg)
{
	char	**cmd;
	int		ret;

	if (msg == NULL)
		return (0);
	if ((cmd = (char **)malloc(sizeof(char *) * 3)) == NULL)
		return (0);
	ret = 0;
	while (ret < 3)
		cmd[ret++] = NULL;
	cmd = msg_split(cmd, msg);
	cmd = msg_clean(cmd);
	if ((ret = msg_exec(clt, cmd)) > 0)
		msgq_enqueue(clt->msgq_write, msg);
	msg_free(cmd);
	return (ret);
}
