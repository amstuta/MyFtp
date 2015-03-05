/*
** main.c for main in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Tue Mar  3 15:17:53 2015 arthur
** Last update Thu Mar  5 20:51:51 2015 arthur
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <string.h>
#include <errno.h>

void			create_socket(char *ip, int port)
{
  int			fd;
  struct protoent	*pe;
  struct sockaddr_in	sin;

  pe = getprotobyname("TCP");
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return ;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(ip);
  if (connect(fd, (const struct sockaddr*)&sin, sizeof(sin)) == -1) // Erreur arch linux: connection refused
    {
      close(fd);
      return ;
    }
  write(fd, "Salut", 5);
  close(fd);
}

int			main(int ac, char **av)
{
  int			port;
  
  if (ac != 3)
    {
      printf("Usage: ./client ip port\n");
      return (EXIT_FAILURE);
    }
  port = atoi(av[2]);
  create_socket(av[1], port);
  return (EXIT_SUCCESS);
}
