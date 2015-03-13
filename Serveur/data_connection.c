/*
** data_connection.c for data in /home/amstuta/rendu/PSU_2014_myftp/Serveur
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 13 13:10:15 2015 arthur
** Last update Fri Mar 13 13:13:18 2015 arthur
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include "server.h"

int			accept_new_client(int fd, int cs)
{
  struct sockaddr_in	sin_c;
  int			c_len;

  c_len = sizeof(sin_c);
  cs = accept(fd, (struct sockaddr*)&sin_c, (socklen_t*)&c_len);
  if (cs == -1)
    return (-1);
  return (cs);
}

int			new_socket()
{
  int			cs;
  int			fd;
  struct protoent	*pe;
  struct sockaddr_in	sin;
  
  pe = getprotobyname("TCP");
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (-1);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(DATA_PORT);
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
