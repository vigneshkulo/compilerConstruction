%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include "parser.tab.h"

%}

blanks          [ \t\n]+
identifier	[A-Z][A-Z0-9]*
number		[1-9][0-9]*|0

%%

"("		{
			yylval.ival = atoi(yytext);
			return LP;
		}

")"		{
			yylval.ival = atoi(yytext);
			return RP;
		}

";"		{
			yylval.ival = atoi(yytext);
			return SC;
		}

":="		{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return ASGN;
		}

"*"|"div"|"mod"			{
					yylval.sval = malloc(strlen(yytext));
					strncpy(yylval.sval, yytext, strlen(yytext));
					return OP2;
				}

"+"|"-"				{
					yylval.sval = malloc(strlen(yytext));
					strncpy(yylval.sval, yytext, strlen(yytext));
					return OP3;
				}

"="|"!="|"<"|">"|"<="|">="	{
					yylval.sval = malloc(strlen(yytext));
					strncpy(yylval.sval, yytext, strlen(yytext));
					return OP4;
				}
"if"		{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return IF;
		}
"then"		{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return THEN;
		}
"else"		{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return ELSE;
		}
"begin"		{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return BEGIN_K;
		}
"end"		{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return END_K;
		}
"while"		{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return WHILE;
		}
"do"		{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return DO;
		}
"program"	{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return PROGRAM;
		}
"var"		{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return VAR;
		}
"as"		{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return AS;
		}
"int"		{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return INT;
		}
"bool"		{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return BOOL;
		}

"readInt"	{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return READINT;
		}
"writeInt"	{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return WRITEINT;
		}

"true"		{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return LITERAL;
		}
"false"		{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return LITERAL;
		}

{blanks}        { /* ignore */ }

{number}	{
			yylval.ival = atoi(yytext);
			return NUMBER;
		}

{identifier}	{
			yylval.sval = malloc(strlen(yytext));
			strncpy(yylval.sval, yytext, strlen(yytext));
			return IDENTIFIER;
		}

.		;

%%
