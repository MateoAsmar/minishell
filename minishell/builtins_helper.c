/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:34:06 by kakra             #+#    #+#             */
/*   Updated: 2024/11/21 21:34:06 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*help(t_env *envp)
{
	envp->empty = true;
	return ("");
}

void	flag_env(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (tmp->value == NULL)
			tmp->flag = 1;
		else
			tmp->flag = 0;
		tmp = tmp->next;
	}
}

pid_t	get_pid_from_proc_stat(void)
{
	int		fd;
	char	buffer[256];
	ssize_t	bytes_read;
	pid_t	pid;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (-1);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read <= 0)
	{
		perror("read");
		close(fd);
		return (-1);
	}
	buffer[bytes_read] = '\0';
	pid = ft_atoi(buffer);
	close(fd);
	return (pid);
}

bool	dir_com(t_command *cmd, t_env *envp)
{
	DIR	*dir;

	dir = opendir(cmd->argv[0]);
	if (dir)
	{
		printf("%s: Is a directory\n", cmd->argv[0]);
		envp->exitcode = 126;
		closedir(dir);
		return (true);
	}
	return (false);
}

void	handle_output_redirection(t_command *cmd, int pipefd[2])
{
	if (cmd->output_files != NULL)
		redirect_output(cmd->output_files);
	else if (cmd->next != NULL)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}
