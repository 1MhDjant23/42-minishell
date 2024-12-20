/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:20:27 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/12 12:24:36 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_char(char *s, char c)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (ft_strdup(&c));
	str = malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i++] = c;
	str[i] = '\0';
	free(s);
	s = NULL;
	return (str);
}

char	*join_expanded_line(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*st;

	i = 0;
	j = 0;
	if (!s2)
		return (s1);
	else if (!s1 || s1[0] == '\0')
		return (ft_strdup(s2));
	st = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!st)
	{
		perror("malloc");
		return (NULL);
	}
	i = -1;
	while (s1[++i])
		st[i] = s1[i];
	while (s2[j])
		st[i++] = s2[j++];
	st[i] = '\0';
	free(s1);
	return (st);
}

char	*extr_var(char *line)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] && line[i] != '$' && ft_isalpha(line[i]) != false)
		i++;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '$' && ft_isalpha(line[i]) != false)
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

bool	store_file_name(t_command *cmd, int x)
{
	t_herdoc	*herd;
	char		*file;
	int			i;

	i = 0;
	herd = cmd->herdoc;
	while (herd)
	{
		i++;
		herd = herd->next;
	}
	herd = cmd->herdoc;
	cmd->hr_file = malloc(sizeof(char *) * (i + 1));
	if (!cmd->hr_file)
		return (false);
	i = 0;
	while (herd)
	{
		file = file_path(i, x);
		cmd->hr_file[i++] = ft_strdup(file);
		free(file);
		herd = herd->next;
	}
	cmd->hr_file[i] = NULL;
	return (true);
}
