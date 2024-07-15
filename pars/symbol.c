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
    char *tmp2;
    int i;
    int j;

    i = 0;
    j = 1;
    tmp2 = ft_strchr(tab[i], '$');
    while (tab[i])
    {
        tmp2 = ft_strchr(tab[i], '$');
        if (tmp2 && (i == 0 || is_type(tab[i-1]) != HEREDOC))
        {
            while (tmp2 && tmp2[j] && (ft_isalnum(tmp2[j]) || tmp2[j] == '_'))
                j++;
            tmp = ft_substr(tab[i], 0, tmp2 - tab[i]);
            if (getenv(ft_substr(tab[i], tmp2 - tab[i] + 1, j - 1)))
                tmp = ft_strjoin(tmp, getenv(ft_substr(tab[i], tmp2 - tab[i] + 1, j - 1)));
            tmp = ft_strjoin(tmp, ft_substr(tab[i], tmp2 - tab[i] + j, ft_strlen(tab[i]) - j));
            free(tab[i]);
            tab[i] = tmp;
        }
        j = 1;
        i++;
    }  
}
