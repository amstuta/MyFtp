/*
** main.c for main in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Tue Mar  3 15:17:53 2015 arthur
** Last update Sun Mar  8 21:08:41 2015 arthur
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/wait.h>
#include "server.h"

#define LINE_SIZE 80

void			read_cmd(int fd)
{
  char			*buf;

  if ((buf = malloc(LINE_SIZE)) == NULL)
    {
      close(fd);
      exit(EXIT_FAILURE);
    }
  if ((read(fd, buf, LINE_SIZE)) == -1)
    {
      close(fd);
      exit(EXIT_FAILURE);
    }
  clean_cmd(buf, fd);
}

void			accept_client(int fd, int cs)
{
  //char			*ip;
  struct sockaddr_in	sin_c;
  int			c_len;

  c_len = sizeof(sin_c);
  if ((cs = accept(fd, (struct sockaddr*)&sin_c, (socklen_t*)&c_len)) == -1)
    {
      printf("accept");
      return ;
    }
  while (1)
    read_cmd(cs);
  //ip = inet_ntoa(sin_c.sin_addr);
}

void			fork_proc(int fd, int cs)
{
  int			i;
  int			child;

  child = fork();
  if (child == 0)
    {
      accept_client(fd, cs);
    }
  else
    {
      waitpid(child, &i, WUNTRACED | WCONTINUED);
    }
}

void			create_socket(int port)
{
  int			cs;
  int			fd;
  struct protoent	*pe;
  struct sockaddr_in	sin;

  pe = getprotobyname("TCP");
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return ;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
      close(fd);
      return ;
    }
  while (1)
    {
      if ((cs = listen(fd, 1)) == -1)
	{
	  close(fd);
	  return ;
	}
      fork_proc(fd, cs);
    }
}

int			main(int ac, char **av)
{
  int			port;
  
  if (ac != 2)
    {
      printf("Usage: ./serveur port\n");
      return (EXIT_FAILURE);
    }
  port = atoi(av[1]);
  create_socket(port);
  return (EXIT_SUCCESS);
}
