/*
** exit.c for exit in /home/amstuta/rendu/PSU_2014_myftp/Serveur
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Thu Mar 12 17:06:23 2015 arthur
** Last update Mon Mar 16 13:40:37 2015 arthur
*/

#include <unistd.h>
#include <stdlib.h>
#include "server.h"

void	close_client()
{
  write(g_fd, "221 - Closing connection\r\n", 26);
  close(g_fd);
  exit(EXIT_SUCCESS);
}

void	exit_signal(int sig)
{
  (void)sig;
  close(g_fd);
  close(g_dfd);
  exit(EXIT_SUCCESS);
}
