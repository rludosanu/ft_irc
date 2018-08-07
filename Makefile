# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rludosan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/18 16:22:03 by rludosan          #+#    #+#              #
#    Updated: 2018/01/03 11:17:21 by rludosan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

LIB_UTILS		=	libutils.a
EXEC_SERVER		=	serveur
EXEC_CLIENT		=	client

DIR_UTILS		=	./src_utils/
DIR_SERVER		=	./src_server/
DIR_CLIENT		=	./src_client/

SRC_UTILS		=	ft_strsub \
					ft_strequ \
					ft_strlen \
					ft_strcpy \
					ft_strchr \
					ft_strcat \
					ft_memset \
					ft_memcpy \
					ft_atoi \
					ft_strcmp

SRC_SERVER		=	main \
					server \
					loop \
					client \
					client_utils \
					channel \
					channel_utils \
					channel_is \
					msg \
					msg_parse \
					msgq \
					cmd_nick \
					cmd_privmsg \
					cmd_join \
					cmd_leave \
					cmd_who \
					cmd_list \
					cmd_topic \
					cmd_kick \
					cmd_ban

SRC_CLIENT		=	main \
					client \
					loop \
					msgq \
					server_read \
					server_write \
					stdin_read \
					msg_parse \
					cmd_help \
					cmd_connect

OBJ_UTILS		=	$(addsuffix .o, $(SRC_UTILS))
OBJ_SERVER		=	$(addsuffix .o, $(SRC_SERVER))
OBJ_CLIENT		=	$(addsuffix .o, $(SRC_CLIENT))

TGT_UTILS		=	$(addprefix $(DIR_UTILS), $(OBJ_UTILS))
TGT_SERVER		=	$(addprefix $(DIR_SERVER), $(OBJ_SERVER))
TGT_CLIENT		=	$(addprefix $(DIR_CLIENT), $(OBJ_CLIENT))

all: $(LIB_UTILS) $(EXEC_SERVER) $(EXEC_CLIENT)

$(LIB_UTILS): $(TGT_UTILS)
	ar rc $@ $^
	ranlib $@

$(EXEC_SERVER): $(TGT_SERVER)
	$(CC) $(CFLAGS) -Iincludes -o $@ $^ $(LIB_UTILS)

$(EXEC_CLIENT): $(TGT_CLIENT)
	$(CC) $(CFLAGS) -Iincludes -o $@ $^ $(LIB_UTILS)

%.o: %.c
	$(CC) $(CFLAGS) -Iincludes -o $@ -c $<

clean:
	rm -f $(TGT_UTILS) $(TGT_SERVER) $(TGT_CLIENT)

fclean: clean
	rm -rf $(LIB_UTILS) $(EXEC_SERVER) $(EXEC_CLIENT)

re: fclean all

.PHONY: all clean fclean re
