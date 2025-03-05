/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkvar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:37:54 by kakra             #+#    #+#             */
/*   Updated: 2024/12/28 01:18:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exp(t_exp	*data)
{
	data->key = NULL;
	data->value = NULL;
	data->expanded_key = NULL;
	data->i = 1;
	data->check = false;
	data->exit = false;
}

void	data_init(t_echo *data)
{
	data->i = 1;
	data->j = 0;
	data->newline = true;
	data->in_double_quote = 0;
	data->in_single_quote = 0;
}

void	init_lst(t_var *data, t_command *cmd)
{
	data->arg = cmd->argv[data->i];
	data->new_arg = ft_strdup("");
	data->inside_single_quote = 0;
	data->inside_double_quote = 0;
	data->j = 0;
}

void	init_lex(t_lex *data)
{
	data->singlequote = false;
	data->doublequote = false;
	data->prev_token = 0;
	data->i = 0;
	data->status = true;
	data->export = false;
}

void	init_cmd(t_command *cmd)
{
	cmd->pipefd[0] = -1;
	cmd->pipefd[1] = -1;
	cmd->heredoc_fd[0] = -1;
	cmd->heredoc_fd[1] = -1;
	cmd->saved_stdin = dup(STDIN_FILENO);
}
