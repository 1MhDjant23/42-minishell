/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:44:20 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/14 21:39:35 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_env(t_minishel *data)
{
	t_env	*ev;

	ev = data->env;
	while (ev)
	{
		if (ev && ev->value && ev->name)
			printf("%s=%s\n", ev->name, ev->value);
		ev = ev->next;
	}
	data->exit_status = 0;
}

char	*get_env(t_minishel *data, char *var)
{
	t_env	*ev;

	ev = data->env;
	if (!ev)
		return (NULL);
	while (ev)
	{
		if (ft_strcmp(var, ev->name) == 0)
			return (ft_strdup(ev->value));
		ev = ev->next;
	}
	return (NULL);
}
