/*
** file.c for file in /home/amstuta/rendu/PSU_2014_myftp/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 13 13:23:27 2015 arthur
** Last update Fri Mar 13 14:11:07 2015 arthur
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
  printf("%s\n", buf);
}

void	send_file(int fd, int sfd, char **args)
{
  int	rd;
  int	ffd;
  char	buf[LINE_SIZE];
  
  write(fd, wtos(args), strlen(wtos(args)));
  if ((rd = read(fd, buf, LINE_SIZE)) == -1)
    return ;
  buf[rd] = 0;
  if (strcmp(buf, "150") || ((ffd = open(args[1], O_RDONLY)) == -1))
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

void	file_transfer(int fd, char **args, char *ip)
{
  int	sfd;

  if ((sfd = new_server(ip)) == -1)
    return ;
  if (!strncmp(args[0], "STOR", 4))
    send_file(fd, sfd, args);
}
