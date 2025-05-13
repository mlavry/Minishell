/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:07:27 by aboutale          #+#    #+#             */
/*   Updated: 2025/05/13 22:43:07 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"





int	isbuiltin(t_data *data)
{
	char *cmd;

	if (!data || !data->cmd || !data->cmd->name)
		return (0);

	cmd = data->cmd->name;

	return (
		ft_strcmp(cmd, "echo") == 0 ||
		ft_strcmp(cmd, "pwd") == 0 ||
		ft_strcmp(cmd, "env") == 0 ||
		ft_strcmp(cmd, "exit") == 0 ||
		ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "unset") == 0
	);
}

void	exec_builtin(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	/* if (!cmd || !cmd->name)
		return (0); */
	if (ft_strcmp(cmd->name, "echo") == 0)
		builtin_echo(data);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd->name, "env") == 0)
		builtin_env(data);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		builtin_exit(data);
	else if (ft_strcmp(cmd->name, "cd") == 0)
		builtin_cd(cmd->args[1], data);
	else if (ft_strcmp(cmd->name, "export") == 0)
		builtin_export(data, cmd);
	else if (ft_strcmp(cmd->name, "unset") == 0)
		builtin_unset(data, cmd);
}

void	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
		perror("cwd");
}

/*
void	antislash(const char *str, int *b_slash, int *i)
{
	int j=0;
	while (str[*i] == '\\')
		{
			(*b_slash)++;
			(*i)++;
		}
		while (j < (*b_slash / 2))
		{
			ft_putchar ('\\');
			j++;
		}
		if (*b_slash % 2 == 1)
		{
			if (str[*i] != '\0')
			{
				if (str[*i] == 'n')
					ft_putchar('n');
				else if (str[*i] == 't')
					ft_putchar('t');
				else
					ft_putchar(str[*i]);
				(*i)++;
			}
		} 
	 	else if (str[*i] != '\0')
		{
			ft_putchar(str[*i]);
			(*i)++;
		}
} 
*/

int	antislash(const char *str, int i)
{
	int	j;
	int	b_slash;

	j = 0;
	b_slash = 0;
	while (str[i] == '\\')
	{
		b_slash++;
		i++;
	}
	while (j < (b_slash / 2))
	{
		ft_putchar ('\\');
		j++;
	}
	if (b_slash % 2 == 1)
	{
		if (str[i] != '\0')
		{
			if (str[i] == 'n')
				ft_putchar('n');
			else if (str[i] == 't')
				ft_putchar('t');
			else
				ft_putchar(str[i]);
			i++;
		}
	}
	else if (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

void	print_antislash(const char *str)
{
	int	i;
	int	j;
	int	b_slash;

	i = 0;
	j = 0;
	while (str[i])
	{
		b_slash = 0;
		i = antislash(str,i);
		/* while (str[i] == '\\')
		{
			b_slash++;
			i++;
		}
		while (j < (b_slash / 2))
		{
			ft_putchar ('\\');
			j++;
		}
		if (b_slash % 2 == 1)
		{
			if (str[i] != '\0')
			{
				if (str[i] == 'n')
					ft_putchar('n');
				else if (str[i] == 't')
					ft_putchar('t');
				else
					ft_putchar(str[i]);
				i++;
			}
		} 
	 	else if (str[i] != '\0')
		{
			ft_putchar(str[i]);
			i++;
		}  */
	}
}



/* void	printescaped(const char *str)
{
	int i;
	int b_slash;
	int j;

	i = 0;
	j = 0;

	while (str[i])
	{
		b_slash = 0;
		while (str[i] == '\\')
		{
			i++;
			b_slash++;
		}

		while (j < (b_slash / 2))
		{
			ft_putchar ('\\');
			j++;
		}
		if(b_slash % 2 == 1)
		{
			if (str[i] != '\0')
			{
				if (str[i] == 'n')
					printf("n");
				else if (str[i] == '\0')
					ft_putchar(str[i]);

			 if (str[i] == '\0') 
				i++;	
			}

		}
		else if (str[i] != '\0')
			{
				ft_putchar(str[i]);
				i++;
			}
	}
} */


/* void echo(t_env *env_list, int i, t_cmd *cmd, t_data *data)
{
    char *value;

    if (cmd->args[i][0] == '$')
    {
        if (cmd->args[i][1] == '\0')
            printf("$");
        else if (cmd->args[i][1] == '?')
        {
            printf("%d", data->exit_code);
            if (cmd->args[i][2] != '\0')
                printf("%s", &cmd->args[i][2]);
        }
        else
        {
            value = getenvp(env_list, cmd->args[i] + 1); // Récupérer la variable d'environnement
            if (value)
                printf("%s", value);
        }
    }
    // Gérer l'anti-slash (\) et le dollar ($) échappés
    else if (cmd->args[i][0] == '\\' && cmd->args[i][1] == '$')
    {
        print_antislash(cmd->args[i]);
    }
    // Gérer les caractères d'échappement spéciaux
    else if (cmd->args[i][0] == '\\')
    {
        if (cmd->args[i][1] == 'n')
            printf("\n");
        else if (cmd->args[i][1] == 't')
            printf("\t");
        else
            print_antislash(cmd->args[i]);  // Cas d'autres séquences échappées
    }
    // Si c'est un argument normal, on l'affiche tel quel
    else
    {
        printf("%s", cmd->args[i]);
    }
} */


/* bool is_a_n_next(char *str)
{
	if ([i][1] == 'n')
} */


void	echo(t_env *env_list, int i, t_cmd *cmd, t_data *data)
{
	char	*value;

	if (cmd->args[i][0] == '$')
	{
		if (cmd->args[i][1] == '\0')
			printf("$");
		else if (cmd->args[i][1] == '?')
		{
			printf("%d", data->exit_code);
			if (cmd->args[i][2] != '\0')
				printf("%s", &cmd->args[i][2]);
		}
		value = getenvp(env_list, cmd->args[i] + 1);
		if (value)
			printf("%s", value);
	}
	else if (cmd->args[i][0] == '\\' && cmd->args[i][1] == '$')
		print_antislash(cmd->args[i]);
	else if (cmd->args[i][0] == '\\')
	{
		if (cmd->args[i][1] == 'n')
		{
			if (cmd->args[i][2] != '\0')
				printf("%s", &cmd->args[i][1]);
			else
				printf("\n");
			/* if (cmd->args[i][2] != '\0')
				printf("%s", cmd->args[i][2]); */
		}
		else if (cmd->args[i][1] == 't')
			printf("\t");
		else
			print_antislash(cmd->args[i]);
	}
	else
		printf("%s", cmd->args[i]);
}

/* void builtin_echo(t_data *data)
{
    t_cmd *cmd = data->cmd;
    char **args = cmd->args;
    int i = 1;
    int newline = 1;

    while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
    {
        i++;
        data->exit_code = 0;
    }
    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (newline && args[1] && args[1][0] == '-' && args[1][1] == 'n')
        newline = 0; 

    if (newline)
        printf("\n");

    data->exit_code = 0;
} */




void	builtin_echo(t_data *data)
{
	int		i;
	int		j;
	int		newline;
	char	**args;
	t_cmd	*cmd;
	t_env	*env_list;

	cmd = data->cmd;
	env_list = data->env;
	i = 1;
	j = 1;
	newline = 1;
	args = cmd->args;

	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		while (args[i][j] == 'n')
		{
			j++;
			data->exit_code = 0;
		}
		if (args[i][j] != '\0')
			break ;
		newline = 0;
		i++;
	}
	while (args[i])
	{
		echo(env_list, i, cmd, data);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
	{
		printf("\n");
		data->exit_code = 0;
	}
} 

void	builtin_exit(t_data *data)
{
	/* t_env	*env_list;
	t_cmd	*cmd;

	env_list = data->env;
	cmd = data->cmd; */

	printf("exit\n");
	free_env_list(data->env);
	free_tab(data->cmd->args);
	exit(0);
}
