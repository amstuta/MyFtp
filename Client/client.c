/*
** main.c for main in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Tue Mar  3 15:17:53 2015 arthur
** Last update Sat Mar 14 11:52:20 2015 arthur
*/

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include "client.h"

static int		g_fd;

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

void			prompt(char *ip)
{
  int			rd;
  char			**cmd_args;
  char			buf[LINE_SIZE];
  char			rep[LINE_SIZE];

  write(1, " > ", 3);
  while (read(0, buf, LINE_SIZE) > 0)
    {
      if ((cmd_args = clean_cmd(buf, g_fd, ip)) != NULL)
	{
	  write(g_fd, wtos(cmd_args), strlen(wtos(cmd_args)));
	  if ((rd = read(g_fd, rep, LINE_SIZE)) == -1)
	    return ;
	  rep[rd] = 0;
	  write(1, rep, strlen(rep));
	  write(1, "\n", 1);
	}
      write(1, " > ", 3);
    }
}

void			exit_signal(int sig)
{
  (void)sig;
  close(g_fd);
  exit(EXIT_SUCCESS);
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
  if (port == DATA_PORT)
    {
      printf("Error: port already used for datas\n");
      return (EXIT_FAILURE);
    }
  fd = create_socket(av[1], port);
  g_fd = fd;
  signal(SIGINT, exit_signal);
  if (auth_to_server(fd) != -1)
    prompt(av[1]);
  close(g_fd);
  return (EXIT_SUCCESS);
}
