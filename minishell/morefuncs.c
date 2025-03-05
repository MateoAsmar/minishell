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

void	print_error(char *str, t_env *envp)
{
	printf("%s\n", str);
	envp->exitcode = 127;
	exit(envp->exitcode);
}

void	parser_helper(t_command **current_cmd)
{
	(*current_cmd)->next = create_command();
	*current_cmd = (*current_cmd)->next;
}

bool	lexer_fail(t_lex data, t_env *envp, t_token *tokens)
{
	if (lexer_error(&data, envp) == false)
	{
		if (tokens)
			free_tokens(tokens);
		return (false);
	}
	else if (data.status == false)
	{
		if (tokens)
			free_tokens(tokens);
		return (false);
	}
	return (true);
}

char	*remove_quotes(const char *str)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i++;
			continue ;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

t_env	*find_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
