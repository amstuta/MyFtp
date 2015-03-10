/*
** server.h for server in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Sun Mar  8 18:47:04 2015 arthur
** Last update Tue Mar 10 17:52:56 2015 arthur
*/

#ifndef SERVER_H_
# define SERVER_H_

# define ERROR		"444"
# define LINE_SIZE	4096

void	read_cmd(int);
void	accept_client(int, int);
void	create_socket(int);
void	execute_cmd(char *, char **, int);
int	get_count(char *);
void	fill_tab(char ***, char *);
char	**split_args(char *);
void	clean_cmd(char *, int);
int	check_cmd(char *);
int	check_client(int);
int	ls();
int	pwd();
int	cd(char *);

#endif
