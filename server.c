/*
** main.c for main in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Tue Mar  3 15:17:53 2015 arthur
** Last update Tue Mar  3 16:03:37 2015 arthur
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

void			accept_client(int fd, int cs, struct sockaddr_in *sin)
{
  char			*ip;
  struct sockaddr_in	sin_c;
  int			c_len;

  c_len = sizeof(sin_c);
  if ((cs = accept(fd, (struct sockaddr*)&sin_c, (socklen_t*)&c_len)) == -1)
    {
      printf("accept");
      return ;
    }
  ip = inet_ntoa(sin_c.sin_addr);
  write(cs, "Salut, toi!\nIP: ", 16);
  write(cs, ip, strlen(ip));
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
  accept_client(fd, cs, &sin);
  close(fd);
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
