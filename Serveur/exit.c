/*
** exit.c for exit in /home/amstuta/rendu/PSU_2014_myftp/Serveur
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Thu Mar 12 17:06:23 2015 arthur
** Last update Thu Mar 12 17:19:12 2015 arthur
*/

#include <unistd.h>
#include <stdlib.h>
#include "server.h"

void	close_client(int fd)
{
  write(fd, "221 - Closing connection\r\n", 26);
  close(fd);
  exit(EXIT_SUCCESS);
}
