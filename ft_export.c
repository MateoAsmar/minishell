/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 04:31:38 by kakra             #+#    #+#             */
/*   Updated: 2024/12/28 21:05:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_env_variable(char *arg, char **key, char **value)
{
	char	*eq_sign;

	if (!arg)
	{
		*key = NULL;
		*value = NULL;
		return ;
	}
	eq_sign = ft_strchr(arg, '=');
	if (eq_sign)
	{
		*key = ft_strndup(arg, eq_sign - arg);
		*value = ft_strtrim(eq_sign + 1, " \t\n\r");
	}
	else
	{
		*key = ft_strtrim(arg, " \t\n\r");
		*value = NULL;
	}
	if (!*key || ft_strlen(*key) == 0)
	{
		free(*key);
		*key = NULL;
	}
}

void	export_welp_help(t_exp	data, t_env **env_list)
{
	if (data.check == false)
		set_env(env_list, data.expanded_key, data.final_value);
	else
	{
		set_env(env_list, data.expanded_key, data.tempo);
		free(data.tempo);
	}
}

void	int_value(t_exp	*dat)
{
	dat->final_value = ft_strndup(dat->value
			+ 1, ft_strlen(dat->value) - 2);
	dat->tempo = ft_strjoin("\\", dat->final_value);
	dat->check = true;
}

void	export_help(t_env **env_list, t_exp	dat, t_env *envp)
{
	dat.final_value = NULL;
	if (dat.value)
	{
		if (dat.value[0] == '\'' && dat.value[ft_strlen(dat.value) - 1] == '\''
			&& ft_strlen(dat.value) > 3)
		{
			int_value(&dat);
		}
		else if (dat.value[0] == '"'
			&& dat.value[ft_strlen(dat.value) - 1] == '"')
		{
			dat.temp = ft_strndup(dat.value + 1, ft_strlen(dat.value) - 2);
			dat.final_value = expand_variables_in_line(dat.temp, envp);
			free(dat.temp);
		}
		else
			dat.final_value = expand_variables_in_line(dat.value, envp);
		export_welp_help(dat, env_list);
		if (envp->empty == false)
			free(dat.final_value);
	}
	else
		set_env(env_list, dat.expanded_key, NULL);
	(*env_list)->exitcode = 0;
}

void	builtin_export(t_env **env_list, t_command *cmd, t_env *envp)
{
	t_exp	data;

	init_exp(&data);
	envp->empty = false;
	handle_display_sorted_env(env_list, cmd);
	while (cmd->argv[data.i])
	{
		clean_args(cmd->argv);
		parse_env_variable(cmd->argv[data.i], &data.key, &data.value);
		data.expanded_key = expand_variables_in_line(data.key, envp);
		if (!data.expanded_key || !is_valid_identifier(data.expanded_key))
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				cmd->argv[data.i]);
			data.exit = true;
		}
		else
			export_help(env_list, data, envp);
		free(data.key);
		free(data.value);
		free(data.expanded_key);
		data.i++;
	}
	if (data.exit == true)
		envp->exitcode = 1;
}
