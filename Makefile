##
## Makefile for myftp in /home/amstuta/rendu/PSU_2014_myftp
##
## Made by arthur
## Login   <amstuta@epitech.net>
##
## Started on  Tue Mar  3 15:19:22 2015 arthur
## Last update Sun Mar  8 20:43:49 2015 arthur
##

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

RM	= rm -f

CLIENT	= client

SERVEUR	= serveur

SRCS_C	= client.c

SRCS_S	= server.c \
	  exec_cmd.c \
	  check.c

OBJS_C	= $(SRCS_C:.c=.o)

OBJS_S	= $(SRCS_S:.c=.o)

all:	$(SERVEUR) $(CLIENT)

$(SERVEUR):	$(OBJS_S)
		$(CC) $(OBJS_S) -o $(SERVEUR)

$(CLIENT):	$(OBJS_C)
		$(CC) $(OBJS_C) -o $(CLIENT)

clean:
	$(RM) $(OBJS_C)
	$(RM) $(OBJS_S)

fclean:	clean
	$(RM) $(SERVEUR)
	$(RM) $(CLIENT)

re:	fclean all

.PHONY:	all clean fclean re
