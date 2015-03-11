/*
** ls.c for ls in /home/amstuta/rendu/PSU_2014_myftp/Serveur
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Tue Mar 10 17:26:34 2015 arthur
** Last update Wed Mar 11 18:05:59 2015 arthur
*/

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "server.h"

int		ls(int fd)
{
  DIR		*dir;
  struct dirent	*rd;
  char		res[LINE_SIZE];

  memset(res, 0, LINE_SIZE);
  if (!(dir = opendir(".")))
    return (-1);
  while ((rd = readdir(dir)))
    {
      if (rd->d_name[0] != '.')
	{
	  strcat(res, rd->d_name);
	  strcat(res, " ");
	}
    }
  write(fd, res, strlen(res));
  return (0);
}

int		cd(char *arg)
{
  return (chdir(arg));
}

int		pwd(int fd)
{
  char		res[LINE_SIZE];
  char		pwd[LINE_SIZE];

  memset(res, 0, LINE_SIZE);
  if (!getcwd(pwd, LINE_SIZE))
    return (-1);
  strcat(res, "Current path: ");
  if (strlen(pwd) + 14 < LINE_SIZE)
    strcat(res, pwd);
  else
    strncat(res, pwd, strlen(pwd) - 14);
  write(fd, res, strlen(res));
  return (0);
}
