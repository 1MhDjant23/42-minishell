//  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣦⣴⣶⣾⣿⣶⣶⣶⣶⣦⣤⣄⠀⠀⠀⠀⠀⠀⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢠⡶⠻⠛⠟⠋⠉⠀⠈⠤⠴⠶⠶⢾⣿⣿⣿⣷⣦⠄⠀⠀⠀            𓐓  exec_utils.c 𓐔           
//  ⠀⠀⠀⠀⠀⢀⠔⠋⠀⠀⠤⠒⠒⢲⠀⠀⠀⢀⣠⣤⣤⣬⣽⣿⣿⣿⣷⣄⠀⠀                                              
//  ⠀⠀⠀⣀⣎⢤⣶⣾⠅⠀⠀⢀⡤⠏⠀⠀⠀⠠⣄⣈⡙⠻⢿⣿⣿⣿⣿⣿⣦⠀ Student: mait-taj <mait-taj@student.1337.ma> 
//  ⢀⠔⠉⠀⠊⠿⠿⣿⠂⠠⠢⣤⠤⣤⣼⣿⣶⣶⣤⣝⣻⣷⣦⣍⡻⣿⣿⣿⣿⡀                                              
//  ⢾⣾⣆⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠉⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇                                              
//  ⠀⠈⢋⢹⠋⠉⠙⢦⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇      Created: 2025/03/28 21:47:33 by mait-taj
//  ⠀⠀⠀⠑⠀⠀⠀⠈⡇⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇      Updated: 2025/03/28 21:47:39 by mait-taj
//  ⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⢀⣾⣿⣿⠿⠟⠛⠋⠛⢿⣿⣿⠻⣿⣿⣿⣿⡿⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⢠⣿⣟⣭⣤⣶⣦⣄⡀⠀⠀⠈⠻⠀⠘⣿⣿⣿⠇⠀                                              
//  ⠀⠀⠀⠀⠀⠱⠤⠊⠀⢀⣿⡿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠘⣿⠏⠀⠀                             𓆩♕𓆪      
//  ⠀⠀⠀⠀⠀⡄⠀⠀⠀⠘⢧⡀⠀⠀⠸⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠐⠋⠀⠀⠀                           𓄂 mait-taj𓆃  
//  ⠀⠀⠀⠀⠀⠘⠄⣀⡀⠸⠓⠀⠀⠀⠠⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                              

#include "../minishell.h"

void	init_fork(t_minishel *data)
{
	int	num_cmd;

	num_cmd = get_count_cmd(data->cmd);
	data->cid = malloc(sizeof(int) * num_cmd);
	if (!data->cid)
		malloc_cid_err(data, 0, error, "malloc");
}

bool	create_pipe(t_minishel *data, int **tub, int num_cmd, int i)
{
	if (i < num_cmd - 1)
	{
		if (pipe(tub[i]) == -1)
		{
			data->exit_status = 1;
			free_old_data(data);
			perror("pipe");
			return (false);
		}
	}
	return (true);
}

void	manage_precedence(t_minishel *data, t_command *cmd)
{
	signals_hand(child);
	if (cmd->herdoc)
		if_multi_herdoc(cmd);
	if (cmd->redirect)
	{
		if (ft_redirection(cmd) < 0)
		{
			free_old_data(data);
			data->exit_status = 1;
			perror("open");
			exit(EXIT_FAILURE);
		}
		redirect_to(cmd);
	}
}

void	child_exiting(t_minishel *data, int n, int **pip)
{
	int	status;
	int	i;

	i = 0;
	while (i < n)
	{
		if (waitpid(data->cid[i], &status, 0) == -1)
		{
			perror("waitpid");
			free_old_data(data);
			exit(1);
		}
		i++;
	}
	if (WIFEXITED(status) == true)
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) == true)
		data->exit_status = WTERMSIG(status) + 128;
	if (data->exit_status == 131)
		printf("Quit: 3\n");
	free_pipe(pip, (get_count_cmd(data->cmd) - 1));
	free_old_data(data);
}

char	**own_argv_to_exec(t_command *command, t_minishel *data)
{
	int		len;
	int		j;
	char	**av;

	j = 0;
	len = lenght(command);
	av = malloc(sizeof(char *) * len);
	if (!av)
	{
		free_old_data(data);
		data->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	av[j++] = command->command;
	if (command->argument)
	{
		while (j < len - 1)
		{
			av[j] = command->argument[j - 1];
			j++;
		}
	}
	av[j] = NULL;
	return (av);
}
