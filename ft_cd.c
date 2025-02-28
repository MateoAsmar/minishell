/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:00:36 by kakra             #+#    #+#             */
/*   Updated: 2024/11/14 21:00:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_single_quotes(const char *value)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	i = 0;
	j = 0;
	if (!value)
		return (NULL);
	len = strlen(value);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (value[i])
	{
		if (value[i] != '\'')
		{
			result[j] = value[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

void	ft_cdhelper(t_command *cmd, t_env *envp)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	cd_checksq(cmd);
	if (ft_strcmp(cmd->argv[1], "-") == 0)
	{
		if (get_env_var_value("OLDPWD", envp) != NULL)
		{
			if (chdir(get_env_var_value("OLDPWD", envp)) == -1)
				printf("cd: %s: %s\n", cmd->argv[1], strerror(errno));
		}
		else
			printf("cd: OLDPWD not set.\n");
	}
	else if (access(cmd->argv[1], F_OK) == 0)
		cd_help(temp, cmd, envp);
	else if (cmd->argv[1][0] == '-' && ft_strlen(cmd->argv[1]) != 1)
		print_cd_option(cmd, envp);
	else
	{
		printf("cd: %s: %s\n", cmd->argv[1], strerror(errno));
		envp->exitcode = 1;
	}
	free(temp);
}

void	ft_cd(t_command *cmd, t_env *envp)
{
	char	*current_pwd;
	char	*temp;

	clean_args(cmd->argv);
	temp = getcwd(NULL, 0);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
	{
		if (twodsize(cmd->argv) == 1 || (twodsize(cmd->argv) == 2
				&& skip(cmd->argv) == 1))
			ft_cd_home(envp);
		else if (twodsize(cmd->argv) == 2)
			ft_cdhelper(cmd, envp);
		else
		{
			printf("cd: too many arguments\n");
			envp->exitcode = 1;
		}
		if (temp)
		{
			current_pwd = getcwd(NULL, 0);
			update_env_variable(envp, "PWD", current_pwd);
			free(current_pwd);
			free(temp);
		}
	}
}

int	skip(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_valid_identifier(char *name)
{
	int	i;

	i = 0;
	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
