/*
** ls.c for ls in /home/amstuta/rendu/PSU_2014_myftp/Serveur
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Tue Mar 10 17:26:34 2015 arthur
** Last update Thu Mar 12 17:23:24 2015 arthur
*/

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "server.h"

void		ls(int fd)
{
  DIR		*dir;
  struct dirent	*rd;
  char		res[LINE_SIZE];

  // Ouvrir new socket
  memset(res, 0, LINE_SIZE);
  if (!(dir = opendir(".")))
    {
      write(fd, "666 - Error: can't list files\r\n", 31);
      return ;
    }
  // Write 150 puis open socket
  strcpy(res, "150 - ");
  while ((rd = readdir(dir)))
    {
      if (rd->d_name[0] != '.' &&
	  (strlen(res) + strlen(rd->d_name) + 1 < LINE_SIZE))
	{
	  strcat(res, rd->d_name);
	  strcat(res, " ");
	}
    }
  write(fd, res, strlen(res));
}

char		*check_cd(char *home, char *dest)
{
  char		*full_path;
  char		pwd[LINE_SIZE];
  
  if (!(full_path = malloc(LINE_SIZE)))
    return (NULL);
  if (!getcwd(pwd, LINE_SIZE))
    return (NULL);
  strcpy(full_path, pwd);
  if (!strcmp(home, full_path) && !strcmp(dest, ".."))
    return (NULL);
  return (full_path);
}

void		cd(char *arg, char *home, int fd)
{
  char		*full_path;
  char		res[LINE_SIZE];

  if ((full_path = check_cd(home, arg)) == NULL)
    {
      write(fd, "666 - You can't go there", 26);
      return ;
    }
  strcat(full_path, "/");
  strcat(full_path, arg);
  if (chdir(full_path) == -1)
    write(fd, "666 - Couldn't change directory", 33);
  else
    {
      memset(res, 0, LINE_SIZE);
      strcat(res, "250 - New path: ");
      if (strlen(full_path) < (LINE_SIZE - 16))
	strcat(res, full_path);
      else
	strncat(res, full_path, LINE_SIZE - 16);
      write(fd, res, strlen(res));
    }
}

void		pwd(int fd)
{
  char		res[LINE_SIZE];
  char		pwd[LINE_SIZE];

  memset(res, 0, LINE_SIZE);
  if (!getcwd(pwd, LINE_SIZE))
    {
      write(fd, "666 - Error: can't get pwd", 26);
      return ;
    }
  strcat(res, "257 - Current path: ");
  if (strlen(pwd) + 20 < LINE_SIZE)
    strcat(res, pwd);
  else
    strncat(res, pwd, strlen(pwd) - 20);
  write(fd, res, strlen(res));
}
