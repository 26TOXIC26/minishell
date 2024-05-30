/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelilah <abdelilah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:03 by bamssaye          #+#    #+#             */
/*   Updated: 2024/05/30 06:23:30 by abdelilah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>      
#include <signal.h>     
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>    
#include <errno.h>    
#include <termios.h>
#include <curses.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
 #include <sys/types.h>
#include <sys/wait.h>

typedef struct _token
{
   
} t_token;

typedef struct _minishell
{
    char *line;
    char **env;
    
} t_minishell;

//COLORS

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"
# define BOLD "\033[1m"

//FUNCTIONS COMMANDS BUILDINS
void ft_pwd(void);
void ft_cd(char *path);
void print_env(t_minishell *mini);

//FUNCTIONS ENV
size_t find_env(char *str, t_minishell *mini);
void plus_shlvl(size_t i, t_minishell *mini);

# endif