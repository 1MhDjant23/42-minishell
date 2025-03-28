//  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣦⣴⣶⣾⣿⣶⣶⣶⣶⣦⣤⣄⠀⠀⠀⠀⠀⠀⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢠⡶⠻⠛⠟⠋⠉⠀⠈⠤⠴⠶⠶⢾⣿⣿⣿⣷⣦⠄⠀⠀⠀         𓐓  step_one_to_exec.c 𓐔           
//  ⠀⠀⠀⠀⠀⢀⠔⠋⠀⠀⠤⠒⠒⢲⠀⠀⠀⢀⣠⣤⣤⣬⣽⣿⣿⣿⣷⣄⠀⠀                                              
//  ⠀⠀⠀⣀⣎⢤⣶⣾⠅⠀⠀⢀⡤⠏⠀⠀⠀⠠⣄⣈⡙⠻⢿⣿⣿⣿⣿⣿⣦⠀ Student: mait-taj <mait-taj@student.1337.ma> 
//  ⢀⠔⠉⠀⠊⠿⠿⣿⠂⠠⠢⣤⠤⣤⣼⣿⣶⣶⣤⣝⣻⣷⣦⣍⡻⣿⣿⣿⣿⡀                                              
//  ⢾⣾⣆⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠉⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇                                              
//  ⠀⠈⢋⢹⠋⠉⠙⢦⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇      Created: 2025/03/28 21:53:13 by mait-taj
//  ⠀⠀⠀⠑⠀⠀⠀⠈⡇⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇      Updated: 2025/03/28 21:53:15 by mait-taj
//  ⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⢀⣾⣿⣿⠿⠟⠛⠋⠛⢿⣿⣿⠻⣿⣿⣿⣿⡿⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⢠⣿⣟⣭⣤⣶⣦⣄⡀⠀⠀⠈⠻⠀⠘⣿⣿⣿⠇⠀                                              
//  ⠀⠀⠀⠀⠀⠱⠤⠊⠀⢀⣿⡿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠘⣿⠏⠀⠀                             𓆩♕𓆪      
//  ⠀⠀⠀⠀⠀⡄⠀⠀⠀⠘⢧⡀⠀⠀⠸⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠐⠋⠀⠀⠀                           𓄂 mait-taj𓆃  
//  ⠀⠀⠀⠀⠀⠘⠄⣀⡀⠸⠓⠀⠀⠀⠠⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                   
#include "../minishell.h"

void	execute(t_minishel **data)
{
	char	*get;

	init_data(*data);
	if (!(*data)->cmd)
		return ;
	if (run_herdoc(*data) == false)
	{
		return ;
	}
	get = get_env(*data, "PATH");
	(*data)->path = ft_split(get, ':');
	free(get);
	get = NULL;
	if (get_count_cmd((*data)->cmd) == 1)
	{
		if (save_prv_fd((*data)->cmd) == false)
		{
			(*data)->exit_status = 1;
			free_old_data(*data);
			return ;
		}
	}
	executing_command(*data);
}

void	executing_command(t_minishel *data)
{
	t_help	help;

	init_help(&help);
	if (get_count_cmd(data->cmd) == 1)
		simple_execute(data);
	else if (get_count_cmd(data->cmd) > 1)
	{
		init_fork(data);
		init_help(&help);
		complex_command(data, &help);
	}
	check_open_herd(data);
	free_old_data(data);
}

void	simple_execute(t_minishel *data)
{
	char	*paths;

	if (check_if_builtins(data->cmd) == true)
		run_builtins(data, data->cmd, simple);
	else
	{
		malloc_cid_err(data, 1, alloc, NULL);
		data->cid[0] = fork();
		if (data->cid[0] == -1)
		{
			if (malloc_cid_err(data, 0, error, "fork") == false)
				return ;
		}
		g_sig = -11;
		if (data->cid[0] == 0)
		{
			manage_precedence(data, data->cmd);
			paths = last_check(data);
			data->command_line = own_argv_to_exec(data->cmd, data);
			if (execve(paths, data->command_line, list_to_darr(data)) == -1)
				perror("execve");
		}
		child_exiting(data, 1, NULL);
	}
}

void	complex_command(t_minishel *data, t_help *help)
{
	t_command	*cur_cmd;
	int			**tube;

	cur_cmd = data->cmd;
	tube = return_pipe(data, (get_count_cmd(data->cmd)) - 1);
	if (!tube)
		return ;
	help->i = -1;
	while (++(help->i) < (get_count_cmd(data->cmd)))
	{
		if (create_pipe(data, tube, get_count_cmd(data->cmd), help->i) == false)
			break ;
		data->cid[help->i] = fork();
		if (data->cid[help->i] == -1)
			return ((void)malloc_cid_err(data, help->i, error, "fork"));
		g_sig = -11;
		if (data->cid[help->i] == 0)
		{
			builtin_exe(cur_cmd, tube, help->i, data);
			exec_single_cmd(data, cur_cmd);
		}
		close_pipe(help->i, tube);
		cur_cmd = cur_cmd->next;
	}
	child_exiting(data, get_count_cmd(data->cmd), tube);
}

void	exec_single_cmd(t_minishel *data, t_command *command)
{
	char	*path_of_command;

	path_of_command = check_cmd_path(data, command->command);
	if (!path_of_command)
		return (free_old_data(data), exit(data->exit_status));
	data->command_line = own_argv_to_exec(command, data);
	if (execve(path_of_command, data->command_line, list_to_darr(data)) == -1)
		perror("execve");
}