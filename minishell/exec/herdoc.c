/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:51:16 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/15 13:58:48 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	run_herdoc(t_minishel *data)
{
	int			x;
	t_command	*cmd;
	t_help		help;

	x = 0;
	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->herdoc)
		{
			init_help(&help);
			if (ft_her_doc(data, cmd, x++, &help) == false)
			{
				free_old_data(data);
				data->exit_status = 1;
				return (false);
			}
		}
		cmd = cmd->next;
	}
	return (true);
}

void	if_multi_herdoc(t_command *cmd)
{
	t_herdoc	*herd;
	int			index;
	int			fd;
	char		*file;

	index = arg_count(cmd->hr_file) - 1;
	file = cmd->hr_file[index];
	herd = cmd->herdoc;
	while (herd && herd->next)
		herd = herd->next;
	fd = open(file, O_RDONLY, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	if (cmd->last_input == HERE_DOC)
		dup2(fd, STDIN_FILENO);
	close(fd);
}

bool	free_file_of_herd(t_minishel *data)
{
	t_command	*cmd;
	int			i;

	cmd = data->cmd;
	while (cmd)
	{
		i = 0;
		if (cmd->herdoc)
		{
			while (cmd->hr_file[i])
			{
				if (access(cmd->hr_file[i], F_OK) == 0)
					unlink(cmd->hr_file[i++]);
			}
		}
		cmd = cmd->next;
	}
	data->exit_status = 1;
	return (false);
}

void	fill_herd(t_minishel *data, int fd, t_herdoc *her_doc)
{
	char	*line;
	char	*tmp;
	t_help	help;

	line = readline("> ");
	while (ft_my_strcmp(line, (her_doc)->delimiter) != 0)
	{
		init_help(&help);
		if (!line)
			break ;
		if ((her_doc)->exp == true && ft_strchr(line, '$'))
		{
			tmp = line;
			line = exp_herdoc(line, data, &help);
			free(tmp);
			tmp = NULL;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	line = NULL;
}

bool	ft_her_doc(t_minishel *data, t_command *cmd, int count, t_help *help)
{
	t_herdoc	*her_doc;
	int			fd;
	int			cid;

	her_doc = cmd->herdoc;
	if (check_name_file(cmd, count, data) == false)
		return (false);
	while (her_doc && g_sig != SIGINT)
	{
		fd = reserve_for_herdoc(file_path(((help->i)++), count));
		if (fd < 0)
			return (free_d_array(cmd->hr_file), free_file_of_herd(data));
		cid = fork();
		g_sig = -11;
		if (cid == 0)
			running_fill(data, fd, her_doc);
		else if (cid != 0)
		{
			if (after_fill_herd(cmd, cid, fd, data) == false)
				return (false);
		}
		her_doc = her_doc->next;
	}
	return (true);
}
