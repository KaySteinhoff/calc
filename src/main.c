#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring.h>
#include "lexer.h"
#include "parser.h"
#include "calcMessenger.h"

void ParseArguments(string_t *equation, char **argv, int argc);

int main(int argc, char **argv)
{
	//Check if calculation exists
	if(argc < 2)
	{
		LogError("No arguments provided! Please type 'calc -h' or provide at minimum an equation: calc <options> \"x+y\"\n");
		return 1;
	}

	string_t input;
	ParseArguments(&input, argv+1, argc-1);
	if(!input.c_str)
	{
		LogError("Failed to read input!\n");
		return 2;
	}

	TokenList tokenList = LexEquation(input);
	if(!tokenList.tokens)
	{
		LogError("Failed to tokenize input!\n");
		return 3;
	}

	Node *root = ParseTokens(tokenList);
	if(!root)
	{
		LogError("Failed to parse equation!\n");
		return 4;
	}

	printf("Result: %g\n", ResolveNode(root));
#ifdef DEBUG
	printf("%s\n", PrintNode(root));
#endif

	return 0;
}

void ParseOption(char *argv)
{
	switch(argv[1])
	{
		case 'h':
			printf("calc <options> [equation]\n\nOPTIONS:\n -h:\n\tDisplays this page\n\n -v:\n\tDisplays the currently installed version of calc and the version it is published under.\n");
			break;
		case 'v':
			printf("calc version 1.0 {Released: 12.09.2024}\nGNU General Public License v3.0\n");
			break;
	}
}

void ParseArguments(string_t *equation, char **argv, int argc)
{
	for(int i = 0; i < argc; ++i)
	{
		if(argv[i][0] == '-')
			ParseOption(argv[i]);
		else // all other arguments are treated as equations right now. will be changed in the future
		{
			string_t tmp = newString(argv[i], strlen(argv[i]));
			equation->c_str = tmp.c_str;
			equation->length = tmp.length;
			equation->capacity = tmp.capacity;
		}
	}
}
