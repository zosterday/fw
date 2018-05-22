#include <stdio.h>
#include "helpers.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
int main(int argc, char *argv[])
{
	int i;
	int x;
	int numberWanted = 10;
	unsigned hashval;
	int numOfWords = 0;
	FILE *file;
	int fileArg = 1;
	int size = 1111024;
	Node **table = (Node**)malloc(sizeof(Node*)*size);
	Node *node = NULL;
	int length;
	char *line = NULL;
	char *wordptr = NULL;
	int uniqueWords = 0;
	if (argv[1] != NULL && (strcmp(argv[1], "-n") == 0))
	{
		if ((argv[2] == NULL) || (argv[2] != NULL && !isdigit(argv[2][0])))
		{
			free(table);
			printf("usage: fw [-n num] [file1 [file2 ...]]\n");
                        return 1;
		}
		else /*if (argv[2] != NULL && isdigit(argv[2]))*/
                {
                        numberWanted = (int)(*argv[2]);
                        fileArg = 3;

		
		}
	}
	if (argv[fileArg] == NULL)
	{
		/*while((*(word = read_word()) != '\0'))*/
               /* while(strcmp((word = read_word()), "") != 0)*/
		/*{
                   	numOfWords++;
                    	if (((double)numOfWords/size) > .4)*/     /*might need to change casting*/
                    	/*{
                      		table = rehash(table, &size);
                     	}
                     	hashval = hash(word, size);
                	insert(table, word, hashval);
                }*/
		while(*(line = read_line()) != '\0')
		/*while(strcmp((line = read_line())," \n\0") != 0 && (*line) != '\0')*/
		{
			wordptr = strtok(line, " ");
			while (wordptr != NULL)
			{
				numOfWords++;
                        	if (((double)numOfWords/size) > .4)
                        		table = rehash(table, &size);
 				hashval = hash(wordptr, size);
                       		insert(table, wordptr, hashval);
				wordptr = strtok(NULL, " .!,\n");	
			}
		}
	}
	else
	{
		while (argv[fileArg] != NULL)
		{
			file = fopen(argv[fileArg], "r");
			if (file == NULL)
			{		/*would this need to be fclosed?*/
				printf("%s: No such file or directory\n", argv[fileArg]);
			}	
			else
			{	
				/*while((word = read_word_from_file(file)) != NULL)
				{
					numOfWords++;
					if (((double)numOfWords/size) > .4)
					{
						table = rehash(table, &size);
					}
					hashval = hash(word, size);
					insert(table, word, hashval);
					
				}*/
				while (*(line = read_line_from_file(file)) != '\0')
				/*while(strcmp((line = read_line_from_file(file))," \n\0") != 0 && (*line) != '\0')*/
				{
					wordptr = strtok(line, " ");
                        		while (wordptr != NULL)
                        		{
                                		numOfWords++;
                                		if (((double)numOfWords/size) > .4)
                                        		table = rehash(table, &size);
                                		hashval = hash(wordptr, size);
                                		insert(table, wordptr, hashval);
                                		wordptr = strtok(NULL, " .!,\n");
                        		}
				}
				fclose(file);					
			}
			/*if null file needs to be closed then move fclose here*/
			fileArg++;
		}
	}
	for (i = 0; i < size; i++)
	{
		if ((*(table + i)) != NULL)
		{
			uniqueWords++;
		}
	}


	length = sizeof(table) / sizeof(*table);
	/*qsort((void*)table, size, sizeof(Node*), comparator);
	sort(table, size);
	*/printf("The top %d words (out of %d) are:\n", numberWanted, uniqueWords);
	i = 0;
	x =0;
	while (x < numberWanted && i < size)
	{
		if ((*(table + i)) != NULL)
		{
			node = *(table +i);
			if (node != NULL)
				printf("        %d %s\n", (node -> count), (node -> word));
			x++;
		}
		i++;
	}
	clear_all(table, size);
	return 0;
	
	
}
