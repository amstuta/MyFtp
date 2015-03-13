/*
** client.h for client in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Sun Mar  8 19:10:14 2015 arthur
** Last update Fri Mar 13 16:21:06 2015 arthur
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# define LINE_SIZE	4096
# define DATA_PORT	43230

int	create_socket(char *, int);
void	prompt(char *);
int	check_cmd(char *);
char	*real_cmd(char *, int);
char	**clean_cmd(char *, int, char *);
char	*wtos(char **);
int	count_word(char *);
char	**fill_up_res(char **, char *, int, int);
char	**create_word_tab(char *);
void	exit_signal(int);
int	auth_to_server(int);
int	check_user(int);
void	close_exit(int);
int	new_server(char *);
void	end_transfer(int, int, int);
void	send_file(int, int, char **);
void	file_transfer(int, char **, char *);
void	print_files(int);
void	rec_ls(int, char *, char **);

#endif
