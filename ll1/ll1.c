#include <string.h>  /* strcpy */
#include <stdlib.h>  /* malloc */
#include <stdio.h>   /* printf */
#include "myDecl.h"
#include "uthash.h"

#define SKIP	11
#define EXIT	0
#define SRC	44
#define REC	55

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
	printf("* Variables: ");
	for(i = 0; i < varNum; i++)
	{
		if(0 != i)
			printf(", ");
		printf("%s", variables[i]);
	}
	printf("\n");
	printf("* Terminals: ");
	for(i = 0; i < termNum; i++)
	{
		if(0 != i)
			printf(", ");
		printf("%s", terminals[i]);
	}
	printf("\n");
        printf("* -------------------------------------------------\n");
	printf("* Production Rules\n");
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

	#if 1
	/* Calculate First Sets */
        HASH_ITER(hh, users, s, tmp)
        {
		str_set temp;
		temp.num = 0;
		temp.set = NULL;

                printf("* Variable: %-3s: ", s->key);
		fflush(stdout);
		if(SKIP == findFirst(s->key, &temp, SRC))
		{
			temp.set = (char**) realloc (temp.set, sizeof(char*) * (temp.num + 1));
			temp.set[temp.num] = (char*) malloc (sizeof(10));
			strncpy(temp.set[temp.num], "epi", 10);
			temp.num++;
		}

		memcpy(&(s->first), &temp, sizeof(str_set));
                printf(" N = %d, First Set = ", s->first.num);
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

                printf("* Variable: %-3s: ", s->key);
		findFollow(s->key, &temp);

		memcpy(&(s->follow), &temp, sizeof(str_set));
                printf(" N = %d, Follow Set = ", s->follow.num);
		for(i = 0; i < s->follow.num; i++)
		{
			if(0 != i)
				printf(", ");
			printf("%s", s->follow.set[i]);
		}
		printf(" \n");
        }

	#endif

	terminals[termNum] = (char*) malloc (3);
	strncpy(terminals[termNum], "$", 3);
	termNum++;

	/*  Creating Parse table */	
	int in;
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
					table[s->tabIndex][j] = (char*) malloc (30);
					strncpy(table[s->tabIndex][j], ruleE, 30);
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
					table[s->tabIndex][j] = (char*) malloc (30);
					strncpy(table[s->tabIndex][j], yytext, 30);
				}
			}
		}
		#ifdef DE
		printf("\n");
		#endif
	}
        printf("* -------------------------------------------------\n");
	printf("\t\t Parse Table\n");
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
	
        printf("* -------------------------------------------------\n");
	HASH_ITER(hh, users, s, tmp) 
	{
		HASH_DEL(users, s);
		free(s);
	}
	return 0;
}
