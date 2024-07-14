/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:13:41 by amousaid          #+#    #+#             */
/*   Updated: 2024/07/14 01:46:50 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void ft_dsymbol(char **tab)
{
    char *tmp;
    int i;
    int j;

    i = 0;
    j = 1;
    while (tab[i])
    {
        if (ft_strchr(tab[i], '$') && i > 0 && is_type(tab[i-1]) != HEREDOC)
        {
            while (tab[i][j] && ((tab[i][j] >= 48 && tab[i][j] <= 57) || (tab[i][j] >= 65 && tab[i][j] <= 90) || (tab[i][j] >= 97 && tab[i][j] <= 122)))
                j++;
            if (tab[i][j] == '\0')
            {
                tmp = tab[i];
                if (getenv(tab[i] + 1) != NULL)
                {
                    tab[i] = ft_strdup(getenv(tab[i] + 1));
                    free(tmp);
                }
            }
            else
            {
                tmp = ft_substr(tab[i], 1, j - 1);
                if (getenv(tmp) != NULL)
                {
                    tmp = ft_strjoin(getenv(tmp), tab[i] + j);
                    free(tab[i]);
                    tab[i] = tmp;
                }
            }
        }
        j = 1;
        i++;
    }  
}
