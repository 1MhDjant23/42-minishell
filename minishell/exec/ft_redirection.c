/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:30:36 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/12 21:32:48 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_in(t_command *cmd)
{
	t_redir	*redir;
	t_redir	*save;

	redir = cmd->redirect;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			save = redir;
		redir = redir->next;
	}
	if (save)
	{
		save->fd = open(save->file, O_RDONLY, 0644);
		if (save->fd < 0)
			perror("open");
		if (cmd->last_input == REDIR_IN && check_if_builtins(cmd) == false)
			dup2(save->fd, STDIN_FILENO);
		close(save->fd);
	}
}

void	d_redir_out(t_command *cmd)
{
	t_redir	*redir;
	t_redir	*save;

	redir = cmd->redirect;
	while (redir)
	{
		if (redir->type == APEND)
			save = redir;
		redir = redir->next;
	}
	if (save)
	{
		save->fd = open(save->file, O_WRONLY | O_APPEND, 0644);
		if (save->fd < 0)
			perror("open");
		dup2(save->fd, STDOUT_FILENO);
		close(save->fd);
	}
}

void	redir_out(t_command *cmd)
{
	t_redir	*redir;
	t_redir	*save;

	redir = cmd->redirect;
	while (redir)
	{
		if (redir->type == REDIR_OUT)
			save = redir;
		redir = redir->next;
	}
	if (save)
	{
		save->fd = open(save->file, O_RDWR | O_TRUNC, 0644);
		if (save->fd < 0)
		{
			perror("open");
		}
		dup2(save->fd, STDOUT_FILENO);
		close(save->fd);
	}
}

void	redirect_to(t_command *cmd)
{
	t_redir		*redir;
	bool		in;
	bool		out;
	bool		app;

	redir = cmd->redirect;
	while (redir)
	{
		if (redir->type == REDIR_IN && in != true)
		{
			in = true;
			redir_in(cmd);
		}
		else if (redir->type == REDIR_OUT && out != true)
		{
			out = true;
			redir_out(cmd);
		}
		else if (redir->type == APEND && app != true)
		{
			app = true;
			d_redir_out(cmd);
		}
		redir = redir->next;
	}
}

int	ft_redirection(t_command *cmd)
{
	t_redir	*redir;

	redir = cmd->redirect;
	while (redir)
	{
		if (redir->type == REDIR_OUT)
			redir->fd = open(redir->file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else if (redir->type == REDIR_IN)
			redir->fd = open(redir->file, O_RDONLY, 0644);
		else if (redir->type == APEND)
			redir->fd = open(redir->file, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (redir->fd < 0)
			return (redir->fd);
		close(redir->fd);
		redir = redir->next;
	}
	return (1);
}
