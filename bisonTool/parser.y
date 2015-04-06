%{
#include <stdio.h>
#include <string.h>
%}

/* Symbols */
%union
{
	int	ival;
	char	cval;
	char	*sval;
};

%token <cval> LP
%token <cval> RP
%token <cval> SC
%token <sval> ASGN

%token <sval> OP2
%token <sval> OP3
%token <sval> OP4

%token <sval> IF
%token <sval> THEN
%token <sval> ELSE
%token <sval> BEGIN_K
%token <sval> END_K
%token <sval> WHILE
%token <sval> DO
%token <sval> PROGRAM
%token <sval> VAR
%token <sval> AS
%token <sval> INT
%token <sval> BOOL

%token <sval> READINT
%token <sval> WRITEINT

%token <sval> LITERAL

%token <ival> NUMBER
%token <sval> IDENTIFIER

%type <sval> Type
%type <sval> Assignment
%type <sval> Stmt
%type <sval> IfStmt
%type <sval> WhileStmt
%type <sval> WriteInt
%type <sval> Factor
%type <sval> Expr
%type <sval> SimpleExpr
%type <sval> Term

%start Program
%%

Program:
	PROGRAM 			{ printf("* PROGRAM\n");} 
	Declarations
	BEGIN_K 			{ printf("\n  BEGIN BLOCK\n");} 
	Stmtseq 
	END_K				{ printf("  END BLOCK\n");}
	;

Declarations:
	/* Epsilon */
	| 	VAR 
		IDENTIFIER 
		AS 
		Type 
		SC 			{ printf("    Variable %s declared as %s\n", $2, $4);} 
		Declarations
	;

Type:
	INT				{ $$ = $1;}
	| BOOL				{ $$ = $1;}
	;

Stmtseq:
	/* Epsilon */
	| 	Stmt SC Stmtseq 
	;

Stmt:
	Assignment
	| IfStmt
	| WhileStmt
	| WriteInt
	;

Assignment:
	IDENTIFIER ASGN Expr		{ printf("    %s is '%s' to %s\n", $1, $2, $3);}
	| IDENTIFIER ASGN READINT 	{ printf("    %s is '%s' to %s\n", $1, $2, $3);}
	;

IfStmt:
	IF 				{ printf("\n    IF "); }
	Expr 				{ printf(" %s ", $3); }
	THEN 				{ printf(" THEN\n"); }
	Stmtseq 
	ElseCl 
	END_K				{ printf("    END-IF\n"); }
	;

ElseCl:
	ELSE  				{ printf("    ELSE\n"); }
	Stmtseq
	| /* Epsilon */
	;

WhileStmt:
	WHILE  				{ printf("\n    WHILE "); }
	Expr  				{ printf(" %s ", $3); }
	DO  				{ printf(" DO\n"); }
	Stmtseq 
	END_K   			{ printf("    END-WHILE\n"); }
	;

WriteInt:
	WRITEINT Expr			{ printf("    %s %s\n", $1, $2);}
	;

Expr:
	SimpleExpr			{ $$ = $1;}
	| SimpleExpr OP4 SimpleExpr	{ $$ = malloc(strlen($1) + strlen($2) + strlen($3) + 4);
					  sprintf($$, "%s %s %s", $1, $2, $3);}
	;

SimpleExpr:
	Term OP3 Term			{ $$ = malloc(strlen($1) + strlen($2) + strlen($3) + 4);
					  sprintf($$, "%s %s %s", $1, $2, $3);}			
	| Term				{ $$ = $1;}
	;

Term:
	Factor OP2 Factor		{ $$ = malloc(strlen($1) + strlen($2) + strlen($3) + 4);
					  sprintf($$, "%s %s %s", $1, $2, $3);}		
	| Factor			{ $$ = $1;}
	;

Factor:
	IDENTIFIER			{ $$ = $1;}
	| NUMBER			{ $$ = (char*) malloc(12);
					  sprintf($$, "%d", $1);}
	| LITERAL			{ $$ = $1;}
	| LP Expr RP			{ $$ = (char*) malloc(strlen($2) + 6);
					  sprintf($$, "{ %s }", $2);}
	;


%%

int yyerror(char *s) {
  printf("yyerror : %s\n",s);
}

int main(void) {
  yyparse();
}

