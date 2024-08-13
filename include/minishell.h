/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:03 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/13 16:31:06 by amousaid         ###   ########.fr       */
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

// FUNCTIONS COMMANDS BUILTINS
void		ft_pwd(void);
// void		ft_cd(char *path);
void		print_env(char **env, int expor);
void		ft_echo(char **str);
void		ft_unset(t_list *cmd, t_minishell *mini);
void		ft_export(t_list *cmd, t_minishell *mini, t_colec *colec);
// void		_bultin(t_main *mi);

// FUNCTIONS ENV
int			find_env(char *str, t_minishell *mini);
void		plus_shlvl(size_t i, t_minishell *mini);

// FUNCTIONS PARS

int			is_space(char *s);
int			chr_cmp(char c);
int			check_quote(t_minishell mini);
int			check_syntax2(t_minishell mini);
int			check_syntax(t_minishell mini);
t_list		*init_cmd(t_main *mini);
t_command	*init_command(t_list *list, t_colec *colec);
int			check_list(t_list *cmd);

// FUNCTIONS UTILS

int			is_type(char *str);
int			d2_len(char **str);
void		*_malloc(size_t size);
void		ft_init(char **env, t_minishell *mini, t_colec *col);
void		edit_old_pwd(size_t i, t_minishell *mini);
void		edit_pwd(size_t i, t_minishell *mini);
void		free_list(t_list *list);
void		free_command(t_command *cmd);
void		sig_handler(int signo);
char		**ft_expand(char **tab, t_main *mini, t_colec *colec);
void		expand_exit_s(char **tab, int i, t_main *mini, char *tmp2);
char		*add_space(char *line, t_colec *colec);
void		remove_quotes(t_list *cmd, t_colec *colec);
char		*remove_quotes2(char *str, t_colec *colec);
void		remove_quotes3(char *str, int *i, int *j, char *new_str);

/// Collectore
void		del_collec(void *value);
void		ft_lstdelone_collec(t_colec *lst, void (*del)(void *));
void		ft_lstclear_collec(t_colec **lst, void (*del)(void *));
int			ft_collectore(t_colec **data, void *ptr);
// ME
void		_set_env(t_minishell *m, char **env, t_colec **col);
char		**i_bultin(void);
void		ft_exit(t_main *m);
void		_bultin(t_main *mi);
char		*get_pwd(void);
void		ft_cd(t_main *cmnd);
void		_clearmini(t_main *m);

#endif