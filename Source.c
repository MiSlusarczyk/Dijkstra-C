/** @file  */

#include <stdio.h>

#include "Functions.h"


int main(int argc, char const *argv[])
{

	if (argc == 0)
	{
		perror("The command line is not available.");
	}
	else
	{
		printf("The program is now running: %s\n", argv[0]);
		if (argc == 1)
		{
			perror("Command line arguments are missing.");
		}
		else
		{
			puts("There are command line arguments.\n");
			printf("Number of arguments: %d\n\n", argc);
			puts("The list of arguments:");
			for (int i = 1; i < argc; i++)
			{
				puts(argv[i]);
			}

		}
	}

	puts("\n");

	char* path1 = NULL;
	char* path2 = NULL;
	char* path3 = NULL;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i],"-u") == 0)
		{
			path1 = argv[i+1];
		}
		else if (strcmp(argv[i],"-i") == 0)
		{
			path2 = argv[i + 1];
		}
		else if (strcmp(argv[i], "-o") == 0)
		{
			path3 = argv[i + 1];
		}
	}

	if ((path1 || path2 || path3) == NULL)
	{
		perror("Path error!");
	}

	
	Management(path1, path2, path3);

	return 0;
}


//WERSJA TESTOWA BEZ WCZYTYWANIA Z KONSOLI
/*
int main()
{

	char* path1 = "./DATA1.txt";
	char* path2 = "./DATA2.txt";
	char* path3 = "./RESULT.txt";

	Management(path1, path2, path3);

	return 0;
}
*/


