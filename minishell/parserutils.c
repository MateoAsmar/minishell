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

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (argv)
	{
		while (argv[i])
		{
			free(argv[i]);
			i++;
		}
		free(argv);
	}
}

void	free_output_files(t_output_file *output_files)
{
	t_output_file	*temp;

	while (output_files)
	{
		temp = output_files;
		free(output_files->filename);
		output_files = output_files->next;
		free(temp);
	}
}

void	free_input_files(t_input_file *input_files)
{
	t_input_file	*temp;

	while (input_files)
	{
		temp = input_files;
		input_files = input_files->next;
		free(temp->filename);
		free(temp);
	}
}

void	free_command_list(t_command *cmd)
{
	t_command	*current;
	int			i;

	while (cmd)
	{
		current = cmd;
		if (cmd->input_files)
			free_input_files(cmd->input_files);
		if (cmd->heredoc_delimiter)
			free(cmd->heredoc_delimiter);
		if (cmd->output_files)
			free_output_files(cmd->output_files);
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		free(cmd->argv);
		cmd = cmd->next;
		free(current);
	}
}

void	add_output_file(t_command *cmd, char *filename, int append)
{
	t_output_file	*new_output_file;
	t_output_file	*temp;

	new_output_file = malloc(sizeof(t_output_file));
	new_output_file->filename = ft_strdup(filename);
	new_output_file->append = append;
	new_output_file->next = NULL;
	if (!cmd->output_files)
	{
		cmd->output_files = new_output_file;
	}
	else
	{
		temp = cmd->output_files;
		while (temp->next)
			temp = temp->next;
		temp->next = new_output_file;
	}
}
