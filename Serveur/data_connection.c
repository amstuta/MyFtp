/*
** data_connection.c for data in /home/amstuta/rendu/PSU_2014_myftp/Serveur
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 13 13:10:15 2015 arthur
** Last update Mon Mar 16 14:01:28 2015 arthur
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <time.h>
#include "server.h"

int			g_dfd;

int			accept_new_client()
{
  int			cs;
  struct sockaddr_in	sin_c;
  int			c_len;

  c_len = sizeof(sin_c);
  cs = accept(g_dfd, (struct sockaddr*)&sin_c, (socklen_t*)&c_len);
  if (cs == -1)
    {
      close(g_dfd);
      return (-1);
    }
  return (cs);
}

void			setopt(int fd)
{
  int yes;

  yes = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    perror("");
}

int			new_socket(int port)
{
  int			cs;
  int			fd;
  struct protoent	*pe;
  struct sockaddr_in	sin;
  
  pe = getprotobyname("TCP");
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (-1);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  setopt(fd);
  if (bind(fd, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
      close(fd);
      return (-1);
    }
  if ((cs = listen(fd, 1)) == -1)
    {
      close(fd);
      return (-1);
    }
  g_dfd = fd;
  return (0);
}
