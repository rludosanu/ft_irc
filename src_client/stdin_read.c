/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2016/07/18 18:10:13 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "utils.h"

/*
** Get input message from keyboard
*/

int			stdin_read(t_client *clt)
{
	char	buf[MSGQ_SZ];
	int		ret;

	ret = read(STDIN_FILENO, buf, MSGQ_SZ - 1);
	if (ret > 0)
	{
		buf[ret] = '\0';
		msgq_enqueue(clt->msgq_read, buf);
		ret = msgq_dequeue(clt, clt->msgq_read, msg_parse);
	}
	return (ret);
}
