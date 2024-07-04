/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:03 by bamssaye          #+#    #+#             */
/*   Updated: 2024/06/25 11:07:16 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

// STRUCTURES

typedef struct _minishell
{
	char	*line;
	char	**env;

}			t_minishell;

// COLORS

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"
# define BOLD "\033[1m"

// FUNCTIONS COMMANDS BUILTINS
void		ft_pwd(void);
void		ft_cd(char *path);
void		print_env(char **env, int export);
void		ft_echo(t_list *cmd);
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
t_list		*init_cmd(t_minishell *mini);

// FUNCTIONS UTILS

void		*_malloc(size_t size);
int			d2_len(char **str);
void		ft_init(char **env, t_minishell *mini);
void		edit_old_pwd(size_t i, t_minishell *mini);
void		edit_pwd(size_t i, t_minishell *mini);
void		ft_init(char **env, t_minishell *mini);

// DEFINES TOKENS
# define CMD 0
# define OPR 1
# define PIPE 3
# define GREAT 4
# define LESS 5
# define HEREDOC 6
# define APPEND 7
# define DOLLAR 8

#endif