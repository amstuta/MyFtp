/*
** data_connection.c for data in /home/amstuta/rendu/PSU_2014_myftp/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 13 13:24:11 2015 arthur
** Last update Sat Mar 14 13:01:46 2015 arthur
*/

#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "client.h"

int			new_server(char *ip, int nport)
{
  int			fd;
  struct protoent	*pe;
  struct sockaddr_in	sin;

  pe = getprotobyname("TCP");
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (-1);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(nport);
  sin.sin_addr.s_addr = inet_addr(ip);
  if (connect(fd, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
      perror("");
      close(fd);
      return (-1);
    }
  return (fd);
}

int			get_new_port(char *buf)
{
  int			i;
  int			spaces;

  i = 0;
  spaces = 0;
  while (buf[i])
    {
      if (buf[i] == ' ')
	++spaces;
      if (spaces == 2)
	break;
      ++i;
    }
  return (atoi(&buf[i + 1]));
}
