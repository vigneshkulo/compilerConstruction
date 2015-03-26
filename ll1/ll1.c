#include <string.h>  /* strcpy */
#include <stdlib.h>  /* malloc */
#include <stdio.h>   /* printf */
#include "myDecl.h"
#include "uthash.h"

#define SKIP	11
#define EXIT	0
#define SRC	44
#define REC	55
#define YES	1
#define NO	0

extern int yylex();
extern int yy_scan_string();
extern char* yytext;

typedef struct {
	int num;
	char **set;
} str_set;

struct my_struct {
	char key[30];			/* key (string is WITHIN the structure) */

	char ***rule;			/* Stores all rules in an array of array of characters */
	int *ruleI;			/* Stores number of elements in a rule */
	int ruleN;			/* Stores the number of rules this Variable has */

	int tabIndex;
	
	str_set first;
	str_set follow;

	UT_hash_handle hh;		/* makes this structure hashable */
};

struct my_struct *users = NULL;

int varNum = 0;
char* variables[10];
int termNum = 0;
char* terminals[20];

int findFirst(char* key, str_set *argSet, int src)
{
	int i, in;
	int tokenVal = 0;
	struct my_struct *s = NULL;

	HASH_FIND_STR( users, key, s);
	for(i = 0; i < s->ruleN; i++)
	{
		yy_scan_string(s->rule[i][0]);
		tokenVal = yylex();
		if(VARIABLE == tokenVal)
		{
			int run = 1;
			char* tempKey = yytext;
			while( SKIP == findFirst(tempKey, argSet, REC))
			{
				if(run == s->ruleI[i])
				{
					for(in = 0; in < argSet->num; in++)
					{
						if(!strcmp(argSet->set[in], "epi"))	
							break;
					}
					if(in == argSet->num)
					{
						argSet->set = (char**) realloc (argSet->set, sizeof(char*) * (argSet->num + 1));
						argSet->set[argSet->num] = (char*) malloc (sizeof(10));
						strncpy(argSet->set[argSet->num], "epi", 10);
						argSet->num++;
					}
					break;
				}
				else
				{
					yy_scan_string(s->rule[i][run]);
					tokenVal = yylex();
					if(VARIABLE == tokenVal)
					{
						tempKey = s->rule[i][run];
						run++;
					}
					else if(TERMINAL == tokenVal)
					{
						for(in = 0; in < argSet->num; in++)
						{
							if(!strcmp(argSet->set[in], yytext))	
								break;
						}
						if(in == argSet->num)
						{
							argSet->set = (char**) realloc (argSet->set, sizeof(char*) * (argSet->num + 1));
							argSet->set[argSet->num] = (char*) malloc (sizeof(10));
							strncpy(argSet->set[argSet->num], yytext, 10);
							argSet->num++;
						}
						break;
					}
				}
			}
		}
		else if(TERMINAL == tokenVal || ((EPSILON == tokenVal) && (SRC == src) ))
		{
			for(in = 0; in < argSet->num; in++)
			{
				if(!strcmp(argSet->set[in], yytext))	
					break;
			}
			if(in == argSet->num)
			{
				argSet->set = (char**) realloc (argSet->set, sizeof(char*) * (argSet->num + 1));
				argSet->set[argSet->num] = (char*) malloc (sizeof(10));
				strncpy(argSet->set[argSet->num], yytext, 10);
				argSet->num++;
			}
		}
		else if(EPSILON == tokenVal)
		{
			if(REC == src)
				return SKIP;
		}
	}
	return 1;
}

int findFollow(char* key, str_set *argSet)
{
	int tokenVal = 0;
	int i, j, k, l, m, in;
	struct my_struct *s, *s1 = NULL;
	for(i = 0; i < varNum; i++)
	{
		HASH_FIND_STR( users, variables[i], s);
		for(j = 0; j < s->ruleN; j++)
		{
			for(k = 0; k < s->ruleI[j]; k++)
			{
				if(!strcmp(key, s->rule[j][k]))
				{
				int status = !EXIT;
				int run = 1;
				while(EXIT != status)
				{	
					if(k+run == s->ruleI[j])
					{
						for(l = 0; l < s->follow.num; l++)
						{
							for(in = 0; in < argSet->num; in++)
							{
								if(!strcmp(argSet->set[in], s->follow.set[l]))	
									break;
							}
							if(in == argSet->num)
							{
								argSet->set = (char**)realloc(argSet->set, sizeof(char*) * (argSet->num + 1));
								argSet->set[argSet->num] = (char*) malloc (sizeof(10));
								strncpy(argSet->set[argSet->num], s->follow.set[l], 10);
								argSet->num++;
							}
						}
						status = EXIT;
					}
					else
					{
						yy_scan_string(s->rule[j][k+run]);
						tokenVal = yylex();
						if(VARIABLE == tokenVal)
						{
							status = EXIT;
							HASH_FIND_STR( users, s->rule[j][k+run], s1);
							for(l = 0; l < s1->first.num; l++)
							{
								if(strcmp(s1->first.set[l], "epi"))
								{
									for(in = 0; in < argSet->num; in++)
									{
										if(!strcmp(argSet->set[in], s1->first.set[l]))	
											break;
									}
									if(in == argSet->num)
									{
										argSet->set = (char**) realloc 
											(argSet->set, sizeof(char*) * (argSet->num + 1));
										argSet->set[argSet->num] = (char*) malloc (sizeof(10));
										strncpy(argSet->set[argSet->num], s1->first.set[l], 10);
										argSet->num++;
									}
								}
								else
								{
									status = !EXIT;
									run++;
								}
							}
						}
						else if(TERMINAL == tokenVal)
						{
							for(in = 0; in < argSet->num; in++)
							{
								if(!strcmp(argSet->set[in], yytext))	
									break;
							}
							if(in == argSet->num)
							{
								argSet->set = (char**)realloc(argSet->set, sizeof(char*) * (argSet->num + 1));
								argSet->set[argSet->num] = (char*) malloc (sizeof(10));
								strncpy(argSet->set[argSet->num], yytext, 10);
								argSet->num++;
							}
							status = EXIT;
						}
					}
				}
				}
			}
		}
	}
	return 1;
}

char* stack;

int pop(int nChar)
{
	int i;
	char temp[50];
	if(1 != strlen(stack))
	{
		for( i = 0; i < nChar; i++)
		{
			sscanf(stack, "%*c%s", temp);
			sprintf(stack, "%s", temp);
		}
	}
	else
		stack[0] = '\0';
	return 0;
}

int replace(char* var, char* prod)
{
	int i;
	char temp[50];
	int nChar = strlen(var);

	/* Remove Variable */
	if(1 != strlen(stack))
	{
		for( i = 0; i < nChar; i++)
		{
			sscanf(stack, "%*c%s", temp);
			sprintf(stack, "%s", temp);
		}
	//	strncpy(stack, (stack+ strlen(var)), strlen(stack) - strlen(var));
	//	stack[strlen(stack)- strlen(var)] = '\0';
	}
	else
		stack[0] = '\0';

	/* Replace with Production rule */
	sprintf(temp, "%s%s", prod, stack);
	sprintf(stack, "%s", temp);

	return 0;
}

/* Program Start */
int main(int argc, char *argv[]) 
{
	int i, j, k;
	int start = 1;
	int index = 0;
	int tokenVal = 0;
	int ruleCount = 0;

	struct my_struct *s, *tmp = NULL;
	struct my_struct *tmp1 = NULL;

	tokenVal = yylex();
	while(tokenVal)
	{
		if(VARIABLE == tokenVal && 1 == start)
		{
			HASH_FIND_STR( users, yytext, tmp);
			if(!tmp)
			{
				s = (struct my_struct*) malloc(sizeof(struct my_struct));
				s->rule = (char***) malloc (sizeof (char**));
				s->rule[0] = NULL;
				s->ruleI = (int*) malloc (sizeof (int));

				strncpy(s->key, yytext,30);
				start = 0;
			}
			else
			{
				s = tmp;
				start = 0;
				index = 0; 
				ruleCount = s->ruleN;
			}
		}
		else if(VARIABLE == tokenVal && 0 == start)
		{
			s->rule[ruleCount] = (char**) realloc (s->rule[ruleCount], sizeof (char*) * (index+1));
			s->rule[ruleCount][index] = (char*) malloc (sizeof (10));

			strncpy(s->rule[ruleCount][index], yytext, 10);
			index++;
		}
		else if(TERMINAL == tokenVal)
		{
			s->rule[ruleCount] = (char**) realloc (s->rule[ruleCount], sizeof (char*) * (index+1));
			s->rule[ruleCount][index] = (char*) malloc (sizeof (10));

			strncpy(s->rule[ruleCount][index], yytext, 10);
			index++;

			for(i = 0; i < termNum; i++)
			{
				if(!strcmp(terminals[i], yytext))	
					break;
			}
			if(i == termNum)
			{
				terminals[termNum] = (char*) malloc (30);
				strncpy(terminals[termNum], yytext, 30);
				termNum++;
			}
		}
		else if(EPSILON == tokenVal)
		{
			s->rule[ruleCount] = (char**) realloc (s->rule[ruleCount], sizeof (char*) * (index+1));
			s->rule[ruleCount][index] = (char*) malloc (sizeof (10));

			strncpy(s->rule[ruleCount][index], yytext, 10);
			index++;
		}
		else if(BAR == tokenVal)
		{
			s->ruleI[ruleCount] = index;
			index = 0;
			ruleCount++;

			s->rule = (char***) realloc (s->rule, sizeof (char**) * (ruleCount + 1));
			s->ruleI = (int*) realloc (s->ruleI, sizeof (int) * (ruleCount + 1));
		}
		else if(NEWLINE == tokenVal)
		{
			s->ruleI[ruleCount] = index;
			start = 1;
			index = 0;
			s->ruleN = ruleCount + 1;
			ruleCount = 0;
			HASH_FIND_STR( users, s->key, tmp);
			if(!tmp)
			{
				s->tabIndex = varNum;
				HASH_ADD_STR( users, key, s );
				variables[varNum] = (char*) malloc (30);
				strncpy(variables[varNum], s->key, 30);
				varNum++;
			}
		}

		tokenVal = yylex();
	}

        printf("* -------------------------------------------------\n");
	printf("\tVariables: ");
	for(i = 0; i < varNum; i++)
	{
		if(0 != i)
			printf(", ");
		printf("%s", variables[i]);
	}
	printf("\n\tTerminals: ");
	for(i = 0; i < termNum; i++)
	{
		if(0 != i)
			printf(", ");
		printf("%s", terminals[i]);
	}
        printf("\n* -------------------------------------------------\n");
	printf("\n\t\tProduction Rules\n");
        printf("* -------------------------------------------------\n");
        HASH_ITER(hh, users, s, tmp)
        {
                printf("\t%-3s -> ", s->key);
		for(i = 0; i < s->ruleN; i++)
		{
			if(0 != i)
				printf(" | ");
			for(j = 0; j < s->ruleI[i]; j++)
				printf("%s", s->rule[i][j]);
			fflush(stdout);
		}
		printf("\n");
        }
        printf("* -------------------------------------------------\n");

	/* Calculate First Sets */
	printf("\n\t\tFirst sets\n");
        printf("* -------------------------------------------------\n");
        HASH_ITER(hh, users, s, tmp)
        {
		str_set temp;
		temp.num = 0;
		temp.set = NULL;

                printf("  Variable: %-3s: ", s->key);
		fflush(stdout);
		if(SKIP == findFirst(s->key, &temp, SRC))
		{
			temp.set = (char**) realloc (temp.set, sizeof(char*) * (temp.num + 1));
			temp.set[temp.num] = (char*) malloc (sizeof(10));
			strncpy(temp.set[temp.num], "epi", 10);
			temp.num++;
		}

		memcpy(&(s->first), &temp, sizeof(str_set));
	//	printf(" N = %d, First Set = ", s->first.num);
		for(i = 0; i < s->first.num; i++)
		{
			if(0 != i)
				printf(", ");
			printf("%s", s->first.set[i]);
		}
		printf(" \n");
        }
        printf("* -------------------------------------------------\n");

	/* Calculate Follow Sets */
	printf("\n\t\tFollow sets\n");
        printf("* -------------------------------------------------\n");
        HASH_ITER(hh, users, s, tmp)
        {
		str_set temp;
		if(!strcmp(s->key, variables[0]))
		{
			temp.set = (char**) malloc (sizeof(char*));
			temp.set[0] = (char*) malloc (sizeof(10));
			strncpy(temp.set[0], "$", 10);
			temp.num = 1;
		}
		else
		{
			temp.num = 0;
			temp.set = NULL;
		}

                printf("  Variable: %-3s: ", s->key);
		findFollow(s->key, &temp);

		memcpy(&(s->follow), &temp, sizeof(str_set));
	//	printf(" N = %d, Follow Set = ", s->follow.num);
		for(i = 0; i < s->follow.num; i++)
		{
			if(0 != i)
				printf(", ");
			printf("%s", s->follow.set[i]);
		}
		printf(" \n");
        }
        printf("* -------------------------------------------------\n");

	terminals[termNum] = (char*) malloc (3);
	strncpy(terminals[termNum], "$", 3);
	termNum++;

	/*  Creating Parse table */	
	int in, ll1 = YES;
	char *table[varNum][termNum];
	memset(table, 0, sizeof(table));

	char* ruleE = (char*) malloc (30);
        HASH_ITER(hh, users, s, tmp)
        {
		#ifdef DE
                printf("\t%-3s [%d]-> \n", s->key, s->ruleN);
		#endif
		for(i = 0; i < s->ruleN; i++)
		{
			#ifdef DE
			printf("\t\t%s ", s->rule[i][0]);
			#endif
			yy_scan_string(s->rule[i][0]);
			tokenVal = yylex();
			if(VARIABLE == tokenVal)
			{
				HASH_FIND_STR( users, yytext, tmp1);
				#ifdef DE
				printf(" -> First Set of %s\n", yytext);
				#endif
				for(in = 0; in < tmp1->first.num; in++)
				{
					for(j = 0; j < termNum; j++)
					{
						if(!strcmp(terminals[j], tmp1->first.set[in]))	
							break;
					}
					#ifdef DE
					printf("\t\t\t-> Add %s to Table[%d][%d]\n", tmp1->first.set[in], s->tabIndex, j);
					#endif

					if(0 == in)
					{
						ruleE[0] = '\0';

						/* Copying entire rule */
						if(NULL == table[s->tabIndex][j])
						{
							for(k = 0; k < s->ruleI[i]; k++)
							{
								strcat(ruleE, s->rule[i][k]);
							}
						}
					}
					if(NULL == table[s->tabIndex][j])
					{
						table[s->tabIndex][j] = (char*) malloc (30);
						strncpy(table[s->tabIndex][j], ruleE, 30);
					}
					else
					{
						printf("* Rule %s already present at table[%d][%d]\n", table[s->tabIndex][j],s->tabIndex,j);
						ll1 = NO;
					}
				}
			}
			else if(TERMINAL == tokenVal)
			{
				for(j = 0; j < termNum; j++)
				{
					if(!strcmp(terminals[j], yytext))	
						break;
				}
				#ifdef DE
				printf(" -> Add %s to Table[%d][%d]\n", yytext, s->tabIndex, j);
				#endif

				ruleE[0] = '\0';

				/* Copying entire rule */
				if(NULL == table[s->tabIndex][j])
				{
					for(k = 0; k < s->ruleI[i]; k++)
					{
						strcat(ruleE, s->rule[i][k]);
					}
					table[s->tabIndex][j] = (char*) malloc (30);
					strncpy(table[s->tabIndex][j], ruleE, 30);
				}
				else
				{
					printf("* Rule %s already present at table[%d][%d]\n", table[s->tabIndex][j],s->tabIndex,j);
					ll1 = NO;
				}
			}
			else if(EPSILON == tokenVal)
			{
				#ifdef DE
				printf(" -> Follow Set of %s\n", s->key);
				#endif
				for(in = 0; in < s->follow.num; in++)
				{
					for(j = 0; j < termNum; j++)
					{
						if(!strcmp(terminals[j], s->follow.set[in]))	
							break;
					}
					#ifdef DE
					printf("\t\t\t-> Add %s to Table[%d][%d]\n", yytext, s->tabIndex, j);
					#endif
					if(NULL == table[s->tabIndex][j])
					{
						table[s->tabIndex][j] = (char*) malloc (30);
						strncpy(table[s->tabIndex][j], yytext, 30);
					}
					else
					{
						printf("* Rule %s already present at table[%d][%d]\n", table[s->tabIndex][j],s->tabIndex,j);
						ll1 = NO;
					}
				}
			}
		}
		#ifdef DE
		printf("\n");
		#endif
	}

	if(YES == ll1)
	{
		printf("\n\t\t Parse Table\n");
		printf("  -------------------------------------------------\n\t");
		for(i = 0; i < termNum; i++)
		{
			printf("%s\t", terminals[i]);
		}
		printf("\n");
		printf("  -------------------------------------------------\n");
		for(i = 0; i < varNum; i++)
		{
			printf("%s\t", variables[i]);
			for(j = 0; j < termNum; j++)
			{
				if (NULL != table[i][j])
					printf("%s\t", table[i][j]);
				else
					printf(" \t");
			}
			printf("\n");
		}
		printf("\n");
	
		/* String pattern matching */
		char input[] = "aacbbcb"; 
		char nul = '\0';
		char tempVar[30];
		char tempTer[30];

		#if 0
		char *ptr = input;			/* Equate to input, if input specified internally */
		#else
		char *ptr = argv[1];			/* Equate to argv1, if input specified externally */
		#endif

		stack = (char* ) malloc (50);
		sprintf(stack, "%s$", variables[0]);

		printf("  -------------------------------------------------\n");
		printf("\tPattern Matching for input: %s\n", ptr);
		printf("  -------------------------------------------------\n");

		/* Accepts NULL string */
		if(NULL == ptr)
			ptr = &nul;

		printf("  Stack is : %s\n", stack);

		int vInd = 0;
		int tInd = 0;
		
		/* Exit if input string is empty or Stack is empty */
		while( (0 != strlen(ptr)) && ('$' != *stack) )
		{
			yy_scan_string(stack);
			tokenVal = yylex();
			if(VARIABLE == tokenVal)
			{
				strncpy(tempVar, yytext, 30);
				printf("  Variable found at top of stack: %s\n", tempVar);

				yy_scan_string(ptr);
				yylex();
				printf("  Input variable: %s\n", yytext);

				for(j = 0; j < termNum; j++)
				{
					if(!strcmp(terminals[j], yytext))	
						break;
				}
				/* Terminal not found */
				if(j == termNum)
				{
					printf("  Invalid terminal symbol: %s \n", yytext);
					break;
				}

				tInd = j;

				HASH_FIND_STR( users, tempVar, s);
				vInd = s->tabIndex;

				/* Variable has no rule to replace */
				if(NULL == table[vInd][tInd])
				{
					printf("  No rule for Variable %s in table[%d][%d]\n", tempVar, vInd, tInd);
					break;
				}

				printf("  Rule for %s & %s: [%d][%d]: %s\n", tempVar, yytext, vInd, tInd, table[vInd][tInd]);

				printf("  STACK => %s ", stack);
				if(!strcmp("epi", table[vInd][tInd]))	
					replace(variables[vInd], "");
				else
					replace(variables[vInd], table[vInd][tInd]);
				printf("-> %s\n", stack);
				printf("  Remaining Input is : %s\n\n", ptr);
			}
			else if (TERMINAL == tokenVal)
			{
				strncpy(tempTer, yytext, 30);
				printf("  Terminal found at top of stack: %s\n", tempTer);

				yy_scan_string(ptr);
				yylex();
				printf("  Input variable: %s\n", yytext);

				if(!strcmp( yytext, tempTer))	
				{
					ptr += strlen(yytext);
					printf("  STACK => %s ", stack);
					pop(strlen(yytext));
					printf("-> %s\n", stack);
					printf("  Remaining Input is : %s\n\n", ptr);
				}
				else
					break;
			}
		}

		printf("* -------------------------------------------------\n");
		if('\0' == *ptr)
			printf("  String is Accepted :-)\n");
		else
			printf("  String is Rejected :-(\n");
		printf("* -------------------------------------------------\n");
	}
	else
	{
		printf("* -------------------------------------------------\n");
		printf("  Grammar is not LL1 :-(\n");
		printf("* -------------------------------------------------\n");
	}

	/* Freeing memory */
	HASH_ITER(hh, users, s, tmp) 
	{
		for(i = 0; i < s->ruleN; i++)
		{
			for(j = 0; j < s->ruleI[i]; j++)
				free(s->rule[i][j]);
			free(s->rule[i]);
		}
		free(s->rule);
		free(s->ruleI);

		for(i = 0; i < s->first.num; i++)
		{
			free(s->first.set[i]);
		}
		free(s->first.set);

		for(i = 0; i < s->follow.num; i++)
		{
			free(s->follow.set[i]);
		}
		free(s->follow.set);

		HASH_DEL(users, s);
		free(s);
	}
	for(i = 0; i < varNum; i++)
	{
		free(variables[i]);
	}
	for(i = 0; i < termNum; i++)
	{
		free(terminals[i]);
	}
	if(YES == ll1) free(stack);
	free(ruleE);

	for(i = 0; i < varNum; i++)
	{
		for(j = 0; j < termNum; j++)
		{
			free(table[i][j]);
		}
	}

	return 0;
}
