/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:08 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/06 09:22:17 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	ft_empty_env(t_minishell *mini, t_colec *colec)
{
	mini->env = _malloc(sizeof(char *) * 4);
	ft_collectore(&colec, mini->env);
	mini->env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	mini->env[1] = ft_strdup("SHLVL=1");
	mini->env[2] = ft_strdup("_=/usr/bin/env");
	mini->env[3] = NULL;
}

f_list	*init_main_list(void)
{
	f_list	*main_list;

	main_list = _malloc(sizeof(f_list));
	main_list->cmd = NULL;
	main_list->colec = NULL;
	main_list->command = NULL;
	main_list->exit_status = 0;
	return (main_list);
}

int	main(int ac, char **av, char **env)
{
	f_list	*main_list;

	(void)ac;
	(void)av;
	main_list = init_main_list();
	if (!env[0])
		ft_empty_env(&main_list->mini, main_list->colec);
	else
	{
		ft_init(env, &main_list->mini, main_list->colec);
		plus_shlvl(find_env("SHLVL", &main_list->mini), &main_list->mini);
	}
	while (1)
	{
		// signal(SIGINT, sig_handler);
		// signal(SIGQUIT, SIG_IGN);
		main_list->mini.line = readline("MINIHELL $> ");
		if (!main_list->mini.line)
		{
			printf("exit\n");
			break ;
		}
		if (main_list->mini.line[0] != '\0' && is_space(main_list->mini.line))
		{
			add_history(main_list->mini.line);
			if (check_syntax(main_list->mini) == 1)
			{
				main_list->mini.line = add_space(main_list->mini.line, main_list->colec);
				main_list->cmd = init_cmd(main_list);
				if (main_list->cmd)
					main_list->command = init_command(main_list->cmd, main_list->colec);
				free(main_list->mini.line);
				main_list->mini.line = NULL;
			}
			// void	_bultin(main_list);
		}
		// int k = 0;
		// while (main_list->command)
		// {
		// 	printf("========================================\n");
		// 	while (main_list->command->options[k])
		// 	{
		// 		if (k == 0)
		// 			printf("cmd = %s\n", main_list->command->options[k]);
		// 		else
		// 			printf("arg = %s\n", main_list->command->options[k]);
		// 		k++;
		// 	}
		// 	while (main_list->command->redir)
		// 	{
		// 		printf("redr = %d\n", main_list->command->redir->type);
		// 		printf("file = %s\n", main_list->command->redir->file);
		// 		main_list->command->redir = main_list->command->redir->next;
		// 	}
		// 	main_list->command = main_list->command->next;
		// 	k = 0;
		// }
		////////////////////////
		// _execinit(command, cmd, &mini);
	}
	free(main_list->mini.line);
	// ft_lstclear_collec(&main_list->colec, del_collec);
	
	
	return (0);
}
