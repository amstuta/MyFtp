##
## Makefile for myftp in /home/amstuta/rendu/PSU_2014_myftp
##
## Made by arthur
## Login   <amstuta@epitech.net>
##
## Started on  Tue Mar  3 15:19:22 2015 arthur
## Last update Mon Mar 16 13:50:33 2015 arthur
##

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

RM	= rm -f

NAME	= serveur

NAME2	= client

FOLD_S	= Serveur

FOLD_C	= Client

SRCS_C	= $(FOLD_C)/client.c \
	  $(FOLD_C)/check_cmd.c \
	  $(FOLD_C)/wordtab.c \
	  $(FOLD_C)/exit.c \
	  $(FOLD_C)/data_connection.c \
	  $(FOLD_C)/file.c \
	  $(FOLD_C)/auth.c \
	  $(FOLD_C)/ls.c

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

all:	$(NAME) $(NAME2)

$(NAME): $(OBJS_S)
	 $(CC) $(OBJS_S) -o $(NAME)

$(NAME2):$(OBJS_C)
	 $(CC) $(OBJS_C) -o $(NAME2)

clean:
	$(RM) $(OBJS_C)
	$(RM) $(OBJS_S)

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(NAME2)

re:	fclean all

.PHONY:	all clean fclean re
