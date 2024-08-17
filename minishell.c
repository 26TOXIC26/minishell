/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:08 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/17 21:52:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	ft_empty_env(t_minishell *mini, t_colec **colec)
{
	mini->env = _malloc(sizeof(char *) * 4);
	ft_collectore(colec, mini->env);
	mini->env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	mini->env[1] = ft_strdup("SHLVL=1");
	mini->env[2] = ft_strdup("_=/usr/bin/env");
	mini->env[3] = NULL;
	
}

t_main	*_initminish(void)
{
	t_main	*minish;

	minish = _malloc(sizeof(t_main));
	minish->cmd = NULL;
	minish->colec = NULL;
	minish->command = NULL;
	minish->exit_status = 0;
	minish->bultin = i_bultin();
	return (minish);
}
void _clearmini(t_main *m)
{
	int i;
	
	free(m->mini.line);
	i = 0;
	while (m->mini.env[i])
		free(m->mini.env[i++]);
	i = 0;
	while (m->bultin[i])
		free(m->bultin[i++]);
	free(m->bultin);
	ft_lstclear_collec(&m->colec, del_collec);
	free(m);
	exit(0);
}
int	main(int ac, char **av, char **env)
{
	t_main	*minish;
	
	(void)ac;
	(void)av;
	minish = _initminish();
	if (!env[0])
		ft_empty_env(&minish->mini, &minish->colec);
	else
	{
		ft_init(env, &minish->mini, minish->colec);
		plus_shlvl(find_env("SHLVL", &minish->mini), &minish->mini);
	}
	_set_env(&minish->mini, env, &minish->colec);
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		minish->mini.line = readline("MINIHELL $> ");
		if (!minish->mini.line)
		{
			printf("exit\n");
			break ;
		}
		if (minish->mini.line[0] != '\0')
		{
			add_history(minish->mini.line);
			if (check_syntax(minish->mini) == 1 && is_space(minish->mini.line))
			{
				minish->mini.line = add_space(minish->mini.line, minish->colec);
				minish->cmd = init_cmd(minish);
				if (minish->cmd)
					minish->command = init_command(minish->cmd, minish->colec);
				_bultin(minish);
				free(minish->mini.line);
				minish->mini.line = NULL;
			}
		}
		int k = 0;
		while (minish->command)
		{	
			printf("========================================\n");
			while (minish->command->options[k])
			{
				if (k == 0)
					printf("cmd = %s\n", minish->command->options[k]);
				else
					printf("arg = %s\n", minish->command->options[k]);
				k++;
			}
			while (minish->command->redir)
			{
				printf("redr = %d\n", minish->command->redir->type);
				printf("file = %s\n", minish->command->redir->file);
				minish->command->redir = minish->command->redir->next;
			}
			minish->command = minish->command->next;
			k = 0;
		}
		////////////////////////
		// _execinit(command, cmd, &mini);
	}
	// free(minish->mini.line);
	// ft_lstclear_collec(&main_list->colec, del_collec);
	// int i = 0;
	// while (main_list->mini.env[i])
	// 	free(main_list->mini.env[i++]);
	// ft_lstclear_collec(&main_list->colec, del_collec);
	
	// free(minish);
	_clearmini(minish);
	
	return (0);
}
