#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "calcMessenger.h"

static string_t plus = { .c_str = "+" };
static string_t minus = { .c_str = "-" };
static string_t asteric = { .c_str = "*" };
static string_t slash = { .c_str = "/" };
static string_t lbracket = { .c_str = "(" };
static string_t rbracket = { .c_str = ")" };

int AppendToken(TokenList *list, string_t value, TokenType type)
{
	if(list->length == list->capacity)
	{
		Token *tmp = realloc(list->tokens, (list->capacity << 1)*sizeof(Token));
		if(!tmp)
			return 0;
		list->tokens = tmp;
		list->capacity <<= 1;
	}

	list->tokens[list->length++] = (Token){
		.value = value,
		.type = type
	};

	return 1;
}

int ReadNumber(string_t input, int startIndex, string_t *output)
{
	memset(output->c_str, 0, output->length);
	output->length = 0;
	int i = startIndex;

	for(; i < input.length; ++i)
	{
		if((input.c_str[i] >= '0' && input.c_str[i] <= '9') || input.c_str[i] == ' ' || (input.c_str[i] == '-' && i == startIndex))
			continue;

		if(input.c_str[i] == '.')
		{
			if(input.c_str[i-1] != '.')
				continue;
			LogWarning("Multiple '.' at position %d! Repeating points will be handled as 1.\n");
		}
		break;
	}

	string_t subStr = stringSubstring(input, startIndex, i-startIndex);
	output->c_str = subStr.c_str;
	output->length = subStr.length;

	return output->length;
}

TokenList LexEquation(string_t equation)
{
	int errorOccured = 0;

	TokenList list = {
		.length = 0,
		.capacity = 1,
		.tokens = malloc(sizeof(Token))
	};
	if(!list.tokens)
		return (TokenList){ 0 };

	for(int i = 0; i < equation.length; ++i)
	{
		switch(equation.c_str[i])
		{
			case ' ':
				break;
			case '+':
				if(AppendToken(&list, plus, PLUS))
					break;
				LogError("Failed to append '+' to token list!\n");
				errorOccured = 1;
				break;
			case '-':
				if(AppendToken(&list, minus, MINUS))
					break;
				LogError("Failed to append '-' to token list!\n");
				errorOccured = 1;
				break;
			case '*':
				if(AppendToken(&list, asteric, ASTERIC))
					break;
				LogError("Failed to append '*' to token list!\n");
				errorOccured = 1;
				break;
			case '/':
				if(AppendToken(&list, slash, SLASH))
					break;
				LogError("Failed to append '/' to token list!\n");
				errorOccured = 1;
				break;
			case '(':
			case '{':
			case '[':
				if(AppendToken(&list, lbracket, LBRACKET))
					break;
				LogError("Failed to append '%c' to token list!\n", equation.c_str[i]);
				errorOccured = 1;
				break;
			case ')':
			case '}':
			case ']':
				if(AppendToken(&list, rbracket, RBRACKET))
					break;
				LogError("Failed to append '%c' to token list!\n", equation.c_str[i]);
				errorOccured = 1;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				string_t number = newString("", 0);
				i += ReadNumber(equation, i, &number)-1;
				if(AppendToken(&list, number, NUMBER))
					break;
				LogError("Failed to append '%s' to token list!\n", number.c_str);
				errorOccured = 1;
				break;
			default:
				LogError("Unknown symbol '%c' at position %d!\n", equation.c_str[i]);
				errorOccured = 1;
				break;
		}
	}

	if(errorOccured)
	{
		free(list.tokens);
		return (TokenList) { 0 };
	}

	return list;
}
