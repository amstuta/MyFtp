/*
** check.c for check in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Sun Mar  8 20:40:00 2015 arthur
** Last update Sun Mar  8 20:43:21 2015 arthur
*/

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
