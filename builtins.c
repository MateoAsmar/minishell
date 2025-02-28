/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:22:03 by kakra             #+#    #+#             */
/*   Updated: 2024/12/28 01:13:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwdhelper(t_command *cmd, t_env *envp)
{
	if (cmd->temp_pwd)
		printf("%s\n", cmd->temp_pwd);
	else
		printf("%s\n", get_env_value("PWD", envp));
	envp->exitcode = 0;
}

void	ft_getpwd(t_command *cmd, t_env *envp)
{
	cmd->temp_pwd = getcwd(NULL, 0);
	if (twodsize(cmd->argv) >= 1 && ft_strcmp(cmd->argv[0], "pwd") == 0)
	{
		if (twodsize(cmd->argv) > 1)
		{
			if (cmd->argv[1][0] == '-')
			{
				printf("pwd: %s : invalid option\n", cmd->argv[1]);
				envp->exitcode = 2;
			}
			else
				pwdhelper(cmd, envp);
		}
		else
		{
			if (cmd->temp_pwd)
				printf("%s\n", cmd->temp_pwd);
			else
				printf("%s\n", get_env_value("PWD", envp));
			envp->exitcode = 0;
		}
	}
	free (cmd->temp_pwd);
	exit(envp->exitcode);
}

void	get_env_utils(t_command *cmd, t_env *a)
{
	if (access(cmd->argv[1], F_OK) == 0)
	{
		printf("env: '%s': Permission denied\n", cmd->argv[1]);
		a->exitcode = 126;
	}
	else
	{
		printf("env: '%s': No such file or directory\n", cmd->argv[1]);
		a->exitcode = 127;
	}
}

void	ft_get_env(t_command *cmd, t_env *a)
{
	t_env	*tmp;

	tmp = a;
	if (ft_strcmp(cmd->argv[0], "env") == 0)
	{
		if (twodsize(cmd->argv) == 1)
		{
			while (tmp)
			{
				if (tmp->flag == 0 && tmp->key && tmp->value)
					printf("%s=%s\n", tmp->key, tmp->value);
				tmp = tmp->next;
			}
			a->exitcode = 0;
		}
		else
			get_env_utils(cmd, a);
	}
	exit(a->exitcode);
}

void	ft_exit(t_command *cmd, t_env *envp)
{
	int		error;
	long	exit_code;

	if (ft_strcmp(cmd->argv[0], "exit") == 0)
	{
		if (twodsize(cmd->argv) == 1)
			exit(envp->exitcode);
		else
		{
			exit_code = ft_strtol(cmd->argv[1], &error);
			if (error || exit_code > LONG_MAX || exit_code < LONG_MIN)
			{
				printf("exit: %s: numeric argument required\n", cmd->argv[1]);
				exit(2);
			}
			if (twodsize(cmd->argv) > 2)
			{
				printf("exit: too many arguments\n");
				envp->exitcode = 1;
			}
			printf("exit\n");
			exit(exit_code % 256);
		}
	}
}
