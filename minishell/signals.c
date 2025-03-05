/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra  <kakra@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:31:26 by kakra             #+#    #+#             */
/*   Updated: 2024/11/29 21:31:26 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handl_nth(int sig)
{
	(void)sig;
	return ;
}

void	handle_nel(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		return ;
	}
}

void	signal_handler(int sig, char *cmd)
{
	(void)sig;
	if (cmd && ft_strcmp(cmd, "./minishell") == 0)
	{
		signal(SIGINT, handl_nth);
	}
	else
	{
		signal(SIGINT, handle_nel);
	}
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_last_exit_code = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

char	*get_env_value(char *var_name, t_env *envp)
{
	t_env	*temp;

	temp = envp;
	while (temp)
	{
		if (ft_strcmp(temp->key, var_name) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}
