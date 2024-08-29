/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:08 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/30 00:28:27 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_main	*minish;

	(void)ac;
	(void)av;
	minish = _initminish(env);
	while (1)
	{
		ig_signal();
		minish->mini.line = readline(GREEN"MINIHELL $> "RESET);
		if (!minish->mini.line)
		{
			printf("exit\n");
			break ;
		}
		add_history(minish->mini.line);
		if (is_space(minish->mini.line)
			&& check_syntax(minish->mini, minish) == 1)
			bash_routine(minish);
		free(minish->mini.line);
	}
	_clearmini(minish, 0);
	return (0);
}
