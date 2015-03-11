/*
** read_cmd.c for read in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Sun Mar  8 18:10:36 2015 arthur
** Last update Wed Mar 11 18:21:26 2015 arthur
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include "server.h"

void	execute_cmd(char *buf, char **args, int fd, char *home)
{
  if (!strcmp(buf, "LIST"))
    ls(fd);
  else if (!strcmp(buf, "CWD"))
    cd(args[1], home, fd);
  else if (!strncmp(buf, "PWD", 3))
    pwd(fd);
  else
    write(fd, "Failure\n", 8);
}

void	clean_cmd(char *buf, int fd, char *home)
{
  char	**args;

  args = create_word_tab(buf);
  execute_cmd((args != NULL) ? args[0] : buf, args, fd, home);
}
