/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelilah <abdelilah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:13:41 by amousaid          #+#    #+#             */
/*   Updated: 2024/07/16 04:48:53 by abdelilah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

char *dstrchr(char *s, char c)
{
    static int quote;
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == '\"')
        {
            quote = 1;
            i++;
            while (s[i] && s[i] != '\"')
            {
                if (s[i] == c && s[i+1] && s[i+1] != c && s[i+1] != '\"')
                    return (s + i);
                i++;
            }
            quote = 0;
        }
        else if (s[i] == '\'' && !quote)
        {
            i++;
            while (s[i] && s[i] != '\'')
                i++;
            i++;
        }
        else if (s[i] == c && s[i+1] && (ft_isalnum(s[i+1]) || s[i+1] == '_'))
            return (s + i);
        i++;
    }
    quote = 0;
    return (NULL);
}

void ft_dsymbol(char **tab, t_minishell *mini)
{
    // tab[0] = $Pwd tab[1] = $PWD
    char *tmp;
    char *tmp2;
    int i;
    int j;

    i = 0;
    j = 1;
    while (tab[i])
    {
        // tmp2 = dstrchr(tab[i], '$');
        while (tab[i][j - 1] && dstrchr(tab[i] + j - 1, '$'))
        {
            tmp2 = dstrchr(tab[i] + j - 1, '$');
            if (tmp2 && tmp2[1] && tmp2[1] == '?')
            {
                tmp = ft_substr(tab[i], 0, tmp2 - tab[i]);
                tmp = ft_strjoin(tmp, ft_itoa(mini->exit_status));
                free(tab[i]);
                tab[i] = tmp;
            }
            else if (tmp2 && (i == 0 || is_type(tab[i-1]) != HEREDOC))
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
        }
        j = 1;
        i++;
    }
}