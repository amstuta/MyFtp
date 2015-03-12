/*
** client.h for client in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Sun Mar  8 19:10:14 2015 arthur
** Last update Thu Mar 12 17:15:50 2015 arthur
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# define LINE_SIZE 4096

int	create_socket(char *, int);
void	prompt();
int	check_cmd(char *);
char	*real_cmd(char *, int);
char	**clean_cmd(char *, int);
char	*wtos(char **);
int	count_word(char *);
char	**fill_up_res(char **, char *, int, int);
char	**create_word_tab(char *);
void	exit_signal(int);
int	auth_to_server();
void	close_exit(int);

#endif
