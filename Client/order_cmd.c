/*
** read_cmd.c for read in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Sun Mar  8 18:10:36 2015 arthur
** Last update Wed Mar 11 14:52:51 2015 arthur
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "client.h"

int	get_count(char *buf)
{
  int	count;

  count = 0;
  while (*buf)
    {
      if (*buf == ' ')
	++count;
      ++buf;
    }
  return (count);
}

void	fill_tab(char ***res, char *buf)

{
  int	i;
  int	j;
  int	k;
  
  i = 0;
  j = 0;
  k = 0;
  while (buf[i])
    {
      if (buf[i] == ' ')
	{
	  (*res)[j][k] = 0;
	  k = 0;
	  ++j;
	}
      else
	{
	  (*res)[j][k] = buf[i];
	  ++k;
	}
      ++i;
    }
  (*res)[j][k] = 0;
  (*res)[++j] = NULL;
}

char	**split_args(char *buf)
{
  int	i;
  int	count;
  char	**res;

  i = 0;
  count = get_count(buf);
  if ((res = malloc(sizeof(char*) * (count + 2))) == NULL)
    exit(EXIT_FAILURE);
  if (count == 0)
    {
      res[0] = strdup(buf);
      res[1] = NULL;
      return (res);
    }
  while (i < count + 1)
    {
      res[i] = malloc(strlen(buf));
      ++i;
    }
  fill_tab(&res, buf);
  return (res);
}

char	*wtos(char **cmd)
{
  int	i;
  int	len;
  char	*res;

  i = len = 0;
  while (cmd[i])
    {
      len += strlen(cmd[i]);
      ++i;
    }
  if ((res = malloc(len + 1)) == NULL)
    return (NULL);
  i = 1;
  strcpy(res, cmd[0]);
  while (cmd[i])
    {
      strcat(res, " ");
      strcat(res, cmd[i]);
      ++i;
    }
  res[len + 1] = 0;
  return (res);
}
