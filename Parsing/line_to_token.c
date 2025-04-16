/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:47:49 by mlavry            #+#    #+#             */
/*   Updated: 2025/04/16 22:58:52 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	quote_choice(bool *sq, bool *dq, char c)
{
	if ((c == '\'' || c == '"') && !*sq && !*dq)
	{
		if (c == '\'' && !*dq)
			*sq = true;
		if (c == '"' && !*sq)
			*dq = true;
	}
	else if (c == '\'' || c == '"')
	{
		if (c == '\'' && !*dq)
			*sq = false;
		if (c == '"' && !*sq)
			*dq = false;
	}
}

int	count_tokens(char *line)
{
	int		start;
	int		i;
	int		count;
	bool	sq;
	bool	dq;

	start = 0;
	i = 0;
	count = 0;
	sq = false;
	dq = false;
	while (line[i])
	{
		quote_choice(&sq, &dq, line[i]);
		if (!sq && !dq)
		{
			if (is_space(line[i]))
			{
				if (i > start)
					count++;
				while (is_space(line[i]))
					i++;
				start = i;
				continue ;
			}
			if (is_operator(line[i]))
			{
				if (i > start)
					count++;
				while (is_operator(line[i]))
					i++;
				count++;
				start = i;
				continue ;
			}
		}
		i++;
	}
	if (i > start)
		count++;
	return (count);
}

/* char	**line_to_token(char *line)
{
	char	**tokens;	
	int		start;
	int		i;
	int		token_index;
	bool	sq;
	bool	dq;

	start = 0;
	i = 0;
	token_index = 0;
	sq = false;
	dq = false;
	while (line[i])
	{
		quote_choice(&sq, &dq, line[i]);
		if (!dq && !sq)
		{
			
		}
	}
} */

//----------------------------TEST COUNT TOKENS-----------------------------------

/* int main(void)
{
	char *line1 = "echo bonjour >>> < <<<";
	char *line2 = "echo \"bonjour le monde\"";
	char *line3 = "cat fichier > sortie";
	char *line4 = "echo \"bonjour > le\" >> fichier";
	char *line5 = "grep main.c | wc -l";

	printf("Test 1: \"%s\" --> %d tokens\n", line1, count_tokens(line1));
	printf("Test 2: \"%s\" --> %d tokens\n", line2, count_tokens(line2));
	printf("Test 3: \"%s\" --> %d tokens\n", line3, count_tokens(line3));
	printf("Test 4: \"%s\" --> %d tokens\n", line4, count_tokens(line4));
	printf("Test 5: \"%s\" --> %d tokens\n", line5, count_tokens(line5));
	printf("Test 6: \"\" --> %d tokens\n", count_tokens(""));
	printf("Test 7: \"echo     hello\" --> %d tokens\n", count_tokens("echo     hello"));
	printf("Test 8: \"echo 'bonjour\" --> %d tokens\n", count_tokens("echo 'bonjour"));
	printf("Test 9: \"cat < file | grep test >> out.txt\" --> %d tokens\n",
	count_tokens("cat < file | grep test >> out.txt"));

	return (0);
} */
