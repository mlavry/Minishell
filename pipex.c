/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 21:07:32 by aboutale          #+#    #+#             */
/*   Updated: 2025/03/26 21:07:33 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int	i;

	i = 0;
	pipex->infile = open(argv[1], O_RDONLY);
	/* if (pipex->infile < 0)
		return (write(2, "Error opening infile", 20), 0);  */
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile < 0)
		return (write(2, "Error opening outfile", 21), 0);
	pipex->n_commands = argc - 3;
	pipex->cmds = malloc((pipex->n_commands + 1) * sizeof(char *));
	if (!pipex->cmds)
		return (write(2, "Error malloc", 12), 0);
	while (i <= pipex->n_commands)
	{
		pipex->cmds[i] = NULL;
		i++;
	}
	allocatecommands(pipex, argv);
	pipex->envp = envp;
	pipex->paths = ft_split(findpath(envp), ':');
	if (!pipex->paths)
		return (free_pipex(pipex), 0);
	return (1);
}

void	execute(t_pipex *pipex, int cmd_index)
{
	char	**args;

	if (!pipex->cmds[cmd_index] || pipex->cmds[cmd_index][0] == '\0')
	{
		perror("Invalid commands (NULL)");
		exit(EXIT_FAILURE);
	}
	args = ft_split(pipex->cmds[cmd_index], ' ');
	if (!args || !args[0])
	{
		perror("command not found ");
		free_split(args);
		free_paths(pipex);
		free_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	get_path(pipex, args);
	if (execve(args[0], args, pipex->envp) == -1)
	{
		perror(args[0]);
		free_split(args);
		free_paths(pipex);
		free_pipex(pipex);
		exit(EXIT_FAILURE);
	}
}

void	childrenprocess(t_pipex *pipex, int i)
{
	if (i == 0)
	{
		dup2(pipex->infile, STDIN_FILENO);
		if (pipex->infile > 0)
			close(pipex->infile);
	}
	else
	{
		dup2(pipex->pipes[(i - 1) % 2][0], STDIN_FILENO);
		close(pipex->pipes[(i - 1) % 2][0]);
		close(pipex->pipes[(i - 1) % 2][1]);
	}
	if (i == pipex->n_commands - 1)
	{
		dup2(pipex->outfile, STDOUT_FILENO);
		if (pipex->outfile > 0)
			close(pipex->outfile);
	}
	else
	{
		dup2(pipex->pipes[i % 2][1], STDOUT_FILENO);
		close(pipex->pipes[i % 2][0]);
		close(pipex->pipes[i % 2][1]);
	}
	closeunusedpipes();
}

void	parentprocess(t_pipex *pipex, int i)
{
	if (i > 0)
	{
		close(pipex->pipes[(i - 1) % 2][0]);
		close(pipex->pipes[(i - 1) % 2][1]);
	}
}

void	forkprocess(t_pipex *pipex)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i < pipex->n_commands)
	{
		if (i < pipex->n_commands - 1 && pipe(pipex->pipes[i % 2]) < 0)
		{
			free_pipex(pipex);
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("Fork error");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			childrenprocess(pipex, i);
			execute(pipex, i);
		}
		else
			parentprocess(pipex, i);
	}
}
