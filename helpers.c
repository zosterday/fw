#include "helpers.h" 	/*add later*/
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
unsigned hash(char *word, int size)
{
	unsigned hashval = 0;
	int i = 0;
	while(*(word + i) != '\0')
	{
		hashval = *(word + i) + 31 * hashval;
		i++;
	}
	return hashval % size;
}

/* 	might need to add prototype for insert at top*/
Node **rehash(Node **table, int *size)
{
	int oldsize = *size; 
	int newsize = *size + *size;
	int i = 0;
	int count;
	char *word = NULL;
	unsigned hashval;
	int length;
	Node *cur = NULL;
	Node **newTable = (Node **)malloc(sizeof(Node*)*newsize);
	*size = newsize;
	while (i < oldsize)
	{
		cur = *(table + i);
		if (cur != NULL)
		{
			while (*((cur -> word) + length) != '\0')
				length++;
			word = (char*)calloc(length, sizeof(char));	
			strcpy(word, cur -> word);
			count = cur ->count;
			hashval = hash(word, newsize);
			rehash_insert(newTable, word, count, hashval);
			free(word);
		}
		i++;	
	}
	clear_all(table, oldsize); 		/*might need to fix*/
	return newTable;
	
}
/*
Node **rehash_end(Node **table, int *size, int newsize)
{
        int oldsize = *size;
        int i = 0;
        int count;
        char *word = NULL;
        unsigned hashval;
        int length;
	int x = 0;
        Node *cur = NULL;
        Node **newTable = (Node **)malloc(sizeof(Node*)*newsize);
        *size = newsize;
	
        while (i < oldsize)
        {
                cur = *(table + i);
                if (cur != NULL)
                {
                        while (*((cur -> word) + length) != '\0')
                                length++;
                        word = (char*)calloc(length, sizeof(char));
                        strcpy(word, cur -> word);
                        count = cur ->count;
                        hashval = hash(word, newsize);
                        rehash_insert(newTable, word, count, hashval);
                        free(word);
			x++;
                }
                i++;
        }
        clear_all(table, oldsize);              might need to fix
        return newTable;

}

*/
void insert(Node **table, char *word, unsigned hashval)
{
	int i = 0;
	int length = 0;
	while ((*(word + i)) != '\0')
	{
		*(word + i) = tolower((*(word + i)));
		i++;
		length++;
	}
	length++;		/*might not be needed*/
        if (*(table + hashval) == NULL)	/*not sure if should derference once or twice*/
        {
                Node *newNode = (Node *)malloc(sizeof(Node));
                if (newNode == NULL)     
                        exit(EXIT_FAILURE);
		newNode -> word = (char*)calloc(length, sizeof(char));
                strcpy(newNode -> word, word);
                newNode -> count = 1;
		*(table + hashval) = newNode;
        }
		/* fix below */
        else 
        {
		int i = 0;
		/* below might be wrong, just the one line*/
                /*while (((strcmp((*(table + hashval +i)) -> word, word)) != 0) || *(table + hashval + i) != NULL) */
                /*{
			i++;
		}
		if ((strcmp((*(table + hashval + i)) -> word, word)) != 0)
		{
			(*(table + hashval + i)) -> count++;
		}
		else 
		{
			Node *newNode = (Node *)malloc(sizeof(Node));
                	if (newNode == NULL)
                        	exit(EXIT_FAILURE);
			newNode -> word = (char*)calloc(length, sizeof(char));
                	strcpy(newNode -> word, word);
                	newNode -> count = 1;
                	*(table + hashval + i) = newNode;
		}*/
		while ((*(table + hashval + i) != NULL) && ((strcmp((*(table + hashval +i)) -> word, word)) != 0))
		{
			/*if ((*(table + hashval + i) == NULL))
			{
				Node *newNode = (Node *)malloc(sizeof(Node));
                        	if (newNode == NULL)
                                	exit(EXIT_FAILURE);
                        	newNode -> word = (char*)calloc(length, sizeof(char));
                        	strcpy(newNode -> word, word);
                        	newNode -> count = 1;
                        	*(table + hashval + i) = newNode;

			}
			else
			{
				(*(table + hashval + i)) -> count = ((*(table + hashval + i)) -> count) + 1;
			}*/
			i++;
		}
		if ((*(table + hashval + i) == NULL))
                        {
                                Node *newNode = (Node *)malloc(sizeof(Node));
                                if (newNode == NULL)
                                        exit(EXIT_FAILURE);
                                newNode -> word = (char*)calloc(length, sizeof(char));
                                strcpy(newNode -> word, word);
                                newNode -> count = 1;
                                *(table + hashval + i) = newNode;

                        }
                        else
                        {
                                (*(table + hashval + i)) -> count = ((*(table + hashval + i)) -> count) + 1;
                        }
        }
}

void rehash_insert(Node **table, char *word, int count, unsigned hashval)
{
	int length = 0;
        while ((*(word + length)) != '\0')
        {
                length++;
        }
        length++;  
	if (*(table + hashval) == NULL)        /*not sure if should derference once or twice*/
        {
                Node *newNode = (Node *)malloc(sizeof(Node));
                if (newNode == NULL)
                        exit(EXIT_FAILURE);
		newNode -> word = (char*)calloc(length, sizeof(char));
                strcpy(newNode -> word, word);
                newNode -> count = count;
                *(table + hashval) = newNode;
        }
	else
	{
		int i = 0;
		Node *newNode = (Node *)malloc(sizeof(Node));
		if (newNode == NULL)
                        exit(EXIT_FAILURE);
		while(*(table + hashval + i) != NULL)
		{
                        i++;
                }
		newNode -> word = (char*)calloc(length, sizeof(char));
                strcpy(newNode -> word, word);
                newNode -> count = count;
                *(table + hashval + i) = newNode;

	}
}

void clear_all(Node **table, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		/*free ((*(table + i)) -> word);*/		/*might be wrong*/
		free(*(table + i));
	}
	free(table);		/*might be wrong, potentially delete this line*/
}

char *read_word(void)
{
        int size = 10;
        int position = 0;
        char *buffer = (char*)calloc(size, sizeof(char));
        /*char *buffer = (char*)malloc(sizeof(char)*size);  */      
	int c;

        if (!buffer)
        {
                exit(EXIT_FAILURE);
        }
        while(1)
        {
                c = getc(stdin);
                if (c == EOF || ! isalpha(c) || c == '\0')
                {
                        buffer[position] = '\0';
                        return buffer;
                }
                else
                {
                        buffer[position] = c;
                }
                position++;
		if (position >= size)
        	{
                	size += 5;
                	buffer = realloc(buffer, size + 1);
                	if (!buffer)
                	{
                        	exit(EXIT_FAILURE);
                	}
        	}
        }
}

char *read_word_from_file(FILE *file)
{
        int size = 10;
        int position = 0;
        char *buffer = (char*)calloc(size, sizeof(char));
        /*char *buffer = (char*)malloc(sizeof(char)*size);  */
        int c;

        if (!buffer)
        {
                exit(EXIT_FAILURE);
        }
        while(1)
        {
                c = getc(file);
                if (feof(file) || !isalpha(c))	/*this might need to be FEOF instead of EOF*/
                {
                        buffer[position] = '\0';
                        return buffer;
                }
                else
                {
                        buffer[position] = c;
                }
                position++;
                if (position >= size)
                {
                        size += 5;
                        buffer = realloc(buffer, size + 1);
                        if (!buffer)
                        {
                                exit(EXIT_FAILURE);
                        }
                }
        }
}



int comparator(const void *p, const void *q)
{
		const Node *eval1 = *(Node **)p;
		const Node *eval2 = *(Node **)q;
		int f = eval1 -> count;
		int s = eval2 -> count;
		if ((f-s) != 0)
		{
			return f-s;
		}
			return strcmp(eval1 -> word, eval2 -> word);
}


int compare(const void * a, const void * b)
{
	int count1, count2;
	char * w1;
	char * w2;
	count1 = ((Node *)a)->count;
	count2 = ((Node *)b)->count;
	w1 = ((Node *)a)->word;
	w2 = ((Node *)b)->word;
	
	if (w1 == NULL && w2 == NULL)
		return 0;
	if (w1 != NULL && w2 == NULL)
		return -1;
	if (w1 == NULL && w2 != NULL)
		return 1;
	if (count1 == count2)
		return strcmp(w1, w2);
	return count1-count2;
}

char *read_line(void)
{
        int size = 100;
        int position = 0;
        /*char *buffer = (char*)calloc(size, sizeof(char));
 *         */char *buffer = (char*)malloc(sizeof(char)*size);
        int c;

        if (!buffer)
        {
                exit(EXIT_FAILURE);
        }
        while(1)
        {
                c = getchar();
                if (c == EOF || c == '\n')
                {
			/*buffer[position] = ' ';
			buffer[position+1] = '\n';
                        */buffer[position] = '\0';
                        return buffer;
                }
                else if (isalpha(c))
                {
                        buffer[position] = c;
                }
		else if (!isalpha(c))
		{
			buffer[position] = ' ';
		}
                position++;
                if (position >= size)
        {
                size = size + size;
                buffer = realloc(buffer, size + 1);
                if (!buffer)
                {
                        exit(EXIT_FAILURE);
                }
        }
	}	
}


char *read_line_from_file(FILE* file)
{
        int size = 100;
        int position = 0;
        /*char *buffer = (char*)calloc(size, sizeof(char));
 *  *         */char *buffer = (char*)malloc(sizeof(char)*size);
        int c;

        if (!buffer)
        {
                exit(EXIT_FAILURE);
        }
        while(1)
        {
                c = getc(file);
                if (c == EOF || c == '\n')
                {
			/*buffer[position] = ' ';
                        buffer[position+1] = '\n';
			*/buffer[position] = '\0';
                        return buffer;
                }
                else if (isalpha(c))
                {
                        buffer[position] = c;
                }
                else if (!isalpha(c))
                {
                        buffer[position] = ' ';
                }
                position++;
                if (position >= size)
        {
                size = size + size;
                buffer = realloc(buffer, size + 1);
                if (!buffer)
                {
                        exit(EXIT_FAILURE);
                }
        }
        }
}
/*
Node *find_max(Node** table, int size)
{
        int i;
        word *temp = NULL;
        word *max = calloc(1, sizeof(word*));
        temp = *(table);
        for (i = 0; i < size; i++)
        {
                if (temp->count < (*(table + i))-count)
                {
                        temp = *(hashtable + i);
                }
                else if ((temp->count == (*(hashtable + i))->count) && strcmp(temp->word, (*(hashtable + i))->word))
                {
                        temp = *(hashtable + i);
                }
        }
        strcpy(max->word, temp->word);
        max->count = temp->count;
        free(temp);
        return max;
}
*/

void sort(Node **table, int size)
{
	int i = 0;
	int x = 0;
	int count;
	Node *temp = NULL;
	while (i < size)
	{
		if (*(table + i) != NULL)
		{
			x = 0;
			count = (*(table + i)) -> count;
			while((*(table + x) != NULL) && ((count < (*(table + x)) -> count) || ((strcmp((*(table+i))->word, (*(table+x))->word) < 0))))
			{
				x++;
			}
			temp = *(table + x);
			(*(table + x)) = (*(table + i));
			(*(table + i)) = temp;
		}
		i++;
	}
}






