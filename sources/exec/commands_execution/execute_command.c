/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:03:57 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/17 11:40:30 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
* @brief Executes the command or pipeline received after the parsing
* of the provided command line
*
* @details None at the moment
*
* @param[in] commands : An array of struct s_ncommand that is null terminated
* and that holds, for each of its elements, one command of the provided
* pipeline
* @param[in] env : The structure holding the environment that has been properly
* formatted in an earlier function
*
* @return the status exit code of the command or pipeline provided. Might
* not return if there is one command and this one command is exit.
*/
int	execute_commands(struct s_ncommand *commands, struct s_env *env)
{
	size_t	commands_nb;
	size_t	i;
	int		err;

	commands_nb = tablen(commands, sizeof * commands);
	if (make_pipes(commands) || \
	heredocs(commands, commands_nb, env->env_list))
	{
		clear_fdlist();
		return (1);
	}
	//print_commands(commands);
	/*
	if (make_redirections((commands + 0)->redirs, (commands + 0)->heredocs))
	{
		ft_printf("Wtf bruv, can't even redir ? U really shell ?\n");
		clear_fdlist();
		return (1);
	}
	*/
	//print_fdlist();
	i = 0;
	while (i < commands_nb)
	{
		err = execute_command(commands + i, env);
		ft_printf("The command number %d returned : %d\n", i + 1, err);
		i ++;
	}
	clear_fdlist();
	return (0);
}
