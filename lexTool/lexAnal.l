%{
	#include <stdio.h>

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


	char* tokens[] = { NULL, "NUMBER", "IDENTIFIER", "LP", "RP", "SC", "ASGN", "OP2", "OP3", "OP4", "IF",
				"THEN", "ELSE", "BEGIN", "END", "WHILE", "DO", "PROGRAM", "VAR", "AS", "INT", "BOOL",
				"READINT", "WRITEINT" };
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

[1-9][0-9]*|0	return NUMBER;
[A-Z][A-Z0-9]*	return IDENTIFIER; 

.		;
\n		;

%%

int main(void)
{
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
	printf("* -----------------------------------------------------------------\n");
	return 0;
}
