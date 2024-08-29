/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:16:50 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/28 23:56:38 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

// DEFINES TOKENS
# define STR 0
# define PIPE 1
# define OUT 2
# define IN 3
# define APPEND 4
# define HEREDOC 5
# define RFILE 6
# define EMSG "MINIHELL: syntax error near unexpected token `"

typedef struct _colectore
{
	void				*ptr;
	struct _colectore	*next;

}						t_colec;

////////
typedef struct _env
{
	char				*line[2];
	int					index;
	int					exp;
	struct _env			*next;
}						t_env;

typedef struct _minishell
{
	char				*line;
	char				**env;
	t_env				*envs;
	int					exit_status;
}						t_minishell;

typedef struct _redir
{
	int					type;
	char				*file;
	int					flag;
	char				h_n[10];
	struct _redir		*next;
}						t_redir;

typedef struct _command
{
	t_redir				*redir;
	char				**options;
	struct _command		*next;
}						t_command;

typedef struct _main
{
	t_command			*command;
	char				**bultin;
	char				**paths;
	t_minishell			mini;
	t_env				*env;
	t_list				*cmd;
	int					pipe_fd[2];
	int					exit_status;
}						t_main;

typedef struct _expand
{
	char				**s_tab;
	char				*complet;
	char				*e_str;
	char				*result;
	char				*last_c;
	int					i;
	int					j;
	int					flag;
	int					len;
}						t_expand;

#endif
