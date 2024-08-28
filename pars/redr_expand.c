/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redr_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 00:59:12 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/28 06:20:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

char *her_expand (char *str, t_main *m)
{
    char *result;
    t_expand e;

    result = ft_strdup(str);
    e.j = 0;
    e.i = 0;
    e.last_c = result;
    while (e.last_c[e.j] && ft_strchr(e.last_c, '$'))
    {
        e.e_str = ft_strchr(e.last_c, '$');
        e.j++;
        if (e.e_str[e.j] && e.e_str[e.j] == '?')
        {
            expand_exit_s(&result, m, &e);
            continue;
        }
        e.result = ft_substr(result, 0, e.e_str - result);
        while (e.e_str[e.j] && (ft_isalnum(e.e_str[e.j]) || e.e_str[e.j] == '_') && !ft_isdigit(e.e_str[1]))
            e.j++;
        e.complet = &e.e_str[e.j];
        e.e_str = ft_substr(e.e_str + 1, 0, e.j - 1);
        // if (getmyenv(m->env, e.e_str))

    }

    return (result);
}
