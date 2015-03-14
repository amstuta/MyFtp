/*
** file.c for file in /home/amstuta/rendu/PSU_2014_myftp/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 13 13:23:27 2015 arthur
** Last update Sat Mar 14 13:09:54 2015 arthur
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "client.h"

void	end_transfer(int fd, int sfd, int ffd)
{
  int	rd;
  char	buf[LINE_SIZE];
  
  close(ffd);
  close(sfd);
  if ((rd = read(fd, buf, LINE_SIZE)) == -1)
    return ;
  buf[rd] = 0;
  write(1, buf, strlen(buf));
  write(1, "\n", 1);
}

void	send_file(int fd, int sfd, char **args)
{
  int	rd;
  int	ffd;
  char	buf[LINE_SIZE];

  if ((ffd = open(args[1], O_RDONLY)) == -1)
    return ;
  memset(buf, 0, LINE_SIZE);
  while ((rd = read(ffd, buf, LINE_SIZE)) > 0)
    {
      buf[rd] = 0;
      write(sfd, buf, strlen(buf));
      memset(buf, 0, LINE_SIZE);
    }
  end_transfer(fd, sfd, ffd);
}

void	receive_file(int fd, int sfd, char **args)
{
  int	rd;
  int	ffd;
  char	buf[LINE_SIZE];

  if ((ffd = open(args[1], O_WRONLY | O_CREAT, 0666)) == -1)
    return ;
  memset(buf, 0, LINE_SIZE);
  while ((rd = read(sfd, buf, LINE_SIZE)) > 0)
    {
      buf[rd] = 0;
      write(ffd, buf, strlen(buf));
      memset(buf, 0, LINE_SIZE);
    }
  end_transfer(fd, sfd, ffd);
}

void	file_transfer(int fd, char **args, char *ip)
{
  int	rd;
  int	sfd;
  int	nport;
  char	buf[LINE_SIZE];

  write(fd, wtos(args), strlen(wtos(args)));
  if ((rd = read(fd, buf, LINE_SIZE)) == -1)
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
    return ;
  if (!strncmp(args[0], "STOR", 4))
    send_file(fd, sfd, args);
  else if (!strncmp(args[0], "RETR", 4))
    receive_file(fd, sfd, args);
}
