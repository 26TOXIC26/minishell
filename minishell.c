/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:08 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/25 23:43:33 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void bash_routine(t_main *m)
{
	m->mini.line = add_space(m->mini.line);
	m->cmd = init_cmd(m);
	if (m->cmd)
		m->command = init_command(m->cmd);
	//_bultin(m, m->command);
	_execinit(m);
	//free(m->mini.line);
	//ft_lstclear_collec(&m->cmd, del_collec);
	
	free_cmd(m->cmd);
	free_comd(m->command);
}

int	main(int ac, char **av, char **env)
{
	t_main	*minish;
	
	(void)ac;
	(void)av;
	minish = _initminish(env);
	while (1)
	{
		ig_signal();
		minish->mini.line = readline("MINIHELL $> ");
		if (!minish->mini.line)
		{
			printf("exit\n");
			break ;
		}
		add_history(minish->mini.line);
		if (is_space(minish->mini.line) && check_syntax(minish->mini) == 1)
			bash_routine(minish);
		free(minish->mini.line);
		// while (minish->env)
		// {
		// 	printf("%d : %s=%s\n", minish->env->exp, minish->env->line[0], minish->env->line[1]);
		// 	minish->env = minish->env->next;
		// }
		// if (minish->mini.line[0] != '\0')
		// {
		// 	add_history(minish->mini.line);
		// 	if (check_syntax(minish->mini) == 1 && is_space(minish->mini.line))
		// 	{
		// 		minish->mini.line = add_space(minish->mini.line, minish->colec);
		// 		minish->cmd = init_cmd(minish);
		// 		if (minish->cmd)
		// 			minish->command = init_command(minish->cmd, minish->colec);
		// 		// _bultin(minish);
		// 		free(minish->mini.line);
		// 		minish->mini.line = NULL;
		// 	}
		// }
		// int k = 0;
		// while (minish->command)
		// {	
		// 	printf("========================================\n");
		// 	while (minish->command->options[k])
		// 	{
		// 		if (k == 0)
		// 			printf("cmd = %s\n", minish->command->options[k]);
		// 		else
		// 			printf("arg = %s\n", minish->command->options[k]);
		// 		k++;
		// 	}
		// 	minish->command = minish->command->next;
		// }
		// 	while (minish->command->redir)
		// 	{
		// 		printf("redr = %d\n", minish->command->redir->type);
		// 		printf("file = %s\n", minish->command->redir->file);
		// 		minish->command->redir = minish->command->redir->next;
		// 	}
		// 	minish->command = minish->command->next;
		// 	k = 0;
		// }
	}
	_clearmini(minish, 0);
	return (0);
}
