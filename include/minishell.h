/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:03 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/24 01:07:05 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structures.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

///////////////////////////////////////////////////

////////////////////////// Parsing //////////////////////////

int			is_space(char *s);
int			chr_cmp(char c);
int			check_quote(t_minishell mini);
int			check_syntax2(t_minishell mini);
int			check_syntax(t_minishell mini);
t_list		*init_cmd(t_main *mini);
t_command	*init_command(t_list *list);
int			check_list(t_list *cmd);

/// Utils ///

int			is_type(char *str);
int			d2_len(char **str);
void		*_malloc(size_t size);
//void		edit_old_pwd(size_t i, t_minishell *mini);
//void		edit_pwd(size_t i, t_minishell *mini);
char		*add_space(char *line);
void		remove_quotes(t_list *cmd);
char		*remove_quotes2(char *str);
void		remove_quotes3(char *str, int *i, int *j, char *new_str);

////////////////////////// bult-in //////////////////////////

void		ft_pwd(void);
void		print_env(t_env *env);
void		ft_echo(char **str);
void		ft_unset(t_command *cmd, t_env **mini);
// int			find_env(char *str, t_minishell *mini);
//int			find_env(char *str, char **env);
// void		plus_shlvl(size_t i, t_minishell *mini);
///
char		**i_bultin(void);
// void		_bultin(t_main *mi);
void		ft_cd(t_main *cmnd);
char		*get_pwd(void);

/////
int			is_bltn(t_main *m, char *cmd);
void		_bultin(t_main *mi, t_command *cmd);
char		**ft_init(char **env);

/// EXPORT
void		ft_export(t_main *mi, t_command *cmd);
void		pexport_e(char *str);
int			ch_eq(char *str);
int			ch_exp(char *str, int f);

////////////////////////// Collect Address //////////////////////////

void		del_collec(void *value);
void		ft_lstdelone_collec(t_list *lst, void (*del)(void *));
void		ft_lstclear_collec(t_list **lst, void (*del)(void *));
int			ft_collectore(t_colec **data, void *ptr);

////////////////////////// expand //////////////////////////

char		**ft_expand(char **tab, t_main *mini);
void		expand_exit_s(char **tab, int i, t_main *mini, char *tmp2);

////////////////////////// Execution //////////////////////////

void		ft_exit(t_main *m, int exits);
//
void		open_rfile(int *_exit, t_redir *files);
int			_openfile(t_main *m, int r_type, char *fname);
void		_heredoc(t_main *m);
void		_execution(t_main *m, int *tin, int *tout, t_command **cmd);
void		_pipe(t_main *m, t_command *cmd);

////////////////////////// Singal //////////////////////////

void		sig_handler(int signo);
void		ig_signal(void);

////////////////////////// CLear Memory //////////////////////////

void		free_list(t_list *list);
void		free_command(t_command *cmd);
void		_clearmini(t_main *m, int f);
void		arry_c(char **str);
void		free_comd(t_command *cmd);
void		free_cmd(t_list *cmd);
void		free_env(t_env *cmd);
void		free_env(t_env *cmd);
int			ft_lstsizess(t_env *lst);
// void		 set_env(t_env **envs, char **env);
// void		set_env(t_minishell *m, char **env);
t_env		*set_envc(char **env);
void		print_exp(t_env *env);

////////////////////////// Main Utils //////////////////////////

t_main		*_initminish(char **env);
void		ft_empty_env(t_minishell *mini);
//////////////
void	ft_env_back(t_env **lst, t_env *new);
t_env	*creat_new_env(char *str, int exp);
int	ft_strchrs(const char *s, int c);
///
int	eq_pos(char *str);
int	ch_eq(char *str);
int	ch_exp(char *str, int f);
////
char	*ft_strdup2(const char *str, int limit);
void	update_env(char *str, t_main *m);
char	*get_env(char *str, t_env *env);
t_env *check_pwd(t_env *env, char *str);

////////////////
#endif