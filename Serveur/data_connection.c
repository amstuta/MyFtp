/*
** data_connection.c for data in /home/amstuta/rendu/PSU_2014_myftp/Serveur
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 13 13:10:15 2015 arthur
** Last update Sat Mar 14 14:38:08 2015 arthur
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

int			accept_new_client(int fd, int cs)
{
  int			yes;
  struct sockaddr_in	sin_c;
  int			c_len;

  yes = 1;
  c_len = sizeof(sin_c);
  cs = accept(fd, (struct sockaddr*)&sin_c, (socklen_t*)&c_len);
  if (cs == -1)
    {
      close(fd);
      return (-1);
    }
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    perror(""); //
  return (cs);
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
  return (accept_new_client(fd, cs));
}

int			get_new_port()
{
  int			nport;

  nport = g_port;
  srand(time(0));
  while (nport == g_port)
    nport = rand() % 1024 + 1024;
  return (nport);
}
