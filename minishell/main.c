/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:38:07 by kakra             #+#    #+#             */
/*   Updated: 2025/01/02 01:28:11 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_code = 0;

t_env	*newenv(char **env)
{
	t_env		*envp;

	envp = env_to_list(env);
	envp->pid = get_pid_from_proc_stat();
	envp->exitcode = 0;
	envp->empty = false;
	return (envp);
}

t_env	*noenv(void)
{
	t_env		*envp;
	char		*pwd;

	envp = malloc(sizeof(t_env));
	pwd = getcwd(NULL, 0);
	envp->empty = false;
	envp = malloc(sizeof(t_env));
	envp->pid = get_pid_from_proc_stat();
	envp->exitcode = 0;
	envp->next = NULL;
	add_to_env(&envp, "PWD", pwd);
	add_to_env(&envp, "SHLVL", "1");
	add_to_env(&envp, "OLDPWD", "");
	free(pwd);
	return (envp);
}

bool	my_funcs(t_command *cmd, t_env *envp)
{
	if (cmd->argv != NULL)
	{
		if (ft_strcmp("export", cmd->argv[0]) == 0 && cmd->next == NULL)
		{
			ft_export(&envp, cmd, envp);
			return (true);
		}
		else if (ft_strcmp("unset", cmd->argv[0]) == 0 && cmd->next == NULL)
		{
			builtin_unset(&envp, cmd);
			return (true);
		}
		else if (ft_strcmp("exit", cmd->argv[0]) == 0 && cmd->next == NULL)
		{
			ft_exit(cmd, envp);
			return (true);
		}
		else if (ft_strcmp("cd", cmd->argv[0]) == 0 && cmd->next == NULL)
		{
			ft_cd(cmd, envp);
			return (true);
		}
	}
	return (false);
}

void	shell(char *input, char **env, t_env *envp)
{
	t_token		*tokens;
	t_command	*cmd;

	add_history(input);
	tokens = lexer(input, envp);
	if (tokens == NULL)
		return ;
	cmd = parse_tokens(tokens);
	if (cmd->argv != NULL)
		replace_env_variables(cmd, envp);
	if (lstsize(tokens) != 0)
	{
		if (my_funcs(cmd, envp) == true)
		{
		}
		else
			execute_commands(cmd, envp, env);
	}
	g_last_exit_code = envp->exitcode;
	free_tokens(tokens);
	free_command_list(cmd);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_env		*envp;

	if (env && *env && argc == 1 && argv)
		envp = newenv(env);
	else
		envp = noenv();
	update_shlvl(envp);
	printf("\n(_,   ()   /\\   ~|~   _\\~   |-|   [-   |_   |_ \n\n");
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		input = readline("GOATSHELL > ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			shell(input, env, envp);
		free(input);
	}
	free_env_list(envp);
	exit(g_last_exit_code);
}
