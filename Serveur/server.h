/*
** server.h for server in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Sun Mar  8 18:47:04 2015 arthur
** Last update Wed Mar 11 18:11:08 2015 arthur
*/

#ifndef SERVER_H_
# define SERVER_H_

# define ERROR		"444"
# define LINE_SIZE	4096

void	read_cmd(int, char *);
void	accept_client(int, int);
void	create_socket(int);
void	execute_cmd(char *, char **, int, char *);
void	clean_cmd(char *, int, char *);
int	check_cmd(char *);
int	check_client(int);
void	ls(int);
void	pwd(int);
void	cd(char *, char *, int);
char	**create_word_tab(char *);

#endif
