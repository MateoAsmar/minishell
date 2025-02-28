/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkvar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:37:54 by kakra             #+#    #+#             */
/*   Updated: 2024/12/29 03:11:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_help(t_command *cmd, t_env *envp, int saved_stdout)
{
	char	*temp;

	temp = remove_quotes(cmd->argv[0]);
	free(cmd->argv[0]);
	cmd->argv[0] = temp;
	cmd->path = accesspath(envp, cmd->argv[0], saved_stdout);
	if (!cmd->path)
	{
		envp->exitcode = 127;
		exit(envp->exitcode);
	}
}

void	var_helper(t_var *data, t_env *envp)
{
	if (data->arg[data->j] == '?')
		ec_help(data, envp);
	else
	{
		data->len = 0;
		while (data->arg[data->j + data->len] && (ft_isalnum(data->arg[data->j
						+ data->len]) || data->arg[data->j + data->len] == '_'))
			data->len++;
		if (data->len > 0)
		{
			data->var_name = ft_strndup(&data->arg[data->j], data->len);
			data->var_value = get_env_var_value(data->var_name, envp);
			free(data->var_name);
			if (data->var_value)
				data->new_arg = safe_strjoin(data->new_arg, data->var_value);
			data->j += data->len;
		}
		else
			data->new_arg = safe_strjoin(data->new_arg, "$");
	}
}

void	var_help(t_var *data, t_env *envp)
{
	if (data->arg[data->j] == '\'' && !data->inside_double_quote)
	{
		data->inside_single_quote = !data->inside_single_quote;
		data->new_arg = safe_strjoin(data->new_arg, "'");
		data->j++;
	}
	else if (data->arg[data->j] == '"' && !data->inside_single_quote)
	{
		data->inside_double_quote = !data->inside_double_quote;
		data->new_arg = safe_strjoin(data->new_arg, "\"");
		data->j++;
	}
	else if (data->arg[data->j] == '$' && !data->inside_single_quote)
	{
		data->j++;
		var_helper(data, envp);
	}
	else
	{
		data->temp[0] = data->arg[data->j];
		data->temp[1] = '\0';
		data->new_arg = safe_strjoin(data->new_arg, data->temp);
		data->j++;
	}
}

void	replace_env_variables(t_command *cmd, t_env *envp)
{
	t_var	data;

	while (cmd)
	{
		data.i = 0;
		while (cmd->argv && cmd->argv[data.i])
		{
			init_lst(&data, cmd);
			while (data.arg[data.j])
			{
				var_help(&data, envp);
			}
			free(cmd->argv[data.i]);
			cmd->argv[data.i] = data.new_arg;
			if (ft_strcmp(data.new_arg, "") == 0)
			{
				free(data.new_arg);
				cmd->argv[data.i] = "";
			}
			else
				cmd->argv[data.i] = data.new_arg;
			data.i++;
		}
		cmd = cmd->next;
	}
}
