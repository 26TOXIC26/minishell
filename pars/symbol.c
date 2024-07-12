/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:13:41 by amousaid          #+#    #+#             */
/*   Updated: 2024/07/12 23:39:34 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void ft_dsymbol(char **tab)
{
    char *tmp;
    int i;

    i = 0;
    while (tab[i])
    {
        if (tab[i][0] == '$')
        {
            tmp = tab[i];
            if (getenv(tab[i] + 1) != NULL)
            {
                tab[i] = ft_strdup(getenv(tab[i] + 1));
                free(tmp);
            }
            else
            {
                tab[i] = ft_strdup("");
                free(tmp);
            }
        }
        i++;
    }  
}
