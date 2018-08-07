/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 11:29:48 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/select.h>

# define ERR_NOSUCHNICK			"401 No such nickname\n"
# define ERR_NOSUCHCHANNEL		"403 No such channel\n"
# define ERR_NORECIPIENT		"411 No recipient given\n"
# define ERR_NOMESSAGE			"412 No text to send\n"
# define ERR_NONICKNAMEGIVEN	"431 No nickname given\n"
# define ERR_ERRONEUSNICKNAME	"432 Invalid nickname characters\n"
# define ERR_NICKNAMEINUSE		"433 Nickname in use\n"
# define ERR_NOTONCHANNEL		"442 Not registered on channel\n"
# define ERR_USERONCHANNEL		"443 Already registered on channel\n"
# define ERR_CHANNELISFULL		"471 Channel is full\n"
# define ERR_BANNEDFROMCHAN		"474 Banned from channel\n"
# define ERR_CHANOPRIVSNEEDED	"482 Not a channel operator\n"

# define ERR_NICKNAMETOOLONG	"501 Nickname too long\n"
# define ERR_CHANNELTOOLONG		"502 Channel name too long\n"
# define ERR_ERRONEUSTOPIC		"503 Invalid topic characters\n"
# define ERR_ERRCHANNELNAME		"504 Invalid channel name\n"
# define ERR_NOCHANNELGIVEN		"505 No channel given\n"
# define ERR_CHANNELNOTCREATED	"506 Unable to create channel\n"
# define ERR_ALREADYBANNED		"507 Client already banned\n"
# define ERR_CANNOTBEBANNED		"508 Unable to ban from channel\n"
# define ERR_UNAUTHSELFKICK		"509 Unauthorised self-kicking\n"
# define ERR_TOPICTOOLONG		"510 Topic name too long\n"
# define ERR_NOTOPICGIVEN		"511 No topic given\n"

# define MSGQ_SZ				512
# define SRV_CONNMAX			42

# define CLT_NICKSZ				9
# define CLT_CHANMAX			10

# define CHAN_NBMAX				200
# define CHAN_NAMESZ			200
# define CHAN_TOPICSZ			200
# define CHAN_CLTMAX			50
# define CHAN_ADMMAX			2
# define CHAN_BANMAX			50

typedef struct					s_msgq
{
	char						*buffer;
	int							head;
	int							tail;
}								t_msgq;

typedef struct					s_channel
{
	char						name[CHAN_NAMESZ + 1];
	char						topic[CHAN_TOPICSZ + 1];
	int							clients[CHAN_CLTMAX];
	int							admins[CHAN_ADMMAX];
	int							bans[CHAN_BANMAX];
	struct s_channel			*next;
}								t_channel;

typedef struct					s_client
{
	int							sockfd;
	char						nick[CLT_NICKSZ + 1];
	t_msgq						*msgq_read;
	t_msgq						*msgq_write;
	struct s_client				*next;
}								t_client;

typedef struct					s_server
{
	int							sockfd;
	int							maxfd;
	fd_set						readfs;
	fd_set						writefs;
	struct s_client				*clients;
	struct s_channel			*channels;
}								t_server;

/*
** Message queue
*/

void							msgq_free(t_msgq *mq);
t_msgq							*msgq_new(int sz);
void							msgq_dequeue(t_server *srv, t_client *clt, \
		t_msgq *mq, \
		int (*msg_handler)(t_server *srv, t_client *clt, char *msg));
void							msgq_enqueue(t_msgq *mq, char *msg);
void							msgq_enqueue_s(t_msgq *mq, char *msg, \
		char *rnd);

/*
** Server
*/

void							server_free(t_server **srv);
t_server						*server_new(int port);
void							server_loop(t_server *srv);

/*
** Client
*/

void							client_free(t_client **clt);
void							client_lfree(t_client **clt);
void							client_ofree(t_client **head, int sockfd);
void							client_add(t_client **clts, t_client *clt);
t_client						*client_new(int sockfd);

/*
** Client utils
*/

t_client						*client_find(t_client *clts, char *nick);

/*
** Commands
*/

char							*cmd_nick(t_server *srv, t_client *clt, \
		char *nick);
char							*cmd_privmsg(t_server *srv, t_client *clt, \
		char *dst, char *msg);
char							*cmd_join(t_server *srv, t_client *clt, \
		char *name);
char							*cmd_leave(t_server *srv, t_client *clt, \
		char *name);
char							*cmd_who(t_server *srv, t_client *clt);
char							*cmd_list(t_server *srv, t_client *clt);
char							*cmd_topic(t_server *srv, t_client *clt, \
		char *channel, char *topic);
char							*cmd_kick(t_server *srv, t_client *clt, \
		char *channel, char *nickname);
char							*cmd_ban(t_server *srv, t_client *clt, \
		char *channel, char *nickname);

/*
** Messages
*/

int								msg_parse(t_server *srv, t_client *clt, \
		char *msg);
int								msg_read(t_server *srv, t_client *clt);
void							msg_write(t_server *srv, t_client *clt);

/*
** Channels
*/

t_channel						*channel_create(char *name, int sockfd);
void							channel_add(t_channel **head, t_channel *node);
void							channel_ofree(t_channel **head, char *name);
void							channel_lfree(t_channel **head);
void							channel_free(t_channel **node);

/*
** Channels utils
*/

t_channel						*channel_find(t_channel *head, char *name);
int								channel_find_client(t_channel *ch, int sockfd);
int								channel_count_clients(t_channel *ch);
int								channel_remove_client(t_channel *ch, \
		int sockfd);
void							channel_remove_client_all(t_channel **head, \
		int sockfd);
int								channel_is_admin(t_channel *ch, int sockfd);
int								channel_is_banned(t_channel *ch, int sockfd);

#endif
