/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:05:37 by ysouhail          #+#    #+#             */
/*   Updated: 2024/12/15 14:59:51 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_sig = 0;

void	handle_c(int x)
{
	if (x == SIGINT)
	{
		if (g_sig != -11)
		{
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		g_sig = SIGINT;
	}
}

void	signals_hand(t_type stat)
{
	if (stat == parent)
	{
		signal(SIGINT, handle_c);
		signal(SIGQUIT, SIG_IGN);
	}
	if (stat == child)
	{
		signal(SIGINT, child_handler);
		signal(SIGQUIT, child_handler);
	}
}

void	ft_readline(char *line, t_minishel data)
{
	t_list	*list;

	list = NULL;
	while (1)
	{
		g_sig = 0;
		signals_hand(parent);
		line = readline(""BRED"$"RSET"");
		if (!line)
		{
			printf("exit\n");
			exit(data.exit_status);
		}
		if (!is_space(line))
		{
			list = ft_lexer(line);
			sysntax_error(list, &data);
		}
		if (line[0])
			add_history(line);
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_minishel	data;

	line = NULL;
	(void)av;
	if (ac != 1)
		return (1);
	if (!env || env[0] == NULL)
		data.env = NULL;
	else
		set_env(&data, env);
	ft_readline(line, data);
	clear_history();
	return (data.exit_status);
}
