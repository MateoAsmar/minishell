/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:36:21 by kakra             #+#    #+#             */
/*   Updated: 2025/01/02 04:13:52 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include "Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/types.h>
# include <dirent.h>

extern int	g_last_exit_code;

typedef struct s_exp
{
	char	*key;
	char	*value;
	char	*expanded_key;
	int		i;
	bool	check;
	char	*tempo;
	char	*final_value;
	char	*temp;
	bool	exit;
}				t_exp;

typedef struct s_lex
{
	char	*start;
	char	*value;
	bool	singlequote;
	bool	doublequote;
	int		i;
	bool	status;
	bool	export;
	char	prev_token;
	bool	check;
}				t_lex;

typedef struct s_output_file
{
	char					*filename;
	int						append;
	struct s_output_file	*next;
}				t_output_file;

typedef struct s_var
{
	int		i;
	char	*arg;
	char	*new_arg;
	int		inside_single_quote;
	int		inside_double_quote;
	int		j;
	char	*exit_code_str;
	char	*var_name;
	char	*var_value;
	int		len;
	char	temp[2];
}				t_var;

typedef struct s_echo
{
	int		i;
	int		j;
	bool	newline;
	int		in_single_quote;
	int		in_double_quote;
}				t_echo;

typedef struct s_env
{
	char			*key;
	char			*value;
	char			**paths;
	char			**command;
	int				exitcode;
	int				flag;
	char			*oldpwd;
	int				pid;
	int				i;
	struct s_env	*next;
	bool			empty;
}		t_env;

typedef struct s_input_file
{
	char				*filename;
	struct s_input_file	*next;
}				t_input_file;

typedef struct s_command
{
	char				**argv;
	char				*heredoc_delimiter;
	t_output_file		*output_files;
	t_input_file		*input_files;
	struct s_command	*next;
	char				*temp_pwd;
	char				*path;
	int					heredoc_fd[2];
	int					saved_stdout;
	int					saved_stdin;
	pid_t				pid;
	int					pipefd[2];
	int					command;
	char				**eni;
	bool				to;
}		t_command;

typedef struct s_mini
{
	char	**envp;
	char	*path;
	int		exitcode;
}			t_mini;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND_OUT,
	TOKEN_HEREDOC,
	TOKEN_EOF,
}		t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}			t_token;

int			lstsize(t_token *tokens);
char		*remove_single_quotes(const char *value);
t_token		*lexer(char *input, t_env *envp);
char		*get_env_var_value(char *var_name, t_env *envp);
char		**env_list_to_array(t_env *envp);
void		ft_cd(t_command *t_command, t_env *envp);
void		update_shlvl(t_env *env);
void		ft_getpwd(t_command *cmd, t_env *envp);
t_env		*add_env_node(t_env *head, const char *key, const char *value);
void		add_to_env(t_env **envp, const char *key, const char *value);
void		ft_get_env(t_command *cmd, t_env *a);
void		ft_exit(t_command *cmd, t_env *envp);
pid_t		get_pid_from_proc_stat(void);
void		ft_echo(t_env *env, t_command *cmd);
char		*expand_help(char *expanded_line, t_env *envp, char *line);
void		redirect_output(t_output_file *output_files);
void		free_tokens(t_token *tokens);
void		handle_signal(int sig);
t_env		*env_to_list(char **env);
void		free_env_list(t_env *head);
void		builtin_export(t_env **env_list, t_command *cmd, t_env *envp);
void		ft_export(t_env **env_list, t_command *cmd, t_env *envp);
void		flag_env(t_env *env_list);
int			is_valid_identifier(char *name);
t_env		*find_env(t_env *env, char *key);
bool		check_char_after_var(t_command *cmd, t_echo *data, char next_char);
void		set_env(t_env **env_list, char *key, char *value);
t_env		*create_env_node(char *key, char *value);
void		insert_sorted_env(t_env **sorted_env, t_env *new_env);
t_env		*copy_and_sort_env(t_env *env);
void		display_env_list(t_env *env, int only_export);
void		free_env_listt(t_env *env);
void		display_sorted_env(t_env *env, int only_export);
void		handle_display_sorted_env(t_env **env_list, t_command *cmd);
t_command	*parse_tokens(t_token *tokens);
void		free_command_list(t_command *cmd_list);
void		execute_commands(t_command *cmd, t_env *envp, char **env);
char		*accesspath(t_env *a, char *cmd, int saved_stdout);
void		replace_env_variables(t_command *cmd, t_env *envp);
int			skip(char **str);
bool		echo_pid(t_command *cmd, t_echo *data, t_env *env);
bool		echo_exit(t_command *cmd, t_echo *data, t_env *env);
bool		check_quotation(t_command *cmd, t_echo *data);
bool		check_more_quotation(t_command *cmd, t_echo *data);
char		*copy_substring(char *src, int start, int len);
bool		lexer_heredoc(t_lex *data, t_token **tokens,
				t_env *envp, char *input);
bool		lexer_append(t_lex *data, t_token **tokens,
				t_env *envp, char *input);
bool		lexer_redirect_in(t_lex *data, t_token **tokens,
				t_env *envp, char *input);
bool		lexer_redirect_out(t_lex *data, t_token **tokens,
				t_env *envp, char *input);
void		lexer_helper(t_lex *data, t_token **tokens,
				t_env *envp, char *input);
bool		check_syntax_error_after_redirection(char *input,
				int i, t_env *envp);
void		add_token(t_token **tokens, t_token_type type, char *value);
void		init_lex(t_lex *data);
bool		lexer_error(t_lex *data, t_env *envp);
void		add_output_file(t_command *cmd, char *filename, int append);
t_command	*create_command(void);
void		handle_heredoc(char *delimiter, t_env *envp, int *heredoc_fd);
void		redirect_output(t_output_file *output_files);
char		*expand_variables_in_line(char *line, t_env *envp);
char		*extract_var_name(char *str, int *index);
char		*get_env_value(char *var_name, t_env *envp);
void		handle_parent_pipes(int prev_pipefd[2], int pipefd[2],
				t_command *cmd);
void		execute_child_process(t_command *cmd, t_env *envp,
				int prev_pipefd[2], char **env);
void		handle_output_redirection(t_command *cmd, int pipefd[2]);
void		setup_pipe(t_command *cmd);
void		exec_commands(t_command *cmd, t_env *envp, int saved_stdout,
				char **env);
void		update_env_variable(t_env *envp, char *key, char *value);
void		print_error(char *str, t_env *envp);
void		handl_nth(int sig);
void		handle_nel(int sig);
void		signal_handler(int sig, char *cmd);
void		parser_helper(t_command **current_cmd);
bool		lexer_fail(t_lex data, t_env *envp, t_token *tokens);
char		*remove_quotes(const char *str);
void		lexer_add(t_lex *data, t_token **tokens);
bool		check_error(t_lex *data, t_env *envp);
void		init_exp(t_exp	*data);
void		data_init(t_echo *data);
void		check_echo_n(t_command *cmd, t_echo *data);
int			is_n_option(char *arg);
char		*help(t_env *envp);
void		ft_cd_home(t_env *envp);
void		cd_helper(t_command *cmd, t_env *envp);
void		cd_helper1(t_command *cmd, t_env *envp);
void		cd_checksq(t_command *cmd);
void		print_cd_option(t_command *cmd, t_env *envp);
void		init_lst(t_var *data, t_command *cmd);
void		init_cmd(t_command *cmd);
void		no_command(t_command *cmd, int saved_stdout,
				int saved_stdin, t_env *envp);
void		no_command_input(t_command *cmd, int saved_stdout, t_env *envp);
void		path(t_command *cmd, t_env *envp, int saved_stdout);
bool		dir_com(t_command *cmd, t_env *envp);
void		handle_output_redirection(t_command *cmd, int pipefd[2]);
bool		is_builtin(char *cmd);
void		check_exist(t_command *cmd, int saved_stdout, t_env *envp);
void		ec_help(t_var *data, t_env *envp);
void		path_help(t_command *cmd, t_env *envp, int saved_stdout);
void		builtin_unset(t_env **env_list, t_command *cmd);
void		cd_help(char *temp, t_command *cmd, t_env *envp);

#endif