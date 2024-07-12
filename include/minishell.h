/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:03 by bamssaye          #+#    #+#             */
/*   Updated: 2024/07/12 23:18:38 by amousaid         ###   ########.fr       */
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

typedef struct _redir
{
	int		type;
	char	*file;
	struct _redir	*next;
}			t_redir;

typedef struct _command
{
	t_redir		*redir;
	char		**options;
	struct _command	*next;
}			t_command;

typedef struct _flist
{
	t_command	*cmd;
	int exit_status;
}		f_list;

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
t_command	*init_command(t_list *list);
int			check_list(t_list *cmd);

// FUNCTIONS UTILS

void		*_malloc(size_t size);
int			d2_len(char **str);
void		ft_init(char **env, t_minishell *mini);
void		edit_old_pwd(size_t i, t_minishell *mini);
void		edit_pwd(size_t i, t_minishell *mini);
void		ft_init(char **env, t_minishell *mini);
void 		free_list(t_list *list);
void 		free_command(t_command *cmd);
void 		sig_handler(int signo);
void 		ft_dsymbol(char **tab);

// DEFINES TOKENS
# define STR 0
# define PIPE 1
# define OUT 2
# define IN 3
# define APPEND 4
# define HEREDOC 5
# define FILE 6

#endif