/*
** auth.c for auth in /home/amstuta/rendu/PSU_2014_myftp/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 13 15:32:12 2015 arthur
** Last update Fri Mar 13 15:33:55 2015 arthur
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "client.h"

int			check_user(int fd)
{
  int			rd;
  char			tmp[LINE_SIZE];
  char			login[LINE_SIZE];

  memset(tmp, 0, LINE_SIZE);
  write(1, "Please enter your login: ", 25);
  if ((rd = read(0, tmp, LINE_SIZE)) <= 0)
    return (-1);
  tmp[rd] = 0;
  memset(login, 0, LINE_SIZE);
  strcat(login, "USER ");
  strcat(login, tmp);
  strcat(login, "\r\n");
  write(fd, login, strlen(login));
  memset(tmp, 0, LINE_SIZE);
  if (read(fd, tmp, LINE_SIZE) == -1)
    return (-1);
  if (strcmp(tmp, "331"))
    {
      write(1, "Wrong user, exiting...\n", 23);
      return (-1);
    }
  return (0);
}

int			auth_to_server(int fd)
{
  char			tmp[LINE_SIZE];

  memset(tmp, 0, LINE_SIZE);
  if (read(fd, tmp, LINE_SIZE) == -1)
    return (-1);
  if (strcmp(tmp, "220"))
    return (-1);
  if (check_user(fd) == -1)
    return (-1);
  write(fd, "PASS \n\r", 7);
  if (read(fd, tmp, LINE_SIZE) == -1)
    return (-1);
  if (strcmp(tmp, "230"))
    return (-1);
  return (0);
}
