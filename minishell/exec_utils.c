/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 19:16:54 by kakra             #+#    #+#             */
/*   Updated: 2024/11/24 19:16:54 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipe(t_command *cmd)
{
	if (pipe(cmd->pipefd) == -1)
	{
		printf("pipe");
		exit(1);
	}
}

void	execute_builtin_in_child(t_command *cmd, t_env *envp)
{
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		ft_export(&envp, cmd, envp);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		builtin_unset(&envp, cmd);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		ft_cd(cmd, envp);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		ft_exit(cmd, envp);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		ft_echo(envp, cmd);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		ft_getpwd(cmd, envp);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		ft_get_env(cmd, envp);
}

void	exec_input(t_command *cmd, t_env *envp)
{
	t_input_file	*current_input;
	int				input_fd;

	current_input = cmd->input_files;
	while (current_input)
	{
		input_fd = open(current_input->filename, O_RDONLY);
		if (input_fd < 0)
		{
			perror(current_input->filename);
			envp->exitcode = 1;
			exit(1);
		}
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
		current_input = current_input->next;
	}
}

void	execute_child_process(t_command *cmd, t_env *envp,
				int prev_pipefd[2], char **env)
{
	if (prev_pipefd[0] != -1)
	{
		dup2(prev_pipefd[0], STDIN_FILENO);
		close(prev_pipefd[0]);
		close(prev_pipefd[1]);
	}
	if (cmd->heredoc_fd[0] != -1)
	{
		dup2(cmd->heredoc_fd[0], STDIN_FILENO);
		close(cmd->heredoc_fd[0]);
		cmd->heredoc_fd[0] = -1;
	}
	else if (cmd->input_files != NULL)
		exec_input(cmd, envp);
	handle_output_redirection(cmd, cmd->pipefd);
	if (is_builtin(cmd->argv[0]))
	{
		execute_builtin_in_child(cmd, envp);
		exit(envp->exitcode);
	}
	exec_commands(cmd, envp, cmd->saved_stdout, env);
}

void	handle_parent_pipes(int prev_pipefd[2], int pipefd[2], t_command *cmd)
{
	if (prev_pipefd[0] != -1)
	{
		close(prev_pipefd[0]);
		close(prev_pipefd[1]);
	}
	if (cmd->next != NULL)
	{
		prev_pipefd[0] = pipefd[0];
		prev_pipefd[1] = pipefd[1];
	}
}
