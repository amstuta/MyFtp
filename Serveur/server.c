/*
** main.c for main in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Tue Mar  3 15:17:53 2015 arthur
** Last update Fri Mar 13 19:22:24 2015 arthur
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
#include "server.h"

void			read_cmd(int fd, char *home)
{
  int			rd;
  char			buf[LINE_SIZE];
  
  if ((rd = read(fd, buf, LINE_SIZE)) == -1)
    {
      close(fd);
      exit(EXIT_FAILURE);
    }
  buf[rd] = 0;
  clean_cmd(buf, fd, home);
}

void			fork_proc(int cs)
{
  int			child;
  char			pwd[LINE_SIZE];

  if ((child = fork()) == -1)
    return ;
  if (!getcwd(pwd, LINE_SIZE))
    return ;
  if (child == 0)
    {
      if (check_client(cs) == -1)
	{
	  close(cs);
	  return ;
	}
      while (1)
	read_cmd(cs, pwd);
    }
}

void			accept_client(int fd, int cs)
{
  struct sockaddr_in	sin_c;
  int			c_len;

  c_len = sizeof(sin_c);
  while (1)
    {
      cs = accept(fd, (struct sockaddr*)&sin_c, (socklen_t*)&c_len);
      if (cs == -1)
	return ;
      fork_proc(cs);
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
  if ((cs = listen(fd, 1)) == -1)
    {
      close(fd);
      return ;
    }
  accept_client(fd, cs);
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
