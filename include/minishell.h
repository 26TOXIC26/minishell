/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:03 by bamssaye          #+#    #+#             */
/*   Updated: 2024/09/05 04:20:25 by amousaid         ###   ########.fr       */
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
int			check_quote(t_minishell mini, t_main *m);
int			check_syntax2(t_minishell mini, t_main *m);
int			check_syntax(t_minishell mini, t_main *m);
t_list		*init_cmd(t_main *mini);
t_command	*init_command(t_list *list, t_main *mini);
int			check_list(t_list *cmd, t_main *m);
int			count_her(t_list *cmd);
int			psyntax_error(char *msg);
/// Utils ///
int			is_type(char *str);
int			d2_len(char **str);
void		*_malloc(size_t size);
char		*add_space(char *line);
void		remove_quotes(t_list *cmd);
char		*remove_quotes2(char *str);
void		remove_quotes3(char *str, int *i, int *j, char *new_str);
int			check_space(char *s);
int			dstrchr2(char *s, char c, int *i);
////////////////////////// bult-in //////////////////////////
void		ft_pwd(int *ex, t_env *env);
void		print_env(t_env *env, int *ex);
void		ft_echo(char **str, int *ex);
void		ft_unset(t_command *cmd, t_env **mini, int *ex);
char		**i_bultin(void);
void		ft_cd(t_main *m, t_command *cmd);
char		*get_pwd(void);
int			is_bltn(t_main *m, char *cmd);
void		_bultin(t_main *mi, t_command *cmd);
void		ft_export(t_main *mi, t_command *cmd);
// SET ENV
void		ft_env_back(t_env **lst, t_env *new);
t_env		*creat_new_env(char *str, int exp, char c);
void		update_env(char *str, t_main *m);
void		sort_env(t_env *env);
////////////////////////// expand //////////////////////////
char		**ft_expand(char **tab, t_main *min);
int			expand_exit_s(char **tab, t_main *mini, t_expand *e);
int			check_quote1(char *str);
char		*strjoing_f1(char *s1, char *s2);
int			do_flag(t_expand *e, char ***tab);
char		**resize_tab(char **tab, char **tmp2_2, int i);
int			do_expand(t_expand *e, char ***tab, t_main *mini);
char		*getmyenv(t_env *env, char *str);
int			in_quotes(char *str, int i, char c);
char		*dstrchr(char *s, char c, int *flag);
char		*her_expand(char *str, t_main *m);
char		*redir_expand(char *file, t_main *m, int *flag);
////////////////////////// Execution //////////////////////////
void		ft_exit(t_main *m, int exits, t_command *cmd);
void		open_rfile(t_main *m, t_redir *files);
int			_openfile(t_main *m, int r_type, char *fname, int flag);
int			_heredoc(t_main *m);
void		_creatfile_n(t_redir *file, int *n);
void		_execution(t_main *m, int *tin, int *tout, t_command **cmd);
void		_pipe(t_main *m, t_command *cmd);
void		exec_check(t_main *m, char *path, char **cmd, char **env);
void		path_check(t_main *m, char *fpath, char *cmd);
////////////////////////// Singal //////////////////////////
void		sig_handler(int signo);
void		ig_signal(t_main *m, int i);
void		setup_signals(void);

////////////////////////// CLear Memory //////////////////////////
void		free_list(t_list *list);
void		free_command(t_command *cmd);
void		_clearmini(t_main *m, int f);
void		arry_c(char **str);
void		free_comd(t_command *cmd);
void		free_cmd(t_list *cmd);
void		free_env(t_env *cmd);
int			size_env(t_env *lst);
t_env		*set_envc(char **env);
void		print_exp(t_env *env);
////////////////////////// Main Utils //////////////////////////
t_main		*_initminish(char **env);
void		bash_routine(t_main *m);
char		*strdup_limit(const char *str, int limit);
////////////////
char		*check_path(char *cmd, char **paths);
char		**get_path(t_main *m);
void		_execinit(t_main *m);
char		**exec_env(t_main *m);
int			_openfile_hd(t_main *m, int f, char *fname);
//////SIGNAL
void		sig_i_herdoc(int sig);
void		sig_parent(int sig);
void		sig_child(void);
void		sig_herdoc(void);
void		sig_ignor(void);
///////////////
t_env		*find_env_node(t_env *env, char *str);
char		*find_env_str(char *str, t_env *env);
int			find_equ_pluse(char *str, char c);
int			find_char_index(char *str, char c);
int			get_index_char(const char *s, int c);
int			open_rfile_bu(t_main *m, t_redir *files);
int			pexport_e(char *str);

#endif
