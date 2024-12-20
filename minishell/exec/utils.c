/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:01:11 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/14 22:49:24 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_str(char *str, t_type type)
{
	int		i;
	char	*st;
	char	*tmp;

	i = 0;
	if (NAME == type)
	{
		while (str[i] && str[i] != '=')
			i++;
		st = malloc(sizeof(char) * i + 1);
		if (!st)
			return (NULL);
		i = -1;
		while (str[++i] && str[i] != '=')
			st[i] = str[i];
		st[i] = '\0';
		return (st);
	}
	else if (VALUE == type)
	{
		tmp = ft_strchr(str, '=');
		return (ft_strdup(tmp));
	}
	return (NULL);
}

char	*join_wit_path(char *path, char *cmd)
{
	char	*n_path;
	char	*fre_path;
	size_t	total;

	total = ft_strlen(path) + ft_strlen(cmd) + 1;
	n_path = malloc(sizeof(char) * total + 1);
	if (!n_path)
		exit(EXIT_FAILURE);
	n_path = ft_strjoin(path, "/");
	fre_path = n_path;
	n_path = ft_strjoin(n_path, cmd);
	free(fre_path);
	return (n_path);
}

int	count_env(t_minishel *data)
{
	t_env	*ev;
	int		i;

	ev = data->env;
	i = 0;
	while (ev)
	{
		i++;
		ev = ev->next;
	}
	return (i);
}

char	**list_to_darr(t_minishel *data)
{
	t_env	*temp;
	char	**d_arr;
	char	*pp;
	int		i;
	int		count;

	i = 0;
	temp = data->env;
	count = count_env(data);
	d_arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!d_arr)
		malloc_cid_err(data, 0, errno, "malloc");
	i = 0;
	while (temp)
	{
		pp = ft_strjoin(temp->name, "=");
		d_arr[i++] = ft_strjoin(pp, temp->value);
		free(pp);
		temp = temp->next;
	}
	d_arr[i] = NULL;
	return (d_arr);
}

int	get_count_cmd(t_command *cmd)
{
	int			count;
	t_command	*head;

	if (!cmd)
		return (0);
	count = 0;
	head = cmd;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}
