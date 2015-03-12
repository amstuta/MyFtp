/*
** check_cmd.c for check in /home/amstuta/rendu/PSU_2014_myftp/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Wed Mar 11 11:11:35 2015 arthur
** Last update Thu Mar 12 17:12:07 2015 arthur
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "client.h"

char	**clean_cmd(char *cmd, int fd)
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
  if (!(res = create_word_tab(cmd)))
    return (NULL);
  if (!check_cmd(res[0]))
    return (NULL);
  res[0] = real_cmd(res[0], fd);
  return (res);
}

int     check_cmd(char *cmd)
{
  if (!strcmp(cmd, "ls") ||
      !strcmp(cmd, "cd") ||
      !strcmp(cmd, "get") ||
      !strcmp(cmd, "put") ||
      !strcmp(cmd, "pwd") ||
      !strcmp(cmd, "quit"))
    return (1);
  return (0);
}

char	*real_cmd(char *cmd, int fd)
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
  else if (!strcmp(cmd, "quit"))
    close_exit(fd);
  return (res);
}
