/*
** check_cmd.c for check in /home/amstuta/rendu/PSU_2014_myftp/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Wed Mar 11 11:11:35 2015 arthur
** Last update Wed Mar 11 14:51:34 2015 arthur
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "client.h"

char	**clean_cmd(char *cmd)
{
  int	i;
  char	**res;

  i = 0;
  while (cmd[i])
    {
      if (cmd[i] == '\n')
	{
	  cmd[i] = 0;
	  break ;
	}
      ++i;
    }
  if (!(res = split_args(cmd)))
    return (NULL);
  if (!check_cmd(res[0]))
    return (NULL);
  res[0] = real_cmd(res[0]);
  return (res);
}

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

char	*real_cmd(char *cmd)
{
  char	*res;

  res = NULL;
  if (!strcmp(cmd, "ls"))
    res = strdup("LIST ");
  else if (!strcmp(cmd, "cd"))
    res = strdup("CWD ");
  else if (!strcmp(cmd, "get"))
    res = strdup("RETR ");
  else if (!strcmp(cmd, "put"))
    res = strdup("STOR ");
  else if (!strcmp(cmd, "pwd"))
    res = strdup("PWD\r\n");
  return (res);
}
