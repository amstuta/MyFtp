/*
** auth.c for auth in /home/amstuta/rendu/PSU_2014_myftp/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 13 15:32:12 2015 arthur
** Last update Fri Mar 27 11:13:52 2015 arthur
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "client.h"

int			check_user(int fd)
{
  char			tmp[LINE_SIZE];
  char			login[LINE_SIZE];

  memset(tmp, 0, LINE_SIZE);
  memset(login, 0, LINE_SIZE);
  strcat(login, "USER Anonymous\r\n");
  write(fd, login, strlen(login));
  memset(tmp, 0, LINE_SIZE);
  if (read(fd, tmp, LINE_SIZE) == -1)
    return (-1);
  if (!strncmp(tmp, "230", 3))
    return (0);
  else if (!strncmp(tmp, "331", 3))
    {
      write(fd, "PASS \r\n", 7);
      if (read(fd, tmp, LINE_SIZE) == -1)
	return (-1);
      if (strncmp(tmp, "230", 3))
	return (-1);
    }
  else
    return (-1);
  return (0);
}

int			auth_to_server(int fd)
{
  char			tmp[LINE_SIZE];

  memset(tmp, 0, LINE_SIZE);
  if (read(fd, tmp, LINE_SIZE) == -1)
    return (-1);
  if (strncmp(tmp, "220", 3))
    return (-1);
  if (check_user(fd) == -1)
    return (-1);
  return (0);
}
