/*
** server.h for server in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Sun Mar  8 18:47:04 2015 arthur
** Last update Sat Mar 14 12:47:07 2015 arthur
*/

#ifndef SERVER_H_
# define SERVER_H_

# define ERROR		"666"
# define LINE_SIZE	4096

extern int	g_port;

void	read_cmd(int, char *);
void	accept_client(int, int);
void	create_socket(int);
void	execute_cmd(char *, char **, int, char *);
void	clean_cmd(char *, int, char *);
int	check_cmd(char *);
int	check_client(int);
void	ls(int);
int	send_ls(int, char *);
void	pwd(int);
void	cd(char *, char *, int);
char	*check_cd(char *, char *);
char	**create_word_tab(char *);
void	close_client(int);
void	send_file(int, char *);
void	end_transfer(int, int, int);
int	new_socket(int);
int	get_new_port();
int	accept_new_client(int, int);
void	receive_file(int, char *);

#endif
