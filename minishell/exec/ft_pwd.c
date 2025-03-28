//  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣦⣴⣶⣾⣿⣶⣶⣶⣶⣦⣤⣄⠀⠀⠀⠀⠀⠀⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢠⡶⠻⠛⠟⠋⠉⠀⠈⠤⠴⠶⠶⢾⣿⣿⣿⣷⣦⠄⠀⠀⠀                𓐓  ft_pwd.c 𓐔           
//  ⠀⠀⠀⠀⠀⢀⠔⠋⠀⠀⠤⠒⠒⢲⠀⠀⠀⢀⣠⣤⣤⣬⣽⣿⣿⣿⣷⣄⠀⠀                                              
//  ⠀⠀⠀⣀⣎⢤⣶⣾⠅⠀⠀⢀⡤⠏⠀⠀⠀⠠⣄⣈⡙⠻⢿⣿⣿⣿⣿⣿⣦⠀ Student: mait-taj <mait-taj@student.1337.ma> 
//  ⢀⠔⠉⠀⠊⠿⠿⣿⠂⠠⠢⣤⠤⣤⣼⣿⣶⣶⣤⣝⣻⣷⣦⣍⡻⣿⣿⣿⣿⡀                                              
//  ⢾⣾⣆⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠉⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇                                              
//  ⠀⠈⢋⢹⠋⠉⠙⢦⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇      Created: 2025/03/28 21:49:58 by mait-taj
//  ⠀⠀⠀⠑⠀⠀⠀⠈⡇⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇      Updated: 2025/03/28 21:50:24 by mait-taj
//  ⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⢀⣾⣿⣿⠿⠟⠛⠋⠛⢿⣿⣿⠻⣿⣿⣿⣿⡿⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⢠⣿⣟⣭⣤⣶⣦⣄⡀⠀⠀⠈⠻⠀⠘⣿⣿⣿⠇⠀                                              
//  ⠀⠀⠀⠀⠀⠱⠤⠊⠀⢀⣿⡿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠘⣿⠏⠀⠀                             𓆩♕𓆪      
//  ⠀⠀⠀⠀⠀⡄⠀⠀⠀⠘⢧⡀⠀⠀⠸⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠐⠋⠀⠀⠀                           𓄂 mait-taj𓆃  
//  ⠀⠀⠀⠀⠀⠘⠄⣀⡀⠸⠓⠀⠀⠀⠠⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                              

#include "../minishell.h"

void	built_pwd(t_minishel *data)
{
	char	*cur_dir;
	char	buffer[PATH_MAX];

	cur_dir = getcwd(buffer, PATH_MAX);
	if (!cur_dir)
	{
		data->exit_status = 1;
		perror("getcwd");
		return ;
	}
	write(STDOUT_FILENO, cur_dir, ft_strlen(cur_dir));
	write(STDOUT_FILENO, "\n", 1);
	data->exit_status = 0;
}

void	reset_wrd_env(t_minishel *data)
{
	t_env	*ev;
	bool	pwd;
	bool	old;

	pwd = false;
	old = false;
	ev = data->env;
	while (ev)
	{
		if (ft_strcmp(ev->name, "PWD") == 0)
			pwd = true;
		if (ft_strcmp(ev->name, "OLDPWD") == 0)
			old = true;
		ev = ev->next;
	}
	if (pwd == false)
		add_node(&data->env, create_node("PWD"));
	if (old == false)
		add_node(&data->env, create_node("OLDPWD"));
}

void	update_working_dir(t_type stat, t_minishel *data)
{
	t_env	*ev;
	char	buf[PATH_MAX];
	char	*var;

	ev = data->env;
	if (OLD == stat)
		var = "OLDPWD";
	else
		var = "PWD";
	reset_wrd_env(data);
	getcwd(buf, PATH_MAX);
	if (buf[0] == '\0')
		return (handl_error("getcwd", 1, data));
	while (ev)
	{
		if (ft_strcmp(var, ev->name) == 0)
		{
			free(ev->value);
			ev->value = NULL;
			ev->value = ft_strdup(buf);
			break ;
		}
		ev = ev->next;
	}
}
