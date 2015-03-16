/*
** server.h for server in /home/amstuta/rendu/PSU_2014_myftp
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Sun Mar  8 18:47:04 2015 arthur
** Last update Mon Mar 16 14:22:09 2015 arthur
*/

#ifndef SERVER_H_
# define SERVER_H_

# define ERROR		"666"
# define LINE_SIZE	4096

extern int		g_fd;
extern int		g_dfd;

void			read_cmd(char *);
void			accept_client(int, int, int);
void			create_socket(int);
void			fork_proc();
void			execute_cmd(char *, char **, char *);
void			clean_cmd(char *, char *);
int			check_cmd(char *);
int			check_client();
void			ls();
int			send_ls(char *);
void			pwd();
void			cd(char *, char *);
char			*check_cd(char *, char *);
char			**create_word_tab(char *);
void			close_client();
void			send_file(char *);
void			end_transfer(int, int);
int			new_socket(int);
int			accept_new_client();
void			receive_file(char *);
void			exit_signal(int);

#endif
