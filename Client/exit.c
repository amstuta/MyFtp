/*
** exit.c for exit in /home/amstuta/rendu/PSU_2014_myftp/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Thu Mar 12 17:12:15 2015 arthur
** Last update Thu Mar 12 17:16:48 2015 arthur
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "client.h"

void	close_exit(int fd)
{
  char	buf[LINE_SIZE];
  
  write(fd, "QUIT\r\n", 6);
  if (read(fd, buf, LINE_SIZE) == -1)
    exit(EXIT_FAILURE);
  write(1, buf, strlen(buf));
  write(1, "\n", 1);
  exit(EXIT_SUCCESS);
}
