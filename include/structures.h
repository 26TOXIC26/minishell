/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:16:50 by bamssaye          #+#    #+#             */
/*   Updated: 2024/07/21 14:26:56 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef STRUCTURES_H
# define STRUCTURES_H


// DEFINES TOKENS
# define STR 0
# define PIPE 1
# define OUT 2
# define IN 3
# define APPEND 4
# define HEREDOC 5
# define FILE 6

///// g_collector /////
typedef struct _colectore
{

void *ptr;
struct _colectore *next;

} t_colec;

////////

typedef struct _minishell
{
	char	*line;
	char	**env;
	int 	exit_status;
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

typedef struct golobal
{
    t_colec *colec;
    t_redir *redir;
    t_command *cmd;
    f_list *flist;
    t_minishell *minishell;
} t_global;

#endif