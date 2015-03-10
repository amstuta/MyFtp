/*
** server.h for server in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Sun Mar  8 18:47:04 2015 arthur
** Last update Sun Mar  8 20:43:39 2015 arthur
*/

#ifndef SERVER_H_
# define SERVER_H_

void	read_cmd(int);
void	accept_client(int, int);
void	create_socket(int);
void	execute_cmd(char *, char **, int);
int	get_count(char *);
void	fill_tab(char ***, char *);
char	**split_args(char *);
void	clean_cmd(char *, int);
int	check_cmd(char *);

#endif
