/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtolst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:57:02 by kakra             #+#    #+#             */
/*   Updated: 2024/11/16 19:11:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_env_var(char *env_var, char **key, char **value)
{
	int	i;

	i = 0;
	while (env_var[i] != '\0' && env_var[i] != '=')
		i++;
	*key = (char *)malloc(i + 1);
	if (*key == NULL)
		return ;
	ft_strncpy(*key, env_var, i);
	(*key)[i] = '\0';
	if (env_var[i] == '=')
		*value = ft_strdup(&env_var[i + 1]);
	else
		*value = NULL;
}

t_env	*add_env_node(t_env *head, const char *key, const char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
		return (NULL);
	new_node->key = ft_strdup((char *)key);
	if (value)
		new_node->value = ft_strdup((char *)value);
	else
		new_node->value = NULL;
	new_node->flag = 0;
	new_node->exitcode = 0;
	new_node->next = NULL;
	if (head == NULL)
		return (new_node);
	current = head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	return (head);
}

t_env	*env_to_list(char **env)
{
	t_env	*head;
	char	*value;
	char	*key;
	int		i;

	head = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		split_env_var(env[i], &key, &value);
		head = add_env_node(head, key, value);
		free(key);
		if (value != NULL)
			free(value);
		i++;
	}
	return (head);
}

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		if (tmp->value != NULL)
			free(tmp->value);
		free(tmp);
	}
}

void	add_to_env(t_env **envp, const char *key, const char *value)
{
	t_env	*new_node;
	t_env	*current;

	current = *envp;
	if (current->key == NULL && current->value == NULL)
	{
		current->key = strdup(key);
		current->value = strdup(value);
		current->next = NULL;
		return ;
	}
	while (current->next != NULL)
	{
		current = current->next;
	}
	new_node = malloc(sizeof(t_env));
	new_node->key = strdup(key);
	new_node->value = strdup(value);
	new_node->next = NULL;
	current->next = new_node;
}
