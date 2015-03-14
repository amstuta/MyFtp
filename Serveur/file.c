/*
** file.c for file in /home/amstuta/rendu/PSU_2014_myftp/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 13 11:37:17 2015 arthur
** Last update Sat Mar 14 11:59:15 2015 arthur
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "server.h"

void			end_transfer(int fd, int sfd, int ffd)
{ 
  close(ffd);
  close(sfd);
  write(fd, "226 - File successfully transfered", 34);
}

void			send_file(int fd, char *file)
{
  int			rd;
  int			ffd;
  int			sfd;
  char			tmp[LINE_SIZE + 1];

  if ((sfd = new_socket()) == -1)
    {
      write(fd, "666 - Couldn't open data connection", 35);
      return ;
    }
  write(fd, "150", 3);
  if ((ffd = open(file, O_RDONLY)) == -1)
    {
      write(fd, "666 - Couldn't open file", 24);
      return ;
    }
  while ((rd = read(ffd, tmp, LINE_SIZE)) > 0)
    {
      tmp[rd] = 0;
      write(sfd, tmp, strlen(tmp));
      memset(tmp, 0, LINE_SIZE);
    }
  end_transfer(fd, sfd, ffd);
}

void			receive_file(int fd, char *file)
{
  int			rd;
  int			ffd;
  int			sfd;
  char			tmp[LINE_SIZE];

  if ((sfd = new_socket()) == -1)
    {
      write(fd, "666 - Couldn't open data connection", 35);
      return ;
    }
  write(fd, "150", 3);
  if ((ffd = open(file, O_RDWR | O_CREAT, 0666)) == -1)
    {
      write(fd, "666 - Couldn't create file", 27);
      return ;
    }
  while ((rd = read(sfd, tmp, LINE_SIZE)) > 0)
    {
      tmp[rd] = 0;
      write(ffd, tmp, strlen(tmp));
      memset(tmp, 0, LINE_SIZE);
    }
  end_transfer(fd, sfd, ffd);
}
