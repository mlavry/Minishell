/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:07:27 by aboutale          #+#    #+#             */
/*   Updated: 2025/03/26 17:07:29 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isbuiltin(t_cmd *cmd, t_env *env_list)
{
 	if (!cmd || !cmd->name)
        return (0);

	if (ft_strcmp(cmd->name, "echo") == 0)
		builtin_echo(cmd, env_list);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		builtin_pwd(cmd);
	else if (ft_strcmp(cmd->name, "env") == 0)
		builtin_env(env_list);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		builtin_exit(cmd);
	else if (ft_strcmp(cmd->name, "cd") == 0)
		builtin_cd(cmd->args[1]);
	else if (ft_strcmp(cmd->name, "export") == 0)
		builtin_export(env_list, cmd);
	/*else if (ft_strcmp(cmd->name, "unset") == 0)
		builtin_unset(cmd); */
	else
		return (0);
	return (1);
}

void	builtin_pwd(t_cmd *cmd)
{
	(void)cmd;
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

void	builtin_echo(t_cmd *cmd, t_env *env_list)
{
	int i;
	int j = 1;
	int newline = 1;
	char *value;

	i = 1;
	char **args = cmd->args;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0') // Si autre chose que "n" après, on arrête
			break ;
		newline = 0;
		i++;
	}
	while (args[i])
	{

		if (args[i][0] == '$') // Si c'est une variable d'environnement
		{
			value = getenvp(env_list, args[i] + 1); // Enlever le '$'
			if (value)
				printf("%s", value);
		}
		else
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

void	builtin_exit(t_cmd *cmd)
{
	(void)cmd;
	printf("exit\n");
	exit(0);

}

void	builtin_env( t_env *env_list)
{
	while (env_list)
	{
		printf("%s=%s\n", env_list->name, env_list->value);
		env_list = env_list->next;
	}
}

void	builtin_cd(char *newpath)
{
	char	path[1024];


	if (newpath == NULL)
	{
		newpath = getenv("HOME");
		chdir("/home");
	}

	if (access(newpath, F_OK) != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", newpath);
		return ;
	}
	getcwd(path, sizeof(path));
	chdir(newpath);
}


/* void builtin_export(t_env *env_list, t_cmd *cmd)
{
    char **args;
    t_env *current;
    int found = 0;

    args = cmd->args;
    current = env_list;

    printf("Exporting: %s\n", args[0]);

    while (current) {
        printf("Checking: %s\n", current->name);
        if (ft_strcmp(args[0], current->name) == 0) {
            printf("Found existing variable, updating value.\n");
            current->value = args[1] ? args[1] : "";  // Si args[1] est NULL, assigner une chaîne vide
            found = 1;
            break;
        }
        current = current->next;
    }

    if (!found) {
        t_env *newvar = malloc(sizeof(t_env));
        if (!newvar) {
            printf("Memory allocation failed\n");
            return;
        }
        newvar->name = args[0];
        newvar->value = args[1] ? args[1] : "";  // Si args[1] est NULL, assigner une chaîne vide
        newvar->next = NULL;

        // Ajouter la nouvelle variable à la fin de la liste chaînée
        if (env_list == NULL) {
            env_list = newvar;
            printf("Added new variable as the first element.\n");
        } else {
            current = env_list;
            while (current->next) {
                current = current->next;
            }
            current->next = newvar;
            printf("Added new variable at the end of the list.\n");
        }
    }
} */



/* void	builtin_export(t_env *env_list, t_cmd *cmd)
{
	char	**args;
	t_env 	*current;
	int found;

	found = 0;


	args = cmd->args;
	current = env_list;

	while(current)
	{
		if (ft_strcmp(args[0], current->name) == 0)
		{
			current->value = args[1] ? args[1] : ""; 
			found = 1;
			break ;
		}
		current = current->next;
	}
	if (!found)
	{
		t_env *newvar = malloc(sizeof(t_env));
		if(!newvar)
			return ;

		newvar->name = args[0];
		newvar->value = args[1] ? args[1] : "";
		newvar->next = NULL;

		while(current->next)
			current = current->next;
		current->next = newvar;
	}
} */

/* void	builtin_unset()
{





} */