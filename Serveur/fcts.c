/*
** ls.c for ls in /home/amstuta/rendu/PSU_2014_myftp/Serveur
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Tue Mar 10 17:26:34 2015 arthur
** Last update Tue Mar 10 17:43:06 2015 arthur
*/

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "server.h"

int		ls()
{
  DIR		*dir;
  struct dirent	*rd;

  if (!(dir = opendir(".")))
    return (-1);
  while ((rd = readdir(dir)))
    {
      if (strcmp(rd->d_name, ".") &&
	  strcmp(rd->d_name, ".."))
      printf("--> %s\n", rd->d_name);
    }
  return (0);
}

int		cd(char *arg)
{
  return (chdir(arg));
}
