/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exportmoreutils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:08:11 by kakra             #+#    #+#             */
/*   Updated: 2024/11/16 19:25:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*copy_and_sort_env(t_env *env)
{
	t_env	*sorted_env;
	t_env	*tmp;
	t_env	*new_env;

	tmp = env;
	sorted_env = NULL;
	while (tmp)
	{
		new_env = create_env_node(tmp->key, tmp->value);
		if (!new_env)
			return (NULL);
		insert_sorted_env(&sorted_env, new_env);
		tmp = tmp->next;
	}
	return (sorted_env);
}

void	display_env_list(t_env *env, int only_export)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (only_export || tmp->value)
		{
			printf("declare -x %s", tmp->key);
			if (tmp->value)
				printf("=\"%s\"", tmp->value);
			printf("\n");
		}
		tmp = tmp->next;
	}
}

void	free_env_listt(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	display_sorted_env(t_env *env, int only_export)
{
	t_env	*sorted_env;

	sorted_env = copy_and_sort_env(env);
	if (!sorted_env)
		return ;
	display_env_list(sorted_env, only_export);
	free_env_listt(sorted_env);
}

void	handle_display_sorted_env(t_env **env_list, t_command *cmd)
{
	if (twodsize(cmd->argv) == 1)
		display_sorted_env(*env_list, 1);
}
