/*
** main.c for main in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Tue Mar  3 15:17:53 2015 arthur
** Last update Tue Mar 10 14:58:27 2015 arthur
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include "client.h"

int			auth_to_server(int fd)
{
  char			tmp[LINE_SIZE];
  
  if (read(fd, tmp, LINE_SIZE) == -1)
    return (-1);
  if (strcmp(tmp, "220"))
    return (-1);
  write(fd, "USER Anonymous\n\r", 16);
  if (read(fd, tmp, LINE_SIZE) == -1)
    return (-1);
  if (strcmp(tmp, "331"))
    return (-1);
  write(fd, "PASS \n\r", 7);
  if (read(fd, tmp, LINE_SIZE) == -1)
    return (-1);
  if (strcmp(tmp, "230"))
    return (-1);
  // reste CWD && CDUP
  return (0);
}

int			create_socket(char *ip, int port)
{
  int			fd;
  struct protoent	*pe;
  struct sockaddr_in	sin;

  pe = getprotobyname("TCP");
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    {
      printf("Error: can't create socket\n");
      exit(EXIT_FAILURE);
    }
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(ip);
  if (connect(fd, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
      printf("Error: can't connect to server\n");
      close(fd);
      exit(EXIT_FAILURE);
    }
  return (fd);
}

void			prompt(int fd)
{
  int			rd;
  char			*buf;
  char			*rep;

  if ((buf = malloc(LINE_SIZE + 1)) == NULL)
    exit(EXIT_FAILURE);
  if ((rep = malloc(LINE_SIZE + 1)) == NULL)
    exit(EXIT_FAILURE);
  write(1, " > ", 3);
  while (read(0, buf, LINE_SIZE) != -1)
    {
      write(fd, buf, strlen(buf));
      if ((rd = read(fd, rep, LINE_SIZE)) == -1)
	return ;
      rep[rd] = 0;
      write(1, rep, strlen(rep));
      write(1, " > ", 3);
    }
}

int			main(int ac, char **av)
{
  int			fd;
  int			port;
  
  if (ac != 3)
    {
      printf("Usage: ./client ip port\n");
      return (EXIT_FAILURE);
    }
  port = atoi(av[2]);
  fd = create_socket(av[1], port);
  if (auth_to_server(fd) != -1)
    prompt(fd);
  close(fd);
  return (EXIT_SUCCESS);
}
