/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra  <kakra@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:40:40 by kakra             #+#    #+#             */
/*   Updated: 2024/11/15 19:40:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_option(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '-' && ft_strlen(arg) == 1)
		return (0);
	if (arg[0] == '"' || arg[0] == '\'')
	{
		if (arg[1] != '-')
			return (0);
		else
			i++;
	}
	else if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n' && arg[i] != '"' && arg[i] != '\'')
			return (0);
		i++;
		if (ft_strlen(arg) == i)
			return (1);
	}
	return (0);
}

bool	check_vara(t_command *cmd, t_echo *data)
{
	if (cmd->argv[data->i][data->j] == '\\'
		&& cmd->argv[data->i][data->j + 1] == '$')
	{
		data->j++;
		while (cmd->argv[data->i][data->j])
		{
			printf("%c", cmd->argv[data->i][data->j]);
			data->j++;
		}
		return (true);
	}
	return (false);
}

bool	check_char_after_var(t_command *cmd, t_echo *data, char next_char)
{
	if (cmd->argv[data->i][data->j] && cmd->argv[data->i][data->j] == next_char)
	{
		printf("%c", next_char);
		data->j++;
		return (true);
	}
	return (false);
}

void	echo_utils(t_command *cmd, t_echo *data, t_env *env)
{
	while (cmd->argv[data->i][data->j])
	{
		if (echo_pid(cmd, data, env) == true)
			continue ;
		if (echo_exit(cmd, data, env) == true)
			continue ;
		else if (check_quotation(cmd, data) == true)
			continue ;
		else if (check_more_quotation(cmd, data) == true)
			continue ;
		else if (check_vara(cmd, data))
			continue ;
		if (check_char_after_var(cmd, data, '%'))
			continue ;
		else
			printf("%c", cmd->argv[data->i][data->j]);
		data->j++;
	}
}

void	ft_echo(t_env *env, t_command *cmd)
{
	t_echo	data;

	data_init(&data);
	check_echo_n(cmd, &data);
	while (cmd->argv[data.i])
	{
		data.j = 0;
		echo_utils(cmd, &data, env);
		if (cmd->argv[data.i + 1])
			printf(" ");
		data.i++;
	}
	if (data.newline)
		printf("\n");
	env->exitcode = 0;
	exit(env->exitcode);
}
