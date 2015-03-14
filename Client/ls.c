/*
** ls.c for ls in /home/amstuta/rendu/PSU_2014_myftp/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 13 16:01:06 2015 arthur
** Last update Sat Mar 14 13:02:16 2015 arthur
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "client.h"

void	print_files(int fd, int sfd)
{
  int	rd;
  char	buf[LINE_SIZE];

  memset(buf, 0, LINE_SIZE);
  while ((rd = read(sfd, buf, LINE_SIZE)) > 0)
    {
      buf[rd] = 0;
      write(1, buf, strlen(buf));
      memset(buf, 0, LINE_SIZE);
    }
  write(1, "\n", 1);
  close(sfd);
  if ((rd = read(fd, buf, LINE_SIZE)) <= 0)
    return ;
  buf[rd] = 0;
  write(1, buf, strlen(buf));
  write(1, "\n", 1);
}

void	rec_ls(int fd, char *ip, char **args)
{
  int	rd;
  int	sfd;
  int	nport;
  char	buf[LINE_SIZE];

  write(fd, wtos(args), strlen(wtos(args)));
  if ((rd = read(fd, buf, LINE_SIZE)) <= 0)
    return ;
  buf[rd] = 0;
  if (strncmp(buf, "150", 3))
    {
      write(1, buf, strlen(buf));
      write(1, "\n", 1);
      return ;
    }
  nport = get_new_port(buf);
  if ((sfd = new_server(ip, nport)) == -1)
    {
      if ((rd = read(fd, buf, LINE_SIZE)) <= 0)
	return ;
      buf[rd] = 0;
      write(1, buf, strlen(buf));
      write(1, "\n", 1);
      return ;
    }
  
  print_files(fd, sfd);
}
