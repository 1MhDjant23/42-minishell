/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:04:34 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/15 11:31:34 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../minishell.h"

/*_____________ Struct For Parser ________________________________________*/
typedef struct s_elem		t_elem;
typedef struct s_minishel	t_minishel;

typedef struct s_help
{
	char	*value;
	char	*tmp;
	char	*store;
	int		i;
}			t_help;

typedef enum e_token
{
	WORD = 0,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	SING_Q = '\'',
	DOBL_Q = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	TAP = '\t',
	HERE_DOC,
	REDIRECTIN,
	APEND,
	NON,
}	t_token;

typedef enum e_state
{
	IN_DQUOTE,
	IN_SIQUOTE,
	GENERAL,
}	t_state;

typedef struct s_flags
{
	bool	com;
	bool	sp;
	char	*sub;
}			t_flags;

struct s_elem
{
	char			*content;
	int				len;
	enum e_token	type;
	enum e_state	state;
	t_elem			*next;
};

typedef struct s_stax
{
	int	count;
	int	x;
	int	pip;
	int	redir;
}	t_stax;

typedef struct t_list
{
	t_elem		*head;
	char		**env;
	t_minishel	*data;
	t_elem		*end;
	int			size;
}	t_list;

typedef struct s_util
{
	bool	com;
	bool	sp;
	char	*sub;
}	t_util;

/*___________ Struct Fot Execution ______________________*/

typedef enum s_type
{
	NAME,
	VALUE,
	OLD,
	PWD,
	PATH,
	EXEC,
	simple,
	complex,
	REDIRE,
	HERDOC,
	alloc,
	error,
	clean,
	built,
	child,
	parent,
}				t_type;

typedef struct s_herdoc
{
	t_token			type;
	char			*delimiter;
	bool			exp;
	char			*fullname;
	int				fd;
	struct s_herdoc	*next;
}	t_herdoc;

typedef struct s_redir
{
	t_token			type;
	char			*file;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_command
{
	char				*command;
	char				**argument;
	char				**hr_file;
	int					*prv_fd;
	t_herdoc			*herdoc;
	t_redir				*redirect;
	bool				out_exist;
	t_token				last_input;	
	struct s_command	*next;

}				t_command;

struct s_minishel
{
	char				**command_line;
	char				**path;
	int					arg_counter;
	int					*cid;
	int					exit_status;
	t_env				*env;
	t_stax				*yssf;
	t_command			*cmd;
};
#endif