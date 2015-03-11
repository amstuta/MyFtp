/*
** client.h for client in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Sun Mar  8 19:10:14 2015 arthur
** Last update Wed Mar 11 14:48:32 2015 arthur
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# define LINE_SIZE 4096

int	create_socket(char *, int);
void	prompt(int);
int	check_cmd(char *);
char	*real_cmd(char *);
char	**clean_cmd(char *);
int	get_count(char *);
void	fill_tab(char ***, char *);
char	**split_args(char *);
char	*wtos(char **);

#endif
