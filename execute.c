/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:46:51 by kakra             #+#    #+#             */
/*   Updated: 2025/01/02 04:18:56 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_command *cmd, t_env *envp, int saved_stdout, char **env)
{
	path(cmd, envp, saved_stdout);
	if (execve(cmd->path, cmd->argv, env) == -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		printf("%s : Command Error\n", cmd->argv[0]);
		envp->exitcode = 127;
		exit(envp->exitcode);
	}
}

void	exec_commands(t_command *cmd, t_env *envp, int saved_stdout, char **env)
{
	char	**new_env;
	char	*cmd_name;

	check_exist(cmd, saved_stdout, envp);
	cmd_name = ft_strdup(cmd->argv[0]);
	if (!cmd_name)
		exit(1);
	if (strcmp(cmd_name, "echo") == 0)
		ft_echo(envp, cmd);
	else if (strcmp(cmd_name, "pwd") == 0)
		ft_getpwd(cmd, envp);
	else if (strcmp(cmd_name, "env") == 0)
		ft_get_env(cmd, envp);
	else if (strcmp(cmd_name, "./minishell") == 0)
	{
		new_env = env_list_to_array(envp);
		execve(cmd->argv[0], cmd->argv, new_env);
		freearray(new_env);
	}
	else
		exec(cmd, envp, saved_stdout, env);
	free(cmd_name);
}

void	heredoc_help_exec(t_command *cmd, t_env *envp)
{
	t_command	*current_cmd;
	int			heredoc_fd[2];

	current_cmd = cmd;
	while (current_cmd != NULL)
	{
		current_cmd->heredoc_fd[0] = -1;
		current_cmd->heredoc_fd[1] = -1;
		if (current_cmd->heredoc_delimiter != NULL)
		{
			handle_heredoc(current_cmd->heredoc_delimiter, envp, heredoc_fd);
			current_cmd->heredoc_fd[0] = heredoc_fd[0];
			current_cmd->heredoc_fd[1] = heredoc_fd[1];
		}
		current_cmd = current_cmd->next;
	}
}

void	exec_helper(t_command *cmd, t_env *envp, int prev_pipefd[2], char **env)
{
	clean_args(cmd->argv);
	signal_handler(SIGINT, cmd->argv[0]);
	if (cmd->next != NULL)
		setup_pipe(cmd);
	cmd->pid = fork();
	if (cmd->pid == -1)
		print_error("Pid Error", envp);
	if (cmd->pid == 0)
		execute_child_process(cmd, envp, prev_pipefd, env);
}

void	execute_commands(t_command *cmd, t_env *envp, char **env)
{
	int			status;
	int			prev_pipefd[2];

	prev_pipefd[0] = -1;
	prev_pipefd[1] = -1;
	init_cmd(cmd);
	heredoc_help_exec(cmd, envp);
	while (cmd != NULL)
	{
		cmd->saved_stdout = dup(STDOUT_FILENO);
		if (cmd->argv == NULL && (cmd->input_files != NULL
				|| cmd->heredoc_delimiter != NULL || cmd->output_files != NULL))
		{
			no_command(cmd, cmd->saved_stdout, cmd->saved_stdin, envp);
			cmd = cmd->next;
			continue ;
		}
		if (dir_com(cmd, envp) == true)
			return ;
		exec_helper(cmd, envp, prev_pipefd, env);
		handle_parent_pipes(prev_pipefd, cmd->pipefd, cmd);
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		envp->exitcode = (status >> 8) & 0xFF;
}
