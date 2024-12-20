/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:29:41 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/15 13:08:21 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_unset_arg(char *var, t_minishel *data)
{
	if (var[0] == '_')
		return (true);
	if (ft_isalpha(var[0]) == false)
	{
		data->exit_status = 1;
		write(STDERR_FILENO, "minishell: unset: not a valid identifier\n", 41);
		return (false);
	}
	return (true);
}

void	remove_node_unset(t_env **node)
{
	free((*node)->name);
	free((*node)->value);
	(*node)->name = NULL;
	(*node)->value = NULL;
	free(*node);
	*node = NULL;
}

void	find_environment_variable(t_env **env, char *name, t_minishel *data)
{
	t_env	*node;
	t_env	*prev;

	node = *env;
	prev = NULL;
	while (node && ft_strcmp(name, node->name) != 0)
	{
		prev = node;
		node = node->next;
	}
	if (node)
	{
		if (node->next)
			prev->next = node->next;
		else
			prev->next = NULL;
		remove_node_unset(&node);
	}
	data->exit_status = 0;
}

void	built_unset(t_minishel *data, char **arg)
{
	t_env	*tmp;
	int		i;

	i = -1;
	if (!arg)
		return ;
	while (arg[++i])
	{
		if (check_unset_arg(arg[i], data) == false)
			continue ;
		tmp = data->env;
		if (data->env && ft_strcmp(arg[i], (data->env)->name) == 0)
		{
			data->env = tmp->next;
			remove_node_unset(&tmp);
		}
		else
		{
			find_environment_variable(&data->env, arg[i], data);
		}
	}
	data->exit_status = 0;
}
