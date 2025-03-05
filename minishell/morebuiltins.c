/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   morebuiltins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:14:07 by kakra             #+#    #+#             */
/*   Updated: 2025/01/01 23:25:12 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_util(int i, t_env **env_list, t_command *cmd)
{
	t_env	*current;
	t_env	*prev;

	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, cmd->argv[i]) == 0)
		{
			if (prev == NULL)
				*env_list = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

void	builtin_unset(t_env **env_list, t_command *cmd)
{
	int		i;

	if (!cmd->argv[1])
		return ;
	i = 1;
	while (cmd->argv[i])
	{
		unset_util(i, env_list, cmd);
		i++;
	}
}

void	ft_export(t_env **env_list, t_command *cmd, t_env *envp)
{
	if (strcmp(cmd->argv[0], "export") == 0)
	{
		builtin_export(env_list, cmd, envp);
		flag_env(*env_list);
	}
}

char	*expand_help(char *expanded_line, t_env *envp, char *line)
{
	char	*var_value;
	char	*var_name;

	envp->i++;
	if (line[envp->i] == '?')
	{
		var_value = ft_itoa(envp->exitcode);
		expanded_line = safe_strjoin(expanded_line, var_value);
		free(var_value);
		envp->i++;
	}
	else
	{
		var_name = extract_var_name(line, &envp->i);
		if (var_name)
		{
			var_value = get_env_value(var_name, envp);
			free(var_name);
			if (var_value)
				expanded_line = safe_strjoin(expanded_line, var_value);
			else
				expanded_line = safe_strjoin(expanded_line, "");
		}
	}
	return (expanded_line);
}

void	update_shlvl(t_env *env)
{
	t_env	*current;
	char	*shlvl_str;
	int		shlvl;

	current = env;
	while (current)
	{
		if (strcmp(current->key, "SHLVL") == 0)
		{
			shlvl_str = current->value;
			shlvl = ft_atoi(shlvl_str);
			shlvl++;
			free(current->value);
			current->value = ft_itoa(shlvl);
			return ;
		}
		current = current->next;
	}
}
