//  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣦⣴⣶⣾⣿⣶⣶⣶⣶⣦⣤⣄⠀⠀⠀⠀⠀⠀⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢠⡶⠻⠛⠟⠋⠉⠀⠈⠤⠴⠶⠶⢾⣿⣿⣿⣷⣦⠄⠀⠀⠀             𓐓  minishell.c 𓐔           
//  ⠀⠀⠀⠀⠀⢀⠔⠋⠀⠀⠤⠒⠒⢲⠀⠀⠀⢀⣠⣤⣤⣬⣽⣿⣿⣿⣷⣄⠀⠀                                              
//  ⠀⠀⠀⣀⣎⢤⣶⣾⠅⠀⠀⢀⡤⠏⠀⠀⠀⠠⣄⣈⡙⠻⢿⣿⣿⣿⣿⣿⣦⠀ Student: mait-taj <mait-taj@student.1337.ma> 
//  ⢀⠔⠉⠀⠊⠿⠿⣿⠂⠠⠢⣤⠤⣤⣼⣿⣶⣶⣤⣝⣻⣷⣦⣍⡻⣿⣿⣿⣿⡀                                              
//  ⢾⣾⣆⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠉⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇                                              
//  ⠀⠈⢋⢹⠋⠉⠙⢦⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇      Created: 2025/03/28 21:52:58 by mait-taj
//  ⠀⠀⠀⠑⠀⠀⠀⠈⡇⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇      Updated: 2025/03/28 21:53:02 by mait-taj
//  ⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⢀⣾⣿⣿⠿⠟⠛⠋⠛⢿⣿⣿⠻⣿⣿⣿⣿⡿⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⢠⣿⣟⣭⣤⣶⣦⣄⡀⠀⠀⠈⠻⠀⠘⣿⣿⣿⠇⠀                                              
//  ⠀⠀⠀⠀⠀⠱⠤⠊⠀⢀⣿⡿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠘⣿⠏⠀⠀                             𓆩♕𓆪      
//  ⠀⠀⠀⠀⠀⡄⠀⠀⠀⠘⢧⡀⠀⠀⠸⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠐⠋⠀⠀⠀                           𓄂 mait-taj𓆃  
//  ⠀⠀⠀⠀⠀⠘⠄⣀⡀⠸⠓⠀⠀⠀⠠⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                              

#include "../minishell.h"

void	add_node(t_env **head, t_env *new)
{
	t_env	*temp;

	if (!head || !new)
		return ;
	temp = *head;
	if (!*head)
	{
		*head = new;
		return ;
	}
	while (temp && temp->next)
		temp = temp->next;
	temp->next = new;
}

t_env	*create_node(char *content)
{
	t_env	*node;
	char	*name;
	char	*value;

	node = malloc(sizeof(t_env));
	if (!node)
		exit(EXIT_FAILURE);
	name = extract_str(content, NAME);
	value = extract_str(content, VALUE);
	node->name = name;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	set_env(t_minishel *data, char **ev)
{
	int	i;

	i = 0;
	data->env = create_node(ev[i]);
	while (ev[++i])
		add_node(&data->env, create_node(ev[i]));
}

void	running_fill(t_minishel *data, int fd, t_herdoc *her)
{
	signal(SIGINT, child_handler);
	fill_herd(data, fd, her);
	exit(0);
}

bool	after_fill_herd(t_command *cmd, int cid, int fd, t_minishel *data)
{
	if (g_sig == SIGINT)
	{
		check_open_herd(data);
		clean_after_signal(cmd->hr_file);
		if (cmd->hr_file)
			free_d_array(cmd->hr_file);
		kill(cid, SIGINT);
		return (false);
	}
	waitpid(cid, NULL, 0);
	close(fd);
	if (g_sig == SIGINT)
	{
		check_open_herd(data);
		g_sig = 0;
		return (false);
	}
	return (true);
}
