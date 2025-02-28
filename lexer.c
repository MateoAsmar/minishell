/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:20:34 by kakra             #+#    #+#             */
/*   Updated: 2025/01/02 01:28:48 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens, t_token_type type, char *value)
{
	t_token	*token;
	t_token	*temp;

	token = new_token(type, value);
	if (!token)
		return ;
	if (!*tokens)
		*tokens = token;
	else
	{
		temp = *tokens;
		while (temp->next)
			temp = temp->next;
		temp->next = token;
	}
}

bool	lexer_pipe(t_lex *data, t_token *tokens, t_env *envp, char *input)
{
	if (input[data->i] == '|')
	{
		if (data->prev_token == '|' || data->prev_token == 0
			|| data->prev_token == '>')
		{
			printf("Syntax error: unexpected token `|`\n");
			envp->exitcode = 2;
			data->status = false;
			return (true);
		}
		add_token(&tokens, TOKEN_PIPE, "|");
		data->prev_token = '|';
		data->i++;
		return (true);
	}
	return (false);
}

bool	smalllexer(t_lex *data, t_token **tokens, t_env *envp, char *input)
{
	if (lexer_pipe(data, *tokens, envp, input) == true)
		return (true);
	else if (lexer_heredoc(data, tokens, envp, input) == true)
		return (true);
	else if (lexer_append(data, tokens, envp, input) == true)
		return (true);
	else if (lexer_redirect_in(data, tokens, envp, input) == true)
		return (true);
	else if (lexer_redirect_out(data, tokens, envp, input) == true)
		return (true);
	return (false);
}

t_token	*lexer(char *input, t_env *envp)
{
	t_token	*tokens;
	t_lex	data;

	tokens = NULL;
	init_lex(&data);
	while (input[data.i])
	{
		data.status = true;
		while (ft_isspace(input[data.i]))
			data.i++;
		if (smalllexer(&data, &tokens, envp, input) == true)
		{
			if (data.status == false)
			{
				if (tokens)
					free_tokens(tokens);
				return (NULL);
			}
		}
		else
			lexer_helper(&data, &tokens, envp, input);
	}
	if (lexer_fail(data, envp, tokens) == false)
		return (NULL);
	return (tokens);
}
