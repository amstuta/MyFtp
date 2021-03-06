/*
** create_word_tab.c for create_word_tab in /home/douzie_l/rendu/Piscine-rattrapage-Jour_05PM/ex_01
** 
** Made by douzie_l
** Login   <douzie_l@epitech.net>
** 
** Started on  Fri Dec 20 14:11:36 2013 douzie_l
** Last update Thu Mar 12 13:49:40 2015 arthur
*/

#include <string.h>
#include <stdlib.h>
#include "client.h"

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
  if ((res = malloc(len + (i + 1))) == NULL)
    return (NULL);
  memset(res, 0, (len + 1));
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

int	count_word(char *str)
{
  int	i;
  int	word;

  i = 0;
  word = 0;
  while (str[i] != '\0')
    {
      if (str[i] == '\t' || str[i] == ' ')
	{
	  while (str[i] && (str[i] == ' ' || str[i] == '\t'))
	    ++i;
	  ++word;
	}
      ++i;
    }
  return (word + 1);
}

char	**fill_up_res(char **res, char *str, int i, int j)
{
  int	x;
  int	tmp;

  x = 0;
  tmp = i;
  while (str[tmp] != ' ' && str[tmp] != '\t' && str[tmp] != '\0')
    {
      tmp = tmp + 1;
      x = x + 1;
    }
  if ((res[j] = malloc((x + 1) * sizeof(char))) == NULL)
    return (NULL);
  x = 0;
  while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
    {
      res[j][x] = str[i];
      i = i + 1;
      x = x + 1;
    }
  res[j][x] = '\0';
  return (res);
}

char	**create_word_tab(char *str)
{
  char	**res;
  int	i;
  int	j;

  i = count_word(str);
  j = 1;
  if ((res = malloc((i + 1) * sizeof(char *))) == NULL)
    return (NULL);
  i = 0;
  res = fill_up_res(res, str, 0, 0);
  while (str[i] != '\0')
    {
      if (str[i] == ' ' || str[i] == '\t')
	{
	  while (str[i] && str[i] == ' ')
	    ++i;
	  res = fill_up_res(res, str, i, j);
	  j = j + 1;
	}
      i = i + 1;
    }
  res[j] = NULL;
  return (res);
}
