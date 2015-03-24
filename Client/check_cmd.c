/*
** check_cmd.c for check in /home/amstuta/rendu/PSU_2014_myftp/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Wed Mar 11 11:11:35 2015 arthur
** Last update Tue Mar 24 17:02:12 2015 Arthur Amstutz
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "client.h"

char	*spec_cmd(char *cmd, char **res, int fd, char *ip)
{
  res[0] = real_cmd(res[0], fd);
  if (!strncmp(cmd, "get", 3) || !strncmp(cmd, "put", 3))
    {
      file_transfer(fd, res, ip);
      return (NULL);
    }
  else if (!strncmp(cmd, "ls", 2))
    {
      rec_ls(fd, ip, res);
      return (NULL);
    }
  else if (!strncmp(cmd, "cd", 2))
    {
      strcat(res[1], "\r\n");
      return (wtos(res));
    }
  if (!check_cmd(cmd))
    return (NULL);
  return (real_cmd(cmd, fd));
}

char	*clean_cmd(char *cmd, int fd, char *ip)
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
  return (spec_cmd(cmd, res, fd, ip));
}

int     check_cmd(char *cmd)
{
  if (!strcmp(cmd, "ls") ||
      !strncmp(cmd, "cd", 2) ||
      !strcmp(cmd, "get") ||
      !strcmp(cmd, "put") ||
      !strcmp(cmd, "pwd") ||
      !strcmp(cmd, "quit"))
    return (1);
  else
    write(1, "Error: unknown command\n", 23);
  return (0);
}

char	*real_cmd(char *cmd, int fd)
{
  char	*res;

  res = NULL;
  if (!strcmp(cmd, "ls"))
    res = strdup("LIST \r\n");
  else if (!strncmp(cmd, "cd", 2))
    res = strdup("CWD");
  else if (!strcmp(cmd, "get"))
    res = strdup("RETR");
  else if (!strcmp(cmd, "put"))
    res = strdup("STOR");
  else if (!strcmp(cmd, "pwd"))
    res = strdup("PWD \r\n");
  else if (!strcmp(cmd, "quit"))
    close_exit(fd);
  return (res);
}
