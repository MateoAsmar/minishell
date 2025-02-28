/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exportutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:07:05 by kakra             #+#    #+#             */
/*   Updated: 2024/12/26 20:12:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_value(t_env *existing, char *value)
{
	if (existing->value)
		free(existing->value);
	if (value)
		existing->value = ft_strdup(value);
	else
		existing->value = NULL;
}

void	add_new_env_node(t_env **env_list, char *key, char *value)
{
	t_env	*new_env;
	t_env	*temp;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return ;
	new_env->key = ft_strdup(key);
	if (value)
		new_env->value = ft_strdup(value);
	else
		new_env->value = NULL;
	new_env->next = NULL;
	if (*env_list == NULL)
		*env_list = new_env;
	else
	{
		temp = *env_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_env;
	}
}

void	set_env(t_env **env_list, char *key, char *value)
{
	t_env	*existing;

	existing = find_env(*env_list, key);
	if (existing)
		update_env_value(existing, value);
	else
		add_new_env_node(env_list, key, value);
}

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = ft_strdup(key);
	if (value)
		new_env->value = ft_strdup(value);
	else
		new_env->value = NULL;
	new_env->next = NULL;
	return (new_env);
}

void	insert_sorted_env(t_env **sorted_env, t_env *new_env)
{
	t_env	*current;

	current = *sorted_env;
	if (!*sorted_env || ft_strcmp(new_env->key, (*sorted_env)->key) < 0)
	{
		new_env->next = *sorted_env;
		*sorted_env = new_env;
	}
	else
	{
		while (current->next && ft_strcmp(new_env->key, current->next->key) > 0)
			current = current->next;
		new_env->next = current->next;
		current->next = new_env;
	}
}
