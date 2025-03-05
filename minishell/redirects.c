/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:36:46 by kakra             #+#    #+#             */
/*   Updated: 2024/11/23 18:36:46 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_var_name(char *str, int *index)
{
	int	start;
	int	len;

	start = *index;
	len = 0;
	while (str[*index] && (ft_isalnum(str[*index]) || str[*index] == '_'))
	{
		(*index)++;
		len++;
	}
	return (ft_substr(str, start, len));
}

char	*expand_variables_in_line(char *line, t_env *envp)
{
	char	*expanded_line;
	char	temp[2];

	expanded_line = NULL;
	envp->i = 0;
	if (!line)
		return (NULL);
	if (ft_strlen(line) == 0)
		return (help(envp));
	while (line[envp->i])
	{
		if (line[envp->i] == '$' && (ft_isalnum(line[envp->i + 1])
				|| line[envp->i + 1] == '_' || line[envp->i + 1] == '?'))
			expanded_line = expand_help(expanded_line, envp, line);
		else
		{
			temp[0] = line[envp->i];
			temp[1] = '\0';
			expanded_line = safe_strjoin(expanded_line, temp);
			envp->i++;
		}
	}
	return (expanded_line);
}

void	heredoc_help(char *line, int *heredoc_fd, t_env *envp)
{
	char	*expanded_line;

	if (*line == '\0')
		write(heredoc_fd[1], "\n", 1);
	else
	{
		expanded_line = expand_variables_in_line(line, envp);
		if (expanded_line)
		{
			write(heredoc_fd[1], expanded_line, ft_strlen(expanded_line));
			free(expanded_line);
		}
		write(heredoc_fd[1], "\n", 1);
	}
}

void	handle_heredoc(char *delimiter, t_env *envp, int *heredoc_fd)
{
	char	*line;

	pipe(heredoc_fd);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(heredoc_fd[1]);
			heredoc_fd[1] = -1;
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		heredoc_help(line, heredoc_fd, envp);
		free(line);
	}
	close(heredoc_fd[1]);
}

void	redirect_output(t_output_file *output_files)
{
	t_output_file	*current;
	int				fd;

	current = output_files;
	while (current)
	{
		if (current->append)
			fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			printf("open error");
			exit(1);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			printf("dup2 error");
			exit(1);
		}
		close(fd);
		current = current->next;
	}
}
