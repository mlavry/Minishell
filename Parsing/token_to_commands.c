/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:28:02 by mlavry            #+#    #+#             */
/*   Updated: 2025/05/05 23:15:40 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int handle_cmd(t_cmd **head, t_cmd **cur, t_token *tokens)
{
    t_cmd   *new;

    new = ft_calloc (1, sizeof(t_cmd));
    if (!new)
        return (0);
    new->name = ft_strdup(tokens->str);
    if (!new->name)
    {
        free(new);
        return (0);   
    }
    new->fd_in = STDIN_FILENO;
    new->fd_out = STDOUT_FILENO;
    if (!add_args(&new->args, new->name))
    {
        free(new->name);
        free(new);
        return (0);
    }
    if (!(*head))
        (*head) = new;
    else
        (*cur)->next = new;
    (*cur) = new;
    return (1);
}

int handle_arg(t_cmd *cur, t_token *token)
{
    if (!cur)
        return (0);
    if (!add_args(&cur->args, token->str))
        return (0);
    return (1);
}

int handle_pipe(t_cmd **cur)
{
    if (!cur || !*cur)
        return (0);
    return (1);
}

t_cmd   *tokens_to_commands(t_token *tokens)
{
    t_cmd   *head;
    t_cmd   *cur;

    head = NULL;
    cur = NULL;
    while (tokens)
    {
        if (tokens->type == CMD)
        {
            if (!handle_cmd(&head, &cur, tokens))
                return (NULL);
        }
        if (tokens->type == ARG)
        {
            if (!handle_arg(cur, tokens))
                return (NULL);
        }
        if (tokens->type == PIPE)
        {
            if (!handle_pipe(&cur))
                return (NULL);
        }
        tokens = tokens->next;
    }
    return (head);
}

/*static t_token *new_token(char *s, int type)
{
    t_token *t = malloc(sizeof *t);
    if (!t) return NULL;
    t->str  = strdup(s);
    t->type = type;
    t->sq = t->dq = false;
    t->next = t->prev = NULL;
    return t;
}

static t_token *chain_tokens(char *arr[], int types[], int n)
{
    t_token *head = NULL, *cur = NULL;
    for (int i = 0; i < n; i++)
    {
        t_token *t = new_token(arr[i], types[i]);
        if (!head) head = t;
        else        cur->next = t, t->prev = cur;
        cur = t;
    }
    return head;
}

static void print_cmds(t_cmd *c)
{
    int idx;
    while (c)
    {
        printf("=== Command: %s ===\n", c->name);
        for (idx = 0; c->args && c->args[idx]; idx++)
            printf("  arg[%d]: %s\n", idx, c->args[idx]);
        printf("  fd_in = %d, fd_out = %d\n", c->fd_in, c->fd_out);
        c = c->next;
    }
}

int main(void)
{
    // --- TEST 1 : ls -l ---    
    {
        char *words[] = {"ls","-l"};
        int   typs[] = {CMD, ARG};
        t_token *tok = chain_tokens(words, typs, 2);
        t_cmd   *cmd = tokens_to_commands(tok);
        printf("\nTest 1: \"ls -l\"\n");
        print_cmds(cmd);
    }

    // --- TEST 2 : echo hello world ---
    {
        char *words[] = {"echo","hello","world"};
        int   typs[] = {CMD, ARG, ARG};
        t_token *tok = chain_tokens(words, typs, 3);
        t_cmd   *cmd = tokens_to_commands(tok);
        printf("\nTest 2: \"echo hello world\"\n");
        print_cmds(cmd);
    }

    // --- TEST 3 : ps aux | grep root ---
    {
        char *words[] = {"ps","aux","|","grep","root"};
        int   typs[] = {CMD, ARG, PIPE, CMD, ARG};
        t_token *tok = chain_tokens(words, typs, 5);
        t_cmd   *cmd = tokens_to_commands(tok);
        printf("\nTest 3: \"ps aux | grep root\"\n");
        print_cmds(cmd);
    }

    // --- TEST 4 : env | sort | uniq ---
    {
        char *words[] = {"env","|","sort","|","uniq"};
        int   typs[] = {CMD, PIPE, CMD, PIPE, CMD};
        t_token *tok = chain_tokens(words, typs, 5);
        t_cmd   *cmd = tokens_to_commands(tok);
        printf("\nTest 4: \"env | sort | uniq\"\n");
        print_cmds(cmd);
    }

    return 0;
}*/
