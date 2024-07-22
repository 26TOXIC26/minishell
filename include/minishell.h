/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:03 by bamssaye          #+#    #+#             */
/*   Updated: 2024/07/21 14:18:07 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include "structures.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

// FUNCTIONS COMMANDS BUILTINS
void		ft_pwd(void);
void		ft_cd(char *path);
void		print_env(char **env, int export);
void		ft_echo(char **str);
void		ft_unset(t_list *cmd, t_minishell *mini);
void		ft_export(t_list *cmd, t_minishell *mini);

// FUNCTIONS ENV
int			find_env(char *str, t_minishell *mini);
void		plus_shlvl(size_t i, t_minishell *mini);

// FUNCTIONS PARS

int			is_space(char *s);
int			chr_cmp(char c);
int			check_quote(t_minishell mini);
int			check_syntax2(t_minishell mini);
int			check_syntax(t_minishell mini);
char		*add_space(char *line);
t_list		*init_cmd(f_list *mini);
t_command	*init_command(t_list *list);
int			check_list(t_list *cmd);

// FUNCTIONS UTILS

int 		is_type(char *str);
int			d2_len(char **str);
void		*_malloc(size_t size);
void		ft_init(char **env, t_minishell *mini);
void		edit_old_pwd(size_t i, t_minishell *mini);
void		edit_pwd(size_t i, t_minishell *mini);
void		ft_init(char **env, t_minishell *mini);
void 		free_list(t_list *list);
void 		free_command(t_command *cmd);
void 		sig_handler(int signo);
void 		ft_dsymbol(char **tab, t_minishell *mini);



#endif