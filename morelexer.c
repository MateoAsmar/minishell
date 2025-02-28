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

bool	check_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

bool	checko(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			return (false);
		i++;
	}
	return (true);
}

void	checkquotes(t_lex *data, t_token **tokens)
{
	char	*check;

	check = remove_quotes(data->value);
	if (ft_strcmp(check, "export") == 0)
		data->export = true;
	free(data->value);
	add_token(tokens, TOKEN_WORD, check);
	free(check);
}

bool	check_error(t_lex *data, t_env *envp)
{
	if (data->singlequote || data->doublequote)
	{
		printf("Syntax error: unclosed quote\n");
		data->status = false;
		envp->exitcode = 2;
		return (false);
	}
	return (true);
}

void	lexer_add(t_lex *data, t_token **tokens)
{
	bool	dollar;
	bool	sign;

	sign = false;
	dollar = false;
	dollar = check_sign(data->value);
	sign = checko(data->value);
	if (dollar == true || sign == true || data->export == true)
	{
		add_token(tokens, TOKEN_WORD, data->value);
		if (ft_strcmp(data->value, "export") == 0)
			data->export = true;
		free(data->value);
	}
	else
		checkquotes(data, tokens);
}
