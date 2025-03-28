//  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣦⣴⣶⣾⣿⣶⣶⣶⣶⣦⣤⣄⠀⠀⠀⠀⠀⠀⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢠⡶⠻⠛⠟⠋⠉⠀⠈⠤⠴⠶⠶⢾⣿⣿⣿⣷⣦⠄⠀⠀⠀                𓐓  export.c 𓐔           
//  ⠀⠀⠀⠀⠀⢀⠔⠋⠀⠀⠤⠒⠒⢲⠀⠀⠀⢀⣠⣤⣤⣬⣽⣿⣿⣿⣷⣄⠀⠀                                              
//  ⠀⠀⠀⣀⣎⢤⣶⣾⠅⠀⠀⢀⡤⠏⠀⠀⠀⠠⣄⣈⡙⠻⢿⣿⣿⣿⣿⣿⣦⠀ Student: mait-taj <mait-taj@student.1337.ma> 
//  ⢀⠔⠉⠀⠊⠿⠿⣿⠂⠠⠢⣤⠤⣤⣼⣿⣶⣶⣤⣝⣻⣷⣦⣍⡻⣿⣿⣿⣿⡀                                              
//  ⢾⣾⣆⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠉⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇                                              
//  ⠀⠈⢋⢹⠋⠉⠙⢦⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇      Created: 2025/03/28 21:48:30 by mait-taj
//  ⠀⠀⠀⠑⠀⠀⠀⠈⡇⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇      Updated: 2025/03/28 21:48:42 by mait-taj
//  ⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⢀⣾⣿⣿⠿⠟⠛⠋⠛⢿⣿⣿⠻⣿⣿⣿⣿⡿⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⢠⣿⣟⣭⣤⣶⣦⣄⡀⠀⠀⠈⠻⠀⠘⣿⣿⣿⠇⠀                                              
//  ⠀⠀⠀⠀⠀⠱⠤⠊⠀⢀⣿⡿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠘⣿⠏⠀⠀                             𓆩♕𓆪      
//  ⠀⠀⠀⠀⠀⡄⠀⠀⠀⠘⢧⡀⠀⠀⠸⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠐⠋⠀⠀⠀                           𓄂 mait-taj𓆃  
//  ⠀⠀⠀⠀⠀⠘⠄⣀⡀⠸⠓⠀⠀⠀⠠⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                              

#include "../minishell.h"

void	display_ex(t_minishel *data)
{
	t_env	*ev;

	ev = data->env;
	while (ev)
	{
		if (!ev->value)
			printf("declare -x %s\n", ev->name);
		else if (ev->name && ev->value)
		{
			write(STDOUT_FILENO, "declare -x ", 11);
			write(STDOUT_FILENO, ev->name, ft_strlen(ev->name));
			write(STDOUT_FILENO, "=\"", 2);
			write(STDOUT_FILENO, ev->value, ft_strlen(ev->value));
			write(STDOUT_FILENO, "\"", 1);
			write(STDOUT_FILENO, "\n", 1);
		}
		ev = ev->next;
	}
	data->exit_status = 0;
}

bool	check_to_set_value(char *name, char *value, t_minishel *data)
{
	t_env	*env;
	bool	up;

	up = false;
	env = data->env;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			if (value)
			{
				free(env->value);
				env->value = ft_strdup(value);
			}
			up = true;
			break ;
		}
		env = env->next;
	}
	return (up);
}

void	update_env(t_minishel *data, t_command *cmd)
{
	char	*name;
	char	*value;
	bool	up;
	int		i;

	i = -1;
	while (cmd->argument[++i])
	{
		if (check_arg(cmd->argument[i], data) == false)
			continue ;
		name = extract_str(cmd->argument[i], NAME);
		value = extract_str(cmd->argument[i], VALUE);
		if (!value)
			up = check_to_set_value(name, NULL, data);
		else
			up = check_to_set_value(name, value, data);
		if (up == false)
			add_node(&data->env, create_node(cmd->argument[i]));
		free(name);
		free(value);
	}
}

bool	check_arg(char *arg, t_minishel *data)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[0]) == false && arg[0] != '_'
		&& arg[0] != ' ' && arg[0] != '\t')
	{
		data->exit_status = 1;
		return (write(2, "minishell: export: not a valid identifier\n", 42), 0);
	}
	while (arg[i] && arg[i] != '=')
	{
		if (special_char(arg[i]) == true)
		{
			data->exit_status = 1;
			write(2, "minishell: export: not a valid identifier\n", 42);
			return (false);
		}
		i++;
	}
	return (true);
}

void	built_export(t_minishel *data, t_command *cmd)
{
	if (!cmd->argument || !cmd->argument[0] || cmd->argument[0][0] == '#')
		display_ex(data);
	else
		update_env(data, cmd);
}
