/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkvarutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 20:13:55 by kakra             #+#    #+#             */
/*   Updated: 2024/11/17 20:13:55 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*create_command(void)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->argv = NULL;
	new_cmd->input_files = NULL;
	new_cmd->output_files = NULL;
	new_cmd->next = NULL;
	new_cmd->heredoc_delimiter = NULL;
	new_cmd->command = 0;
	return (new_cmd);
}

char	*copy_substring(char *src, int start, int len)
{
	int		src_len;
	char	*var_name;

	src_len = ft_strlen(src);
	if (start > src_len)
		start = src_len;
	if (start + len > src_len)
		len = src_len - start;
	var_name = (char *)malloc(len + 1);
	if (var_name == NULL)
		return (NULL);
	ft_strncpy(var_name, src + start, len);
	var_name[len] = '\0';
	return (var_name);
}

char	*get_env_var_value(char *var_name, t_env *envp)
{
	while (envp)
	{
		if (ft_strncmp(envp->key, var_name, ft_strlen(var_name)) == 0
			&& ft_strlen(envp->key) == ft_strlen(var_name))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	return (ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "unset") == 0);
}

void	check_exist(t_command *cmd, int saved_stdout, t_env *envp)
{
	if (!cmd->argv || !cmd->argv[0])
	{
		dup2(saved_stdout, STDOUT_FILENO);
		envp->exitcode = 0;
		exit(envp->exitcode);
	}
}
