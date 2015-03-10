/*
** check.c for check in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Sun Mar  8 20:40:00 2015 arthur
** Last update Tue Mar 10 14:36:25 2015 arthur
*/

#include <unistd.h>
#include <string.h>
#include "server.h"

int	check_cmd(char *cmd)
{
  if (!strcmp(cmd, "ls") ||
      !strcmp(cmd, "cd") ||
      !strcmp(cmd, "get") ||
      !strcmp(cmd, "put") ||
      !strcmp(cmd, "pwd"))
    return (1);
  return (0);
}

int	check_client(int fd)
{
  char	tmp[LINE_SIZE];
  
  write(fd, "220", 3);
  if (read(fd, tmp, LINE_SIZE) == -1)
    return (-1);
  if (!strstr(tmp, "USER") || \
      !strstr(tmp, "Anonymous\n\r"))
    {
      write(fd, ERROR, 3);
      return (-1);
    }
  write(fd, "331", 3);
  if (read(fd, tmp, LINE_SIZE) == -1)
    return (-1);
  if (!strstr(tmp, "PASS"))
    {
      write(fd, ERROR, 3);
      return (-1);
    }
  write(fd, "230", 3);
  // Reste CWD && CDUP
  return (0);
}
