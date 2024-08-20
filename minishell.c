/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:08 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/20 04:28:09 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// t_env	*ft_lstl(t_env *token)
// {
// 	if (!token)
// 		return (NULL);
// 	while (token->next)
// 		token = token->next;
// 	return (token);
// }

// void	ft_lst_back(t_env **lst, t_env *new)
// {
// 	t_env	*last;

// 	if (!new)
// 		return ;
// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	last = ft_lstl(*lst);
// 	last->next = new;
// }
// t_env	*ft_lstn(char *a, char *b, int type)
// {
// 	t_env	*node;

// 	node = malloc(sizeof(t_env));
// 	if (!node)
// 		return (NULL);
// 	node->line = _malloc(sizeof(char *) * 3);
// 	node->line[0] = ft_strdup(a);
// 	node->line[1] = ft_strdup(b);
// 	node->line[2] = NULL;
// 	node->exp = type;
// 	node->next = NULL;
// 	return (node);
// }
void bash_routine(t_main *m)
{
	


	m->mini.line = add_space(m->mini.line);
	m->cmd = init_cmd(m);
	if (m->cmd)
		m->command = init_command(m->cmd);
	_bultin(m, m->command);
	//free(m->mini.line);
	//ft_lstclear_collec(&m->cmd, del_collec);
	
	free_cmd(m->cmd);
	free_comd(m->command);
}

int	main(int ac, char **av, char **env)
{
	t_main	*minish;
	// t_env *node;
	
	(void)ac;
	(void)av;
	minish = _initminish();
	// set_env(&minish->env, env);
	(void)env;
	// node = ft_lstn("SHLVL", "1", 0);
	// minish->env = ft_lstn("PWD", "tmp", 0);
	// ft_lst_back(&minish->env, node);
	// ft_lst_back(&minish->env, ft_lstn("dsad", "dhgjghj", 0));
	minish->env = set_envc(env);
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
		// minish->mini.line = NULL;
		while (minish->env)
		{
			printf("%d : %s=%s\n", minish->env->exp, minish->env->line[0], minish->env->line[1]);
			minish->env = minish->env->next;
		}
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
		////////////////////////
		// _execinit(command, cmd, &mini);
	}
	// free(minish->mini.line);
	// ft_lstclear_collec(&main_list->colec, del_collec);
	// int i = 0;
	// while (main_list->mini.env[i])
	// 	free(main_list->mini.env[i++]);
	
	// free(minish);
	

	_clearmini(minish);
	
	return (0);
}
