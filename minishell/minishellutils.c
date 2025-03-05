/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:17:32 by kakra             #+#    #+#             */
/*   Updated: 2024/12/29 02:44:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lstsize(t_token *tokens)
{
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

char	**allocate_env_array(t_env *envp, int *count)
{
	t_env	*tmp;
	char	**env_array;

	tmp = envp;
	*count = 0;
	while (tmp)
	{
		(*count)++;
		tmp = tmp->next;
	}
	env_array = malloc((*count + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	return (env_array);
}

char	**env_list_to_array(t_env *envp)
{
	char	**env_array;
	t_env	*tmp;
	int		count;
	int		i;
	char	*temp;

	env_array = allocate_env_array(envp, &count);
	if (!env_array)
		return (NULL);
	tmp = envp;
	i = 0;
	while (tmp)
	{
		env_array[i] = ft_strjoin(tmp->key, "=");
		temp = env_array[i];
		env_array[i] = ft_strjoin(env_array[i], tmp->value);
		free(temp);
		i++;
		tmp = tmp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	ec_help(t_var *data, t_env *envp)
{
	if (g_last_exit_code != 0)
		envp->exitcode = g_last_exit_code;
	data->exit_code_str = ft_itoa(envp->exitcode);
	data->new_arg = safe_strjoin(data->new_arg, data->exit_code_str);
	free(data->exit_code_str);
	data->j++;
}
