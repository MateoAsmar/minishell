/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:12:57 by kakra             #+#    #+#             */
/*   Updated: 2024/12/25 13:52:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_argv(t_command *cmd, char *arg)
{
	int		argc;
	char	**new_argv;
	int		i;

	i = 0;
	argc = 0;
	while (cmd->argv && cmd->argv[argc])
		argc++;
	new_argv = malloc(sizeof(char *) * (argc + 2));
	if (new_argv == NULL)
		exit(1);
	while (i < argc)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[argc] = ft_strdup(arg);
	new_argv[argc + 1] = NULL;
	if (cmd->argv)
		free(cmd->argv);
	cmd->argv = new_argv;
}

void	word_parse(t_token **tokens, t_command *current_cmd)
{
	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_REDIRECT_IN
		&& (*tokens)->type != TOKEN_REDIRECT_OUT
		&& (*tokens)->type != TOKEN_APPEND_OUT
		&& (*tokens)->type != TOKEN_HEREDOC)
	{
		if ((*tokens)->type == TOKEN_WORD)
			add_to_argv(current_cmd, (*tokens)->value);
		*tokens = (*tokens)->next;
	}
}

void	add_input_file(t_command *cmd, char *filename)
{
	t_input_file	*new_input_file;
	t_input_file	*temp;

	new_input_file = malloc(sizeof(t_input_file));
	if (!new_input_file)
		exit(1);
	new_input_file->filename = ft_strdup(filename);
	new_input_file->next = NULL;
	if (!cmd->input_files)
	{
		cmd->input_files = new_input_file;
	}
	else
	{
		temp = cmd->input_files;
		while (temp->next)
			temp = temp->next;
		temp->next = new_input_file;
	}
}

void	parse_redi(t_token **tokens, t_command *current_cmd)
{
	if ((*tokens)->next && (*tokens)->next->type == TOKEN_WORD)
	{
		if ((*tokens)->type == TOKEN_REDIRECT_IN)
		{
			add_input_file(current_cmd, (*tokens)->next->value);
		}
		else if ((*tokens)->type == TOKEN_REDIRECT_OUT)
		{
			add_output_file(current_cmd, (*tokens)->next->value, 0);
		}
		else if ((*tokens)->type == TOKEN_APPEND_OUT)
		{
			add_output_file(current_cmd, (*tokens)->next->value, 1);
		}
		else if ((*tokens)->type == TOKEN_HEREDOC)
		{
			current_cmd->heredoc_delimiter = ft_strdup((*tokens)->next->value);
		}
		*tokens = (*tokens)->next;
	}
}

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*cmd_list;
	t_command	*current_cmd;

	cmd_list = create_command();
	current_cmd = cmd_list;
	while (tokens && tokens->type != TOKEN_EOF)
	{
		word_parse(&tokens, current_cmd);
		if (tokens && (tokens->type == TOKEN_PIPE
				|| tokens->type == TOKEN_REDIRECT_IN
				|| tokens->type == TOKEN_REDIRECT_OUT
				|| tokens->type == TOKEN_APPEND_OUT
				|| tokens->type == TOKEN_HEREDOC))
		{
			if (tokens->type == TOKEN_PIPE)
				parser_helper(&current_cmd);
			else
				parse_redi(&tokens, current_cmd);
		}
		if (tokens)
			tokens = tokens->next;
	}
	return (cmd_list);
}
