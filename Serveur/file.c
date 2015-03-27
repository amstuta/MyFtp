/*
** file.c for file in /home/amstuta/rendu/PSU_2014_myftp/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 13 11:37:17 2015 arthur
** Last update Fri Mar 27 11:04:54 2015 arthur
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
#include <stdio.h>
#include "server.h"

void			end_transfer(int sfd, int ffd)
{
  close(ffd);
  close(sfd);
  write(g_fd, "226 - File successfully transfered\r\n", 36);
}

void			send_file(char *file)
{
  int			rd;
  int			ffd;
  int			sfd;
  char			tmp[LINE_SIZE + 1];

  write(g_fd, "150 \r\n", 6);
  if ((sfd = accept_new_client()) == -1)
    {
      write(g_fd, "666 - Couldn't open data connection\r\n", 37);
      return ;
    }
  if ((ffd = open(file, O_RDONLY)) == -1)
    {
      close(sfd);
      write(g_fd, "666 - Couldn't open file\r\n", 26);
      return ;
    }
  while ((rd = read(ffd, tmp, LINE_SIZE)) > 0)
    {
      tmp[rd] = 0;
      write(sfd, tmp, strlen(tmp));
      memset(tmp, 0, LINE_SIZE);
    }
  end_transfer(sfd, ffd);
}

void			receive_file(char *file)
{
  int			rd;
  int			ffd;
  int			sfd;
  char			tmp[LINE_SIZE];

  write(g_fd, "150 \r\n", 6);
  if ((sfd = accept_new_client()) == -1)
    {
      write(g_fd, "666 - Couldn't open data connection\r\n", 37);
      return ;
    }
  if ((ffd = open(file, O_RDWR | O_CREAT, 0666)) == -1)
    {
      write(g_fd, "666 - Couldn't create file\r\n", 29);
      return ;
    }
  while ((rd = read(sfd, tmp, LINE_SIZE)) > 0)
    {
      tmp[rd] = 0;
      write(ffd, tmp, strlen(tmp));
      memset(tmp, 0, LINE_SIZE);
    }
  end_transfer(sfd, ffd);
}
