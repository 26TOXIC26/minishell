/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redr_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 00:59:12 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/26 06:41:24 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

void check_redir(t_main *main)
{
    t_redir	*redir_tmp;
    t_command *cmd_tmp;
    // char **files;
    // int i;

    // cmd_tmp = main->command;
    // while (cmd_tmp)
    // {
    //     redir_tmp = cmd_tmp->redir;
    //     while (redir_tmp)
    //     {
    //         if (redir_tmp->type != HEREDOC && redir_tmp->file)
    //             i++;
    //         redir_tmp = redir_tmp->next;
    //     }
    //     files = _malloc(sizeof(char *) * (i + 1));
    //     i = 0;
    //     redir_tmp = cmd_tmp->redir;
    //     while (redir_tmp)
    //     {
    //         if (redir_tmp->type != HEREDOC && redir_tmp->file)
    //         {
    //             files[i] = ft_strdup(redir_tmp->file);
    //             i++;
    //         }
    //         redir_tmp = redir_tmp->next;
    //     }
    //     files[i] = NULL;
    //     i = 0;
    //     redir_tmp = cmd_tmp->redir;
    //     files = ft_expand(files, main, 1);
    //     while (redir_tmp)
    //     {
    //         if (redir_tmp->type != HEREDOC && redir_tmp->file)
    //         {
    //             if (!files[i])
    //                 redir_tmp->flag = 1;
    //             else
    //             {
    //                 free(redir_tmp->file);
    //                 redir_tmp->file = ft_strdup(files[i]);
    //             }
    //             redir_tmp->file = remove_quotes2(redir_tmp->file);
    //             i++;
    //         }
    //         redir_tmp = redir_tmp->next;
    //     }
    //     arry_c(files);
    //     cmd_tmp = cmd_tmp->next;
    // }
}
