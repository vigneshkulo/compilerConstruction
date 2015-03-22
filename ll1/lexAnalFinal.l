%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdio.h>

	#include "myDecl.h"
%}

%%

"E"|"T"|"T'"|"F"		return VARIABLE;
"+"|"x"|"w"|"*"|"y"|"z"		return TERMINAL;
"epi"				return EPSILON;
\n				return NEWLINE;
"|"				return BAR;
.		;

%%

int yywrap(void)
{
	return 1;
}

#if 0
int main(void)
{
	int tokenVal = 0;

	printf("* -----------------------------------------------------------------\n");
	printf("\tLexeme\t\t\tToken\t\t\tValue\n");
	printf("* -----------------------------------------------------------------\n");
	tokenVal = yylex();
	while(tokenVal)
	{
		if(VARIABLE == tokenVal)
			printf("\t%-20s\t%-20s%s\n", yytext, "VARIABLE", yytext);
		else if(TERMINAL == tokenVal)
			printf("\t%-20s\t%-20s%s\n", yytext, "TERMINAL", yytext);
		else if(EPSILON == tokenVal)
			printf("\t%-20s\t%-20s%s\n", yytext, "EPSILON", yytext);

		tokenVal = yylex();
	}
	printf("* -----------------------------------------------------------------\n");
	return 0;
}
#endif
