/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:36:00 by ysouhail          #+#    #+#             */
/*   Updated: 2024/12/12 18:11:15 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redir(t_elem *str)
{
	if (str->type == REDIR_IN || str->type == REDIR_OUT 
		|| str->type == APEND || str->type == HERE_DOC)
	{
		return (true);
	}
	return (false);
}

void	check_last_redir(t_elem *list, t_command *cmd)
{
	t_elem	*serch;

	serch = list;
	cmd->out_exist = false;
	cmd->last_input = NON;
	while (serch)
	{
		if (serch->type == APEND || serch->type == REDIR_OUT)
		{
			cmd->out_exist = true;
		}
		if (serch->type == REDIR_IN || serch->type == HERE_DOC)
		{
			cmd->last_input = serch->type;
		}
		if (serch && serch->type == PIPE_LINE)
		{
			break ;
		}
		serch = serch->next;
	}
}

void	arg_fuller(char *str, t_command *cmds)
{
	char	**tmp;

	tmp = NULL;
	if (!str)
		return ;
	if (cmds->argument == NULL) 
	{
		cmds->argument = malloc(sizeof(char *) * 2);
		if (cmds->argument == NULL)
			return ;
		cmds->argument[0] = str_dup(str);
		cmds->argument[1] = NULL;
	}
	else 
	{
		tmp = cmds->argument;
		cmds->argument = big_join(cmds->argument, str);
		free(tmp);
	}
}

char	**big_join(char **argument, char *arg)
{
	char	**newargument;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (argument[i])
	{
		count++;
		i++;
	}
	i = -1;
	newargument = malloc(sizeof(char *) * (count + 2));
	while (argument[++i])
		newargument[i] = argument[i];
	newargument[i] = str_dup(arg);
	i++;
	newargument[i] = NULL;
	return (newargument);
}
