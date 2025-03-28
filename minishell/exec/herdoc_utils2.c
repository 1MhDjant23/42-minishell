//  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣦⣴⣶⣾⣿⣶⣶⣶⣶⣦⣤⣄⠀⠀⠀⠀⠀⠀⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢠⡶⠻⠛⠟⠋⠉⠀⠈⠤⠴⠶⠶⢾⣿⣿⣿⣷⣦⠄⠀⠀⠀         𓐓  herdoc_utils2.c 𓐔           
//  ⠀⠀⠀⠀⠀⢀⠔⠋⠀⠀⠤⠒⠒⢲⠀⠀⠀⢀⣠⣤⣤⣬⣽⣿⣿⣿⣷⣄⠀⠀                                              
//  ⠀⠀⠀⣀⣎⢤⣶⣾⠅⠀⠀⢀⡤⠏⠀⠀⠀⠠⣄⣈⡙⠻⢿⣿⣿⣿⣿⣿⣦⠀ Student: mait-taj <mait-taj@student.1337.ma> 
//  ⢀⠔⠉⠀⠊⠿⠿⣿⠂⠠⠢⣤⠤⣤⣼⣿⣶⣶⣤⣝⣻⣷⣦⣍⡻⣿⣿⣿⣿⡀                                              
//  ⢾⣾⣆⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠉⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇                                              
//  ⠀⠈⢋⢹⠋⠉⠙⢦⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇      Created: 2025/03/28 21:52:31 by mait-taj
//  ⠀⠀⠀⠑⠀⠀⠀⠈⡇⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇      Updated: 2025/03/28 21:52:35 by mait-taj
//  ⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⢀⣾⣿⣿⠿⠟⠛⠋⠛⢿⣿⣿⠻⣿⣿⣿⣿⡿⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⢠⣿⣟⣭⣤⣶⣦⣄⡀⠀⠀⠈⠻⠀⠘⣿⣿⣿⠇⠀                                              
//  ⠀⠀⠀⠀⠀⠱⠤⠊⠀⢀⣿⡿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠘⣿⠏⠀⠀                             𓆩♕𓆪      
//  ⠀⠀⠀⠀⠀⡄⠀⠀⠀⠘⢧⡀⠀⠀⠸⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠐⠋⠀⠀⠀                           𓄂 mait-taj𓆃  
//  ⠀⠀⠀⠀⠀⠘⠄⣀⡀⠸⠓⠀⠀⠀⠠⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                              

#include "../minishell.h"

void	get_exit_status(t_help *help, t_minishel *data)
{
	help->tmp = ft_itoa(data->exit_status);
	help->store = join_expanded_line(help->store, help->tmp);
	free(help->tmp);
	help->tmp = NULL;
	help->i += 2;
}

void	get_expanding(t_help *help, t_minishel *data, char *line)
{
	help->tmp = extr_var(&line[help->i + 1]);
	help->value = get_env(data, help->tmp);
	help->store = join_expanded_line(help->store, help->value);
	help->i += (ft_strlen(help->tmp) + 1);
	free(help->tmp);
	free(help->value);
	help->value = NULL;
	help->tmp = NULL;
}

char	*exp_herdoc(char *line, t_minishel *data, t_help *help)
{
	while (line[help->i] != '\0')
	{
		if (line[help->i] == '$')
		{
			if (line[help->i] == '$' && line[help->i + 1] == '?')
			{
				get_exit_status(help, data);
				continue ;
			}
			else if (line[help->i] == '$' && ft_isalpha(line[help->i + 1]) == 0)
			{
				help->store = join_char(help->store, '$');
				help->i++;
				continue ;
			}
			get_expanding(help, data, line);
		}
		else
		{
			if (line[help->i] == '\0')
				break ;
			help->store = join_char(help->store, line[help->i++]);
		}
	}
	return (help->store);
}

char	*file_path(int x, int y)
{
	char	*file;
	char	*index;
	char	*yy;
	char	*xx;
	char	*str;

	str = "/tmp/her_doc_";
	yy = ft_itoa(y);
	xx = ft_itoa(x);
	index = ft_strjoin(yy, xx);
	file = ft_strjoin(str, index);
	free(index);
	free(yy);
	free(xx);
	return (file);
}

int	reserve_for_herdoc(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd < 0)
	{
		free(file);
		perror("open");
	}
	free(file);
	return (fd);
}
