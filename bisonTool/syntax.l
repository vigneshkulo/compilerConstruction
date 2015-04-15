%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include "parser.tab.h"
	#ifndef  COMMON_H  
	#include "common.h"
	#endif

	int symIndex = 0;
        SYMTABLE *symTable = NULL;
        SYMTABLE *s, *tmp = NULL;
%}

blanks          [ \t\n]+
identifier	[A-Z][A-Z0-9]*
number		[1-9][0-9]*|0

%%

"("		{
			yylval.ival = yytext[0];
			return LP;
		}

")"		{
			yylval.cval = yytext[0];
			return RP;
		}

";"		{
			yylval.cval = yytext[0];
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

                        /* Adding to hash table if it is not added already */
                        HASH_FIND_STR( symTable, yytext, s);
                        if(!s)
                        {
                                s = (SYMTABLE*) malloc(sizeof(SYMTABLE));
                                strncpy(s->key, yytext,30);
                                s->index = ++symIndex;
                                s->type = "UNDEFINED";
                                HASH_ADD_STR( symTable, key, s );
                        }

			return IDENTIFIER;
		}

.		;

%%
