%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include "uthash.h"

	#define	NUMBER		1
	#define IDENTIFIER	2

	#define LP		3
	#define RP		4
	#define SC		5
	#define ASGN		6

	#define OP2		7
	#define OP3		8
	#define OP4		9

	#define IF		10
	#define THEN		11
	#define ELSE		12
	#define BEGIN_K		13
	#define END_K		14
	#define WHILE		15
	#define DO		16
	#define PROGRAM		17
	#define VAR		18
	#define AS		19
	#define INT		20
	#define BOOL		21

	#define READINT		22
	#define WRITEINT	23

	#define LITERAL		24


	/* Hash Table implementation is from "UTHASH" open source code */
	struct my_struct {
	    char key[30];		/* key (string is WITHIN the structure) */
	    int id;
	    int type;
	    UT_hash_handle hh;		/* makes this structure hashable */
	};

	char* tokens[] = { NULL, "NUMBER", "IDENTIFIER", "LP", "RP", "SC", "ASGN", "OP2", "OP3", "OP4", "IF",
				"THEN", "ELSE", "BEGIN", "END", "WHILE", "DO", "PROGRAM", "VAR", "AS", "INT", "BOOL",
				"READINT", "WRITEINT", "LITERAL" };
	int tokenVal;
%}

%%

"("		return LP;
")"		return RP;
";"		return SC;
":="		return ASGN;

"*"|"div"|"mod"			return OP2;
"+"|"-"				return OP3;
"="|"!="|"<"|">"|"<="|">="	return OP4;

"if"		return IF;
"then"		return THEN;
"else"		return ELSE;
"begin"		return BEGIN_K;
"end"		return END_K;
"while"		return WHILE;
"do"		return DO;
"program"	return PROGRAM;
"var"		return VAR;
"as"		return AS;
"int"		return INT;
"bool"		return BOOL;

"readInt"	return READINT;
"writeInt"	return WRITEINT;

"true"		return LITERAL;
"false"		return LITERAL;

[1-9][0-9]*|0	return NUMBER;
[A-Z][A-Z0-9]*	return IDENTIFIER; 

.		;
\n		;

%%

int main(void)
{
	int symIndex = 0;
	struct my_struct *s, *tmp, *users = NULL;

	printf("* -----------------------------------------------------------------\n");
	printf("\tLexeme\t\t\tToken\t\t\tValue\n");
	printf("* -----------------------------------------------------------------\n");
	tokenVal = yylex();
	while(tokenVal)
	{
		if(NUMBER == tokenVal)
		{
			if(atoi(yytext) >= 0 && atoi(yytext) <= 2147483647)
				printf("\t%-20s\t%-20s%d\n", yytext, tokens[tokenVal], atoi(yytext));
			else
				printf("\t%-20s\t%-20s%s\n", yytext, "ILLEGAL NUMBER", yytext);
		}
		else if(IDENTIFIER == tokenVal)
		{
			printf("\t%-20s\t%-20s%s\n", yytext, "IDENTIFIER", tokens[tokenVal]);

			/* Adding to hash table if it is not added already */
			HASH_FIND_STR( users, yytext, s);
			if(!s)
			{
				s = (struct my_struct*) malloc(sizeof(struct my_struct));
				strncpy(s->key, yytext,30);
				s->id = ++symIndex;
				s->type = tokenVal;
				HASH_ADD_STR( users, key, s );
			}
		}
		else if(LITERAL == tokenVal)
			printf("\t%-20s\t%-20s%s\n", yytext, "LITERAL", tokens[tokenVal]);
		else if(tokenVal >= LP && tokenVal <= ASGN)
			printf("\t%-20s\t%-20s%s\n", yytext, "SYMBOL", tokens[tokenVal]);
		else if(tokenVal >= OP2 && tokenVal <= OP4)
			printf("\t%-20s\t%-20s%s\n", yytext, "OPERATOR", tokens[tokenVal]);
		else if(tokenVal >= IF && tokenVal <= BOOL)
			printf("\t%-20s\t%-20s%s\n", yytext, "KEYWORD", tokens[tokenVal]);
		else if(tokenVal >= 22 && tokenVal <= 23)
			printf("\t%-20s\t%-20s%s\n", yytext, "PROCEDURE", tokens[tokenVal]);

		tokenVal = yylex();
	}
	printf("* -----------------------------------------------------------------\n\n");
	printf("\t\t\tSymbol Table\n");
	printf("* -------------------------------------------------\n");
	printf("\tId\tLexeme\t\t\tType\n");
	printf("* -------------------------------------------------\n");
	HASH_ITER(hh, users, s, tmp) 
	{
		printf("\t%d\t%-20s\t%-20s\n", s->id, s->key, tokens[s->type]);
	}
	printf("* -----------------------------------------------------------------\n");

	/* free the hash table contents */
	HASH_ITER(hh, users, s, tmp) 
	{
		HASH_DEL(users, s);
		free(s);
	}

	return 0;
}
