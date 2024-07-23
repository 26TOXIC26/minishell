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

char *getmyenv(t_minishell *mini, char *str)
{
    int i;

    i = 0;
    while (mini->env[i])
    {
        if (ft_strncmp(mini->env[i], str, ft_strlen(str)) == 0)
            return (mini->env[i] + ft_strlen(str)+1);
        i++;
    }
    return (NULL);
}

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

char **resize_tab(char **tab, char **tmp2_2, int i)
{
    int j;
    int k;
    char **tmp;

    j = 0;
    k = 0;
    while (tab[j])
        j++;
    tmp = _malloc(sizeof(char *) * (j + d2_len(tmp2_2) + 1));
    j = 0;
    while (tab[j])
    {
        if (j == i)
        {
            while (tmp2_2[k])
            {
                tmp[j] = ft_strdup(tmp2_2[k]);
                j++;
                k++;
            }
        }
        tmp[j] = ft_strdup(tab[j]);
        j++;
    }
    tmp[j] = NULL;
    free(tab);
    return (tmp);
}


void ft_dsymbol(char **tab, t_minishell *mini)
{
    // tab[0] = $Pwd tab[1] = $PWD
    char *tmp;
    char *tmp2;
    char **tmp2_2;
    int i;
    int j;

    i = 0;
    j = 1;
    while (tab[i])
    {
        while (tab[i][j - 1] && dstrchr(tab[i] + j - 1, '$'))
        {
            tmp2 = dstrchr(tab[i] + j - 1, '$');
            // if (tmp2 && tmp2[1] && tmp2[1] == '?')
            // {
            //     tmp = ft_substr(tab[i], 0, tmp2 - tab[i]);
            //     tmp = ft_strjoin(tmp, ft_itoa(mini->exit_status));
            //     free(tab[i]);
            //     tab[i] = tmp;
            // }
            if (tmp2 && (i == 0 || is_type(tab[i-1]) != HEREDOC))
            {
                while (tmp2 && tmp2[j] && (ft_isalnum(tmp2[j]) || tmp2[j] == '_'))
                    j++;
                tmp = ft_substr(tab[i], 0, tmp2 - tab[i]);
                if (getmyenv(mini ,ft_substr(tab[i], tmp2 - tab[i] + 1, j - 1)))
                    tmp = ft_strjoin(tmp, getmyenv(mini ,ft_substr(tab[i], tmp2 - tab[i] + 1, j - 1)));
                tmp = ft_strjoin(tmp, ft_substr(tab[i], tmp2 - tab[i] + j, ft_strlen(tab[i]) - j));
                printf("tmp = %s\n", tmp);
                if (tmp[0] == '\"')
                {
                    free(tab[i]);
                    tab[i] = tmp;
                }
                else
                {
                    tmp2_2 = ft_split(tmp);
                    tab = resize_tab(tab, tmp2_2, i);
                    free(tmp);
                }
            }
        }
        j = 1;
        i++;
    }
}
