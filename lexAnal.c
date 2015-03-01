/* Group : 10 
 * Lexical Analyser
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char keywords[13][20] = { "DEFINITIONS",
			"AUTOMATIC", 
			"TAGS", 
			"BEGIN", 
			"SEQUENCE", 
			"VisibleString", 
			"SIZE", 
			"NumericString", 
			"OPTIONAL", 
			"FROM", 
			"INTEGER", 
			"BOOLEAN", 
			"END", 
			};

int checkUpper(int val)
{
        if(65 <= val && val <= 90)
                return 1;
        else
                return 0;
}

int checkLower(int val)
{
        if(97 <= val && val <= 122)
                return 1;
        else
                return 0;
}

int checkNum(int val)
{
        if(48 <= val && val <= 57)
                return 1;
        else
                return 0;
}

int checkSpace(int val)
{
        if(' ' == val || '\t' == val)
                return 1;
        else if('\n' == val || '\v' == val)
                return 1;
        else if('\r' == val || '\f' == val)
                return 1;
        else
                return 0;
}

int checkAlpha(int val)
{
	return (checkUpper(val) || checkLower(val));
}

int checkAlNum(int val)
{
	return (checkAlpha(val) || checkNum(val));
}

int checkAlNumHyp(int val)
{
	return (checkAlNum(val) || (45 == val));
}

int main(int argc, char *argv[])
{
	char fileName[255];

	/* Check for Command Line Input */
	if(NULL == argv[1])
	{
		printf("* Please Enter FileName\n");
		exit(0);
	}

	/* Copy Input into FileName */
	strncpy(fileName, argv[1], sizeof(fileName));

	FILE *fp = NULL;
	char line[200];
	char *linePtr = NULL;
	char *lexStart = NULL;
	char lexeme[100];
	char *fwd = NULL;
	int i = 0;
	int found = 0;

	fp = fopen( fileName, "r+");
	if(NULL == fp)
	{
		perror("* Error ");
		exit(-1);
	}

	printf("* --------------------------------------------------------- *\n");
	printf("* \tLexeme\t\t\tToken Name		    *\n");
	printf("* --------------------------------------------------------- *\n");
	/* Loop and read each line till EOF is reached */
	while(NULL != fgets(line, sizeof(line), fp))
	{
		if('\n' == line[0])
		{
		//	printf("* EMPTY LINE -> SKIPPED\n");
			continue;
		}

	//	printf("\n%s", line);	

		/* Replace \n by \0, because 'fgets' will have \n in the line buffer */
		line[strlen(line)-1] = '\0';
		linePtr = line;

		while('\0' !=  *linePtr)
		{
			/* Remove trailing space characters */
			while(checkSpace(*linePtr)) linePtr++;

			if (checkUpper(*linePtr))
			{
				lexStart = linePtr;
				fwd = linePtr;

				while(checkAlNumHyp(*fwd)) fwd++;

				strncpy(lexeme, lexStart, fwd-lexStart);			
				lexeme[fwd-lexStart] = '\0';

				linePtr = fwd;

				i = -1;
				if(NULL == strchr(lexeme, '-'))
				{
					for(i = 0; i < 13; i++)
					{
						if(!strcmp(lexeme, keywords[i]))
						{
							printf("* \t%-30sReserved Word\n", lexeme);
							break;
						}
					}
				}
				if('-' != lexeme[strlen(lexeme) - 1] && (13 == i || -1 == i))
					printf("* \t%-30sTypeRef\n", lexeme);
				else if(13 == i || -1 == i)
				{
					printf("* \t%-30s### Error: Ends with Hypen ###\n", lexeme);
					found++;
				}
			}
			else if (checkLower(*linePtr))
			{
				lexStart = linePtr;
				fwd = linePtr;

				while(checkAlNumHyp(*fwd)) fwd++;

				strncpy(lexeme, lexStart, fwd-lexStart);			
				lexeme[fwd-lexStart] = '\0';
				if('-' != lexeme[strlen(lexeme) - 1])
					printf("* \t%-30sIdentifier\n", lexeme);
				else
				{
					printf("* \t%-30s### Error: Ends with Hypen ###\n", lexeme);
					found++;
				}

				linePtr = fwd;
			}
			else if (checkNum(*linePtr))
			{
				lexStart = linePtr;
				fwd = linePtr;

				while(checkNum(*fwd)) fwd++;

				strncpy(lexeme, lexStart, fwd-lexStart);			
				lexeme[fwd-lexStart] = '\0';
				printf("* \t%-30sNumber\n", lexeme);

				linePtr = fwd;
			}
			else if (':' == *linePtr)
			{
				lexStart = linePtr;
				fwd = linePtr;

				if(':' == *(++fwd))
				{
					if('=' == *(++fwd))
					{
						fwd++;
						strncpy(lexeme, lexStart, fwd-lexStart);			
						lexeme[fwd-lexStart] = '\0';
						printf("* \t%-30sASSIGN\n", lexeme);
					}
				}
				else
				{
					lexeme[0] = ':';
					lexeme[1] = '\0';
					printf("* \t%-30sCOLON\n", lexeme);
				}
				linePtr = fwd;
			}
			else if ('.' == *linePtr)
			{
				lexStart = linePtr;
				fwd = linePtr;
				
				if('.' == *(++fwd))
				{
					fwd++;
					strncpy(lexeme, lexStart, fwd-lexStart);			
					lexeme[fwd-lexStart] = '\0';
					printf("* \t%-30sRange_Separator\n", lexeme);
				}
				else
				{
					printf("* \t%c### Error: Period ###\n", *(fwd-1));
					found++;
					fwd++;
				}
				linePtr = fwd;
			}
			else if ('{' == *linePtr)
			{
				lexeme[0] = '{';
				lexeme[1] = '\0';
				printf("* \t%-30sLCURLY\n", lexeme);
				linePtr++;
			}
			else if (',' == *linePtr)
			{
				lexeme[0] = ',';
				lexeme[1] = '\0';
				printf("* \t%-30sCOMMA\n", lexeme);
				linePtr++;
			}
			else if ('}' == *linePtr)
			{
				lexeme[0] = '}';
				lexeme[1] = '\0';
				printf("* \t%-30sRCURLY\n", lexeme);
				linePtr++;
			}
			else if ('(' == *linePtr)
			{
				lexeme[0] = '(';
				lexeme[1] = '\0';
				printf("* \t%-30sLPAREN\n", lexeme);
				linePtr++;
			}
			else if (')' == *linePtr)
			{
				lexeme[0] = ')';
				lexeme[1] = '\0';
				printf("* \t%-30sRPAREN\n", lexeme);
				linePtr++;
			}
			else if ('"' == *linePtr)
			{
				lexeme[0] = '"';
				lexeme[1] = '\0';
				printf("* \t%-30sQUOTE\n", lexeme);
				linePtr++;
			}
			else if ('|' == *linePtr)
			{
				lexeme[0] = '|';
				lexeme[1] = '\0';
				printf("* \t%-30sBAR\n", lexeme);
				linePtr++;
			}
			else
			{
				if(0 != *linePtr)
				{
					printf("* \t%-30c### Error: Undefined Symbol ###\n", *linePtr);
					found++;
				}
				linePtr++;
			}
		}
	}
	printf("* --------------------------------------------------------- *\n");
	if(0 == found)
		printf("* SUCCESS -> File Parsed Successfully *\n");
	else
		printf("* %d Errors Found -> File Parsed Successfully *\n", found);
	printf("* --------------------------------------------------------- *\n");

	return 0;
}
