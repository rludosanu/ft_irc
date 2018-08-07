/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2016/07/18 18:10:13 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "utils.h"

int		cmd_help(void)
{
	printf("\n\x1b[33m/connect <machine> <port>\x1b[0m\n");
	printf("    Connect to an IPV4 IRC server.\n\n");
	printf("\x1b[33m/nick <nickname>\x1b[0m\n");
	printf("    Change client's nickname.\n\n");
	printf("\x1b[33m/list\x1b[0m\n");
	printf("    List all public available channels.\n\n");
	printf("\x1b[33m/join <channel>\x1b[0m\n");
	printf("    Join or create as operator a (new) channel.\n\n");
	printf("\x1b[33m/leave <channel>\x1b[0m\n");
	printf("    Leave a channel.\n\n");
	printf("\x1b[33m/who\x1b[0m\n");
	printf("    List all users registered into common channel(s).\n\n");
	printf("\x1b[33m/msg <channel|nickname> <message>\x1b[0m\n");
	printf("    Send a message to a channel or a single client.\n\n");
	printf("\x1b[33m/topic <channel> <topic>\x1b[0m\n");
	printf("    (Operator) Change channel's topic message.\n\n");
	printf("\x1b[33m/kick <channel> <nickname>\x1b[0m\n");
	printf("    (Operator) Kick a client from a channel.\n\n");
	printf("\x1b[33m/ban <channel> <nickname>\x1b[0m\n");
	printf("    (Operator) Kick/Ban a client from a channel.\n\n");
	printf("\x1b[33m/quit\x1b[0m\n");
	printf("    Close the connection and exit program.\n\n");
	return (0);
}
