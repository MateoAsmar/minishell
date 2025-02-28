/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echoutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra  <kakra@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:29:55 by kakra             #+#    #+#             */
/*   Updated: 2024/11/15 20:29:55 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	echo_pid(t_command *cmd, t_echo *data, t_env *env)
{
	if (cmd->argv[data->i][data->j] == '$'
		&& cmd->argv[data->i][data->j + 1] == '$')
	{
		printf("%d", env->pid);
		data->j += 2;
		return (true);
	}
	return (false);
}

bool	echo_exit(t_command *cmd, t_echo *data, t_env *env)
{
	if (cmd->argv[data->i][data->j] == '$'
		&& cmd->argv[data->i][data->j + 1] == '?')
	{
		if (g_last_exit_code != 0)
			env->exitcode = g_last_exit_code;
		printf("%d", env->exitcode);
		data->j += 2;
		return (true);
	}
	return (false);
}

bool	check_quotation(t_command *cmd, t_echo *data)
{
	if (cmd->argv[data->i][data->j] == '\''
		&& !data->in_double_quote)
	{
		data->in_single_quote = !data->in_single_quote;
		data->j++;
		return (true);
	}
	return (false);
}

bool	check_more_quotation(t_command *cmd, t_echo *data)
{
	if (cmd->argv[data->i][data->j] == '"'
		&& !data->in_single_quote)
	{
		data->in_double_quote = !data->in_double_quote;
		data->j++;
		return (true);
	}
	return (false);
}

void	check_echo_n(t_command *cmd, t_echo *data)
{
	while (cmd->argv[data->i] && is_n_option(cmd->argv[data->i]))
	{
		data->newline = 0;
		data->i++;
	}
}
