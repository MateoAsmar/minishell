/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:19:25 by kakra             #+#    #+#             */
/*   Updated: 2024/12/28 19:46:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error1(char *parsecmd, t_env *a, int saved_stdout)
{
	dup2(saved_stdout, STDOUT_FILENO);
	if (ft_strcmp(parsecmd, "$?") == 0)
		printf("%d : command not found\n", a->exitcode);
	else
		printf("%s: command not found\n", parsecmd);
}

void	ft_path(t_env *a)
{
	t_env	*temp;
	int		check;

	check = 0;
	temp = a;
	while (!(ft_strnstr(temp->key, "PATH", 4)) && temp->next != NULL)
	{
		if (ft_strnstr(temp->key, "PATH", 4) == 0)
			check++;
		temp = temp->next;
	}
	a->paths = ft_split(temp->value, ':');
}

char	*accesspath(t_env *a, char *cmd, int saved_stdout)
{
	int		i;
	char	*path;
	char	*command;
	char	**parsecmd;

	ft_path(a);
	parsecmd = ft_split(cmd, ' ');
	i = 0;
	command = ft_strjoin("/", parsecmd[0]);
	while (a->paths[i])
	{
		path = ft_strjoin(a->paths[i], command);
		if (access(path, X_OK) == 0)
		{
			free(command);
			freearray(parsecmd);
			return (path);
		}
		free(path);
		i++;
	}
	print_error1(parsecmd[0], a, saved_stdout);
	freearray(parsecmd);
	free(command);
	return (NULL);
}

void	update_env_variable(t_env *envp, char *key, char *value)
{
	t_env	*var;

	var = find_env(envp, key);
	if (var)
	{
		free(var->value);
		var->value = strdup(value);
	}
	else
		set_env(&envp, key, value);
}

void	no_command(t_command *cmd, int saved_stdout,
		int saved_stdin, t_env *envp)
{
	int	heredoc_fd[2];

	if (cmd->input_files != NULL)
		no_command_input(cmd, saved_stdout, envp);
	else if (cmd->heredoc_delimiter != NULL)
	{
		handle_heredoc(cmd->heredoc_delimiter, envp, heredoc_fd);
		dup2(heredoc_fd[0], STDIN_FILENO);
		close(heredoc_fd[0]);
		close(heredoc_fd[1]);
	}
	dup2(saved_stdin, STDIN_FILENO);
	if (cmd->argv == NULL && cmd->output_files != NULL)
	{
		saved_stdout = dup(STDOUT_FILENO);
		redirect_output(cmd->output_files);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}
