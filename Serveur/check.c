/*
** check.c for check in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Sun Mar  8 20:40:00 2015 arthur
** Last update Thu Mar 12 11:14:52 2015 arthur
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

int	check_client(int fd)
{
  char	tmp[LINE_SIZE];
  
  write(fd, "220", 3);
  memset(tmp, 0, LINE_SIZE);
  if (read(fd, tmp, LINE_SIZE) == -1)
    return (-1);
  if (strncmp(tmp, "USER Anonymous", 14))
    {
      write(fd, ERROR, 3);
      return (-1);
    }
  write(fd, "331", 3);
  memset(tmp, 0, LINE_SIZE);
  if (read(fd, tmp, LINE_SIZE) == -1)
    return (-1);
  if (strncmp(tmp, "PASS ", 5))
    {
      write(fd, ERROR, 3);
      return (-1);
    }
  write(fd, "230", 3);
  return (0);
}
