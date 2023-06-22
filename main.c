#include "monty.h"

/**
 * main - main program entery
 * @argc: number argsd
 * @argv: string vectors
 * Return: 0 on success, 1 otherwise
 */

data_t param;

int main(int argc, char **argv)
{
	char *read_line = NULL, *ch_value = NULL;
	ssize_t chread = 0;
	void (*f)(stack_t **stack, unsigned int line_number);

	initialize_param();

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	param.readfd = fopen(argv[1], "rb");

	if (opcode_file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	chread = getline(&read_line, 128, param.readfd);
	while (chread != -1)
	{
		param.line_number++;
		param.opcode = strtok(read_line, " \t\n");
		trim_word(&param.opcode);
		ch_value = strtok(NULL, " \t\n");
		toInt(ch_value);

		f = get_opcodeFunc();

		f(&param.headptr, param.line_number);

		chread = getline(&read_line, 128, param.readfd);


	}

	freeParam();

}

/**
 * trim_word - trim leading and trailing spaces
 * @str: input string
 * Return: new string;
 */
char *trim_word(char **str)
{
	int  i,j;
	char *s = NULL;

	if (str == NULL || *str == NULL)
		return (NULL);
	s = *str;
	for(i=0; s[i] == ' ' || s[i] == '\t'; i++);

	for(j=0;s[i];i++)
	{
		s[j++]=s[i];
	}
	s[j]='\0';
	for(i=0;s[i]!='\0';i++)
	{
		if(s[i]!=' '&& s[i]!='\t')
				j=i;
	}
	s[j+1]='\0';

	return (s);
}

/**
 * isInt - check is string is an int
 * @str: string arg
 * Return: 0 if an INT 1 if otherwise
 */
int toInt(char *str)
{
	int str_len = strlen(str), j = 0;

	if (str != NULL)
		while (j < str_len)
		{
			if (str[j] > 47 && str[j] < 58)
				j++;
			else
				break;

		}
	else
		j++;
	
	if (j != str_len)
	{
		fprintf(stderr, "L%u: usage: push integer", param.line_number);
		exit(EXIT_FAILURE);
	}
	
	param.value = atoi(str);
}
