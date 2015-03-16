/*
** check.c for check in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Sun Mar  8 20:40:00 2015 arthur
** Last update Mon Mar 16 13:40:04 2015 arthur
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

int	check_client()
{
  char	tmp[LINE_SIZE];
  
  write(g_fd, "220", 3);
  memset(tmp, 0, LINE_SIZE);
  if (read(g_fd, tmp, LINE_SIZE) == -1)
    return (-1);
  if (strncmp(tmp, "USER Anonymous", 14))
    {
      write(g_fd, ERROR, 3);
      return (-1);
    }
  write(g_fd, "331", 3);
  memset(tmp, 0, LINE_SIZE);
  if (read(g_fd, tmp, LINE_SIZE) == -1)
    return (-1);
  if (strncmp(tmp, "PASS ", 5))
    {
      write(g_fd, ERROR, 3);
      return (-1);
    }
  write(g_fd, "230", 3);
  return (0);
}
