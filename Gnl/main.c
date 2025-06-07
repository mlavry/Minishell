/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: aboutale <aboutale@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/20 12:21:47 by aboutale		  #+#	#+#			 */
/*   Updated: 2024/11/22 18:14:11 by aboutale		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int main()
{
	int fd = open("gnlfile", O_RDONLY); 
	int fd2 = open("gnlfile", O_RDONLY);
	char *line;
	char *line2;
   // size_t readbytes;
   // line = get_next_line(fd);
   // readbytes = read(fd, line, BUFFER_SIZE);
	if (fd == -1)
	{
		perror("Erreur d'ouverture");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL && (line2 = get_next_line(fd2)) != NULL)
	{
		printf("%s", line);
		printf("%s", line2);
		free(line);
		free(line2);
	}  
	// line = get_next_line(fd);
	// printf("%s", line);
	// free(line);
	// line = get_next_line(fd);
	// printf("%s", line);
	// free(line);
	close(fd);
	close(fd2);
	return (0);
}  


/*       #include <stdio.h>

int main() {
    int fd = open("gnlfile", O_RDONLY); 
    char *line;

    if (fd == -1)
    {
        perror("Erreur d'ouverture");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line); 
      
    }

    close(fd);
    return (0);
}      */ 