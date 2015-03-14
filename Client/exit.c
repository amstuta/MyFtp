/*
** exit.c for exit in /home/amstuta/rendu/PSU_2014_myftp/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Thu Mar 12 17:12:15 2015 arthur
** Last update Fri Mar 13 13:52:44 2015 arthur
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "client.h"

void	close_exit(int fd)
{
  int	rd;
  char	buf[LINE_SIZE];
  
  write(fd, "QUIT\r\n", 6);
  if ((rd = read(fd, buf, LINE_SIZE)) == -1)
    exit(EXIT_FAILURE);
  buf[rd] = 0;
  write(1, buf, strlen(buf));
  write(1, "\n", 1);
  close(fd);
  exit(EXIT_SUCCESS);
}
