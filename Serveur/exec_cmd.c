/*
** read_cmd.c for read in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Sun Mar  8 18:10:36 2015 arthur
** Last update Wed Mar 11 15:19:12 2015 arthur
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include "server.h"

void	execute_cmd(char *buf, char **args, int fd)
{
  if (!strcmp(buf, "LIST"))
    {
      ls();
      write(fd, "Success\n", 8);
    }
  else if (!strcmp(buf, "CWD"))
    {
      cd(args[1]);
      write(fd, "Success\n", 8);
    }
  else if (!strncmp(buf, "PWD", 3))
    {
      pwd();
      write(fd, "Success\n", 8);
    }
  else
    write(fd, "Failure\n", 8);
}

void	clean_cmd(char *buf, int fd)
{
  char	**args;

  args = create_word_tab(buf);
  execute_cmd((args != NULL) ? args[0] : buf, args, fd);
}
