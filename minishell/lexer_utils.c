/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:55:29 by kakra             #+#    #+#             */
/*   Updated: 2024/11/20 21:55:29 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	lexer_heredoc(t_lex *data, t_token **tokens, t_env *envp, char *input)
{
	if (input[data->i] == '<' && input[data->i + 1] == '<')
	{
		if (data->prev_token == '>' || data->prev_token == '<')
		{
			printf("Syntax error: unexpected token `<<`\n");
			envp->exitcode = 2;
			data->status = false;
			return (true);
		}
		add_token(tokens, TOKEN_HEREDOC, "<<");
		data->prev_token = '<';
		data->i += 2;
		if (!check_syntax_error_after_redirection(input, data->i, envp))
		{
			data->status = false;
			return (true);
		}
		return (true);
	}
	return (false);
}

bool	lexer_append(t_lex *data, t_token **tokens, t_env *envp, char *input)
{
	if (input[data->i] == '>' && input[data->i + 1] == '>')
	{
		if (data->prev_token == '>' || data->prev_token == '<')
		{
			printf("Syntax error: unexpected token `>>`\n");
			envp->exitcode = 2;
			data->status = false;
			return (true);
		}
		add_token(tokens, TOKEN_APPEND_OUT, ">>");
		data->prev_token = '>';
		data->i += 2;
		if (!check_syntax_error_after_redirection(input, data->i, envp))
		{
			data->status = false;
			return (true);
		}
		return (true);
	}
	return (false);
}

bool	lexer_redirect_in(t_lex *data, t_token **tokens,
		t_env *envp, char *input)
{
	if (input[data->i] == '<')
	{
		if (data->prev_token == '>' || data->prev_token == '<')
		{
			printf("Syntax error: unexpected token `<`\n");
			envp->exitcode = 2;
			data->status = false;
			return (true);
		}
		add_token(tokens, TOKEN_REDIRECT_IN, "<");
		data->prev_token = '<';
		data->i++;
		if (!check_syntax_error_after_redirection(input, data->i, envp))
		{
			data->status = false;
			return (true);
		}
		return (true);
	}
	return (false);
}

bool	lexer_redirect_out(t_lex *data, t_token **tokens,
	t_env *envp, char *input)
{
	if (input[data->i] == '>')
	{
		if (data->prev_token == '>' || data->prev_token == '<')
		{
			printf("Syntax error: unexpected token `>`\n");
			envp->exitcode = 2;
			data->status = false;
			return (true);
		}
		add_token(tokens, TOKEN_REDIRECT_OUT, ">");
		data->prev_token = '>';
		data->i++;
		if (!check_syntax_error_after_redirection(input, data->i, envp))
		{
			data->status = false;
			return (true);
		}
		return (true);
	}
	return (false);
}

void	lexer_helper(t_lex *data, t_token **tokens, t_env *envp, char *input)
{
	data->start = &input[data->i];
	while (input[data->i] && (!ft_isspace(input[data->i])
			|| data->singlequote || data->doublequote))
	{
		if (input[data->i] == '\'' && !data->doublequote)
			data->singlequote = !data->singlequote;
		else if (input[data->i] == '"' && !data->singlequote)
			data->doublequote = !data->doublequote;
		else
		{
		}
		data->i++;
	}
	if (check_error(data, envp) == false)
		return ;
	data->value = ft_strndup(data->start, &input[data->i] - data->start);
	lexer_add(data, tokens);
	data->prev_token = 'w';
}
