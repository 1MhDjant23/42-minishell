/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:08:49 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/15 14:10:49 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include "exec/structs.h"
# include <sys/stat.h>

# define BBLK "\e[1;30m"
# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BBLU "\e[1;34m"
# define BMAG "\e[1;35m"
# define BCYN "\e[1;36m"
# define RSET "\e[0m"

/*%%%%%%%%%%%%%%%%%%%%%%%% Parsing Part %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

int			g_sig;
int			str_cmp(char *s1, char *s2);
bool		is_space(char *s);
int			is_operator(char c);
t_list		*init_list(t_list *list);
t_elem		*new_elem(char *content, int len, t_token type, t_state state);
void		free_comand(t_command *cmd);
t_list		*ft_lexer(char *str);
int			is_empty(t_list *list);
void		add_tail(t_list *list, t_elem *new);
char		*sub_str(char *str, int start, int len);
int			str_len(char *str);
void		handle_word(char *str, int *i, t_list *list, t_state x);
void		handle_env(char *str, int *i, t_list *list, t_state x);
void		handle_redirections(char *str, int *i, t_list *list, t_state x);
void		handle_quotes(t_list *list, char *str, int *i, t_state *state);
void		sysntax_error(t_list *list, t_minishel *data);
void		free_things(t_list **list, t_command **current);
char		*str_dup(char *str);
void		struct_full(t_list *list, t_minishel *data);
char		*str_join(char *s1, char *s2);
char		**big_join(char **args, char *arg);
char		*cut_string(t_elem **list, t_minishel *data);
bool		is_redir(t_elem *str);
t_command	*init_command(void);
t_herdoc	*init_herdoc(void);
t_redir		*init_redir(void);
t_elem		*skip_space(t_elem *str);
void		check_quotes(t_elem *current, int *count, int *x);
int			check_pipe(t_list *list, t_elem *current);
void		handle_syntax_error(t_list *list, t_minishel *data);
bool		redir_syntax(t_elem *str);
void		put_str(char *str, int fd);
void		env_hand(t_elem *str, t_minishel *data);
char		*cut_herdoc(t_elem **list, t_herdoc *hero);
void		arg_fuller(char *str, t_command *cmds);
void		add_redir(t_redir **list, t_redir *new);
void		add_back(t_command **list, t_command *new);
void		add_herdoc(t_herdoc **list, t_herdoc *new);
void		check_last_redir(t_elem *list, t_command *cmd);
void		_just_send(t_list *list, char *str, 
				t_token new_token, t_state *state);

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*_____________ Execution prototype _________________________*/

void		set_env(t_minishel *data, char **ev);
char		**list_to_darr(t_minishel *data);
void		complex_command(t_minishel *data, t_help *help);
void		execute(t_minishel **data);
void		exec_single_cmd(t_minishel *data, t_command *command);
bool		check_if_builtins(t_command *cmd);
void		simple_execute(t_minishel *data);
void		init_data(t_minishel *data);
char		**own_argv_to_exec(t_command *command, t_minishel *data);
char		*get_env(t_minishel *data, char *var);
int			arg_count(char **str);
char		*extract_str(char *str, t_type stat);
void		add_node(t_env **head, t_env *new);
t_env		*create_node(char *content);
char		*join_wit_path(char *path, char *cmd);
int			get_count_cmd(t_command *cmd);
char		*check_cmd_path(t_minishel *data, char *cmd);
void		redirect_to(t_command *cmd);
int			ft_redirection(t_command *cmd);
int			ft_my_strcmp(const char *s1, const char *s2);
void		if_multi_herdoc(t_command *cmd);
void		manage_precedence(t_minishel *data, t_command *cmd);
/*_____________ Builtins ____________________________________*/
void		run_builtins(t_minishel *data, t_command *cmd, t_type stat);
void		is_builtin(t_minishel *data, t_command *cmd);
void		built_exit(t_minishel *data, t_command *cmd);
void		built_pwd(t_minishel *data);
void		built_export(t_minishel *data, t_command *cmd);
void		built_env(t_minishel *data);
void		built_cd(t_minishel *data, t_command *cmd);
void		built_unset(t_minishel *data, char **arg);
void		built_echo(t_command *cmd);
void		update_working_dir(t_type stat, t_minishel *data);
/*_________________ Pipe func ________________________________________*/
void		init_fork(t_minishel *data);
void		synch_pipe(int **pip, int indx, int n_cmd, t_command *cmd);
int			**return_pipe(t_minishel *data, int x);
/*_________________ HEEEER--------DOOOOC ____________________________________*/
bool		run_herdoc(t_minishel *data);
char		*exp_herdoc(char *line, t_minishel *data, t_help *help);
char		*join_char(char *s, char c);
char		*join_expanded_line(char *s1, char *s2);
char		*extr_var(char *line);
bool		store_file_name(t_command *cmd, int x);
char		*file_path(int x, int y);
int			reserve_for_herdoc(char *file);
void		if_multi_herdoc(t_command *cmd);
void		fill_herd(t_minishel *data, int fd, t_herdoc *her_doc);
bool		ft_her_doc(t_minishel *data, t_command *cmd, int count,
				t_help *help);
/*____________ Cleanner ________________________________________*/
void		handl_error(const char *err_mess, int ex_st, t_minishel *data);
bool		free_file_of_herd(t_minishel *data);
void		unlink_files(char **files);
void		child_handler(int sig);
void		cleann_exec(t_minishel *data, t_command *cmd,
				t_type stat1, t_type stat2);
void		free_old_data(t_minishel *data);
bool		free_file_of_herd(t_minishel *data);
bool		malloc_cid_err(t_minishel *data, int size, t_type stat, char *err);
void		child_exiting(t_minishel *data, int n, int **pip);
void		free_d_array(char **str);
void		free_pipe(int **pipe, int n);
void		reset_wrd_env(t_minishel *data);
int			lenght(t_command *cmd);
bool		save_prv_fd(t_command *cmd);
void		executing_command(t_minishel *data);
void		check_open_herd(t_minishel *data);
bool		create_pipe(t_minishel *data, int **tub, int num_cmd, int i);
void		builtin_exe(t_command *cmd, int **pip, int i, t_minishel *data);
void		close_pipe(int i, int **pip);
void		init_help(t_help *help);
char		*check_other_path(t_minishel *data, char *path);
bool		check_arg(char *arg, t_minishel *data);
bool		special_char(char c);
void		handle_c(int x);
void		signals_hand(t_type stat);
char		*last_check(t_minishel *data);
void		clean_after_signal(char **files);
bool		check_name_file(t_command *cmd, int count, t_minishel *data);
void		running_fill(t_minishel *data, int fd, t_herdoc *her);
bool		after_fill_herd(t_command *cmd, int cid, int fd, t_minishel *data);
#endif