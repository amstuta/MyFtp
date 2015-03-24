/*
** main.c for main in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Tue Mar  3 15:17:53 2015 arthur
** Last update Tue Mar 24 16:56:14 2015 Arthur Amstutz
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
int			g_dport;

int			create_socket(char *ip, int port)
{
  int			fd;
  struct protoent	*pe;
  struct sockaddr_in	sin;

  pe = getprotobyname("TCP");
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    {
      perror("");
      exit(EXIT_FAILURE);
    }
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(ip);
  if (connect(fd, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
      perror("");
      close(fd);
      exit(EXIT_FAILURE);
    }
  return (fd);
}

void			prompt(char *ip)
{
  int			rd;
  char			*cmd;
  char			buf[LINE_SIZE];
  char			rep[LINE_SIZE];

  write(1, " > ", 3);
  while (read(0, buf, LINE_SIZE) > 0)
    {
      if ((cmd = clean_cmd(buf, g_fd, ip)) != NULL)
	{
	  write(g_fd, cmd, strlen(cmd));
	  if ((rd = read(g_fd, rep, LINE_SIZE)) == -1)
	    return ;
	  rep[rd] = 0;
	  write(1, rep, strlen(rep));
	  write(1, "\n", 1);
	}
      memset(buf, 0, LINE_SIZE);
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
  fd = create_socket(av[1], port);
  g_fd = fd;
  g_dport = port - 1;
  signal(SIGINT, exit_signal);
  if (auth_to_server(fd) != -1)
    prompt(av[1]);
  close(g_fd);
  return (EXIT_SUCCESS);
}
