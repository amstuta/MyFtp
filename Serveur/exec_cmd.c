/*
** read_cmd.c for read in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Sun Mar  8 18:10:36 2015 arthur
** Last update Mon Mar 16 13:39:35 2015 arthur
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include "server.h"

void	execute_cmd(char *buf, char **args, char *home)
{
  if (!strcmp(buf, "LIST"))
    ls();
  else if (!strcmp(buf, "CWD"))
    cd(args[1], home);
  else if (!strncmp(buf, "PWD", 3))
    pwd();
  else if (!strncmp(buf, "RETR", 4))
    send_file(args[1]);
  else if (!strncmp(buf, "STOR", 4))
    receive_file(args[1]);
  else if (!strncmp(buf, "QUIT", 4))
    close_client();
  else
    write(g_fd, "666 - Unknown command", 21);
}

void	clean_cmd(char *buf, char *home)
{
  char	**args;

  args = create_word_tab(buf);
  execute_cmd((args != NULL) ? args[0] : buf, args, home);
}
