/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:03:07 by kakra             #+#    #+#             */
/*   Updated: 2024/11/16 20:03:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_help(char *temp, t_command *cmd, t_env *envp)
{
	if (temp)
		cd_helper (cmd, envp);
	else
		cd_helper1 (cmd, envp);
}

bool	check_syntax_error_after_redirection(char *input, int i, t_env *envp)
{
	while (input[i] && ft_isspace(input[i]))
		i++;
	if (input[i] == '|')
	{
		printf("Syntax error: unexpected token `|`\n");
		envp->exitcode = 2;
		return (false);
	}
	return (true);
}

bool	lexer_error(t_lex *data, t_env *envp)
{
	if (data->prev_token == '|' || data->prev_token == '<'
		|| data->prev_token == '>')
	{
		printf("Syntax error: unexpected end of input\n");
		envp->exitcode = 2;
		data->check = true;
		return (false);
	}
	return (true);
}

void	no_command_input(t_command *cmd, int saved_stdout, t_env *envp)
{
	t_input_file	*current_input;
	int				input_fd;

	current_input = cmd->input_files;
	while (current_input)
	{
		input_fd = open(current_input->filename, O_RDONLY);
		if (input_fd < 0)
		{
			printf("%s: %s\n", current_input->filename, strerror(errno));
			envp->exitcode = 1;
			dup2(saved_stdout, STDIN_FILENO);
			break ;
		}
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
		current_input = current_input->next;
	}
}

void	path(t_command *cmd, t_env *envp, int saved_stdout)
{
	if (cmd->argv[0][0] == '/'
		|| (cmd->argv[0][0] == '.' && cmd->argv[0][1] == '/'))
	{
		cmd->path = cmd->argv[0];
		if (access(cmd->path, X_OK) == -1)
		{
			dup2(saved_stdout, STDOUT_FILENO);
			printf("%s: No such file or directory.\n", cmd->path);
			envp->exitcode = 127;
			exit(envp->exitcode);
		}
	}
	else
		path_help(cmd, envp, saved_stdout);
}
