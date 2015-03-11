/*
** check_cmd.c for check in /home/amstuta/rendu/PSU_2014_myftp/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Wed Mar 11 11:11:35 2015 arthur
** Last update Wed Mar 11 11:15:00 2015 arthur
*/

#include "client.h"

int     check_cmd(char *cmd)
{
  if (!strcmp(cmd, "ls") ||
      !strcmp(cmd, "cd") ||
      !strcmp(cmd, "get") ||
      !strcmp(cmd, "put") ||
      !strcmp(cmd, "pwd"))
    return (1);
  return (0);
}
