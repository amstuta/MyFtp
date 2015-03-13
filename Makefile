##
## Makefile for myftp in /home/amstuta/rendu/PSU_2014_myftp
##
## Made by arthur
## Login   <amstuta@epitech.net>
##
## Started on  Tue Mar  3 15:19:22 2015 arthur
## Last update Fri Mar 13 13:34:38 2015 arthur
##

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

RM	= rm -f

CLIENT	= client

SERVEUR	= serveur

FOLD_S	= Serveur

FOLD_C	= Client

SRCS_C	= $(FOLD_C)/client.c \
	  $(FOLD_C)/check_cmd.c \
	  $(FOLD_C)/wordtab.c \
	  $(FOLD_C)/exit.c \
	  $(FOLD_C)/data_connection.c \
	  $(FOLD_C)/file.c

SRCS_S	= $(FOLD_S)/server.c \
	  $(FOLD_S)/exec_cmd.c \
	  $(FOLD_S)/check.c \
	  $(FOLD_S)/fcts.c \
	  $(FOLD_S)/wordtab.c \
	  $(FOLD_S)/exit.c \
	  $(FOLD_S)/file.c \
	  $(FOLD_S)/data_connection.c

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
