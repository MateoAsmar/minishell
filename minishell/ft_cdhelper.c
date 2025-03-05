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

void	ft_cd_home(t_env *envp)
{
	if (get_env_value("HOME", envp) == NULL)
	{
		printf("cd : HOME not set.\n");
		envp->exitcode = 1;
	}
	else
	{
		envp->oldpwd = getcwd(NULL, 0);
		update_env_variable(envp, "OLDPWD", envp->oldpwd);
		if (chdir(get_env_value("HOME", envp)) == -1)
			printf("cd: %s: %s\n", "HOME", strerror(errno));
		free(envp->oldpwd);
	}
}

void	cd_helper(t_command *cmd, t_env *envp)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (access(cmd->argv[1], X_OK) == -1)
	{
		printf("cd: %s: %s\n", cmd->argv[1], strerror(errno));
		envp->exitcode = 1;
	}
	else if (chdir(cmd->argv[1]) == -1)
	{
		printf("cd: %s: %s\n", cmd->argv[1], strerror(errno));
		envp->exitcode = 1;
	}
	else
	{
		envp->oldpwd = temp;
		update_env_variable(envp, "OLDPWD", envp->oldpwd);
		temp = getcwd(NULL, 0);
		update_env_variable(envp, "PWD", temp);
		free(envp->oldpwd);
	}
	free(temp);
}

void	cd_helper1(t_command *cmd, t_env *envp)
{
	char	*temppwd;

	temppwd = ft_strjoin(get_env_value("PWD", envp), "/..");
	update_env_variable(envp, "OLDPWD", get_env_value("PWD", envp));
	update_env_variable(envp, "PWD", temppwd);
	printf("cd: error retrieving current directory\n");
	chdir(cmd->argv[1]);
	free(temppwd);
}

void	cd_checksq(t_command *cmd)
{
	char	*ar;

	if (cmd->argv[1][0] == '\'')
	{
		ar = remove_single_quotes(cmd->argv[1]);
		free(cmd->argv[1]);
		cmd->argv[1] = ar;
	}
}

void	print_cd_option(t_command *cmd, t_env *envp)
{
	printf("cd: %s: invalid option\n", cmd->argv[1]);
	envp->exitcode = 2;
}
