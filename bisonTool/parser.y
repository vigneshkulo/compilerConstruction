%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h" 

extern SYMTABLE *symTable;

char *tokens[] = { "INTEGER", "BOOLEAN", "UNDEFINED"};

enum treeType { T_PROGRAM, T_DECL, T_STMTSEQ, T_TERMINAL, T_STMT, T_ASSIGN, T_IF, T_WHILE, T_WRITE, T_READ, T_EXPR, 
		T_OP, T_NO_OP, T_SIMPLE_EXPR, T_TERM, T_FACTOR, T_NUMBER, T_ELSE};

typedef struct tree {
	enum treeType type;
	union{
		struct{
			char* C_PROG;
			struct tree* decl;
			char* C_BEGIN;
			struct tree* statSeq;
			char* C_END;
		}program;

		struct{
			char* C_VAR;
			char* C_IDENT;
			char* C_AS;
			struct tree* type;
			char C_SC;
			struct tree* decl;
		}declare;

		struct{
			struct tree* stmt;
			char C_SC;
			struct tree* statSeq;
		}statementseq;

		struct{
			enum treeType type;
			struct tree* stmt;
		}statement;

		struct{
			char* C_WRITEINT;
			struct tree* expr;
		}writeint;

		struct{
			char* C_IDENT;
			char* C_ASGN;
			enum treeType type;
			union{
				char* C_READINT;
				struct tree* expr;
			}arg3;
		}assign;

		struct{
			enum treeType type;
			union{
				struct tree* simpleExpr;
				struct {
					struct tree* simpleExprl;
					char* C_OP4;
					struct tree* simpleExprr;
				}exprOP;
			}arg;
		}expression;

		struct{
			enum treeType type;
			union{
				struct tree* term;
				struct {
					struct tree* terml;
					char* C_OP3;
					struct tree* termr;
				}exprOP;
			}arg;
		}simexpression;

		struct{
			enum treeType type;
			union{
				struct tree* factor;
				struct {
					struct tree* factorl;
					char* C_OP2;
					struct tree* factorr;
				}exprOP;
			}arg;
		}term;

		struct{
			char C_LP;
			struct tree* expr;
			char C_RP;
		}factor;

		struct{
			char* C_IF;
			struct tree* expr;
			char* C_THEN;
			struct tree* statSeq;
			struct tree* elseCl;
			char* C_END;
		}ifcl;

		struct{
			char* C_WHILE;
			struct tree* expr;
			char* C_DO;
			struct tree* statSeq;
			char* C_END;
		}whilecl;

		struct{
			char* C_ELSE;
			struct tree* statSeq;
		}elsecl;

		char* terminal;
		int number;
	}body;
} Tree;

Tree* addProg(char* Prog, Tree* decl, char* beg, Tree* stSeq, char* end)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_PROGRAM;
	cur->body.program.C_PROG = Prog;
	cur->body.program.decl = decl;
	cur->body.program.C_BEGIN = beg;
	cur->body.program.statSeq = stSeq;
	cur->body.program.C_END = end;

	return cur;
}

Tree* addDecl(char* Var, char* Ident, char* As, Tree* type, char SemiC, Tree* decl)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_DECL;
	cur->body.declare.C_VAR = Var;
	cur->body.declare.C_IDENT = Ident;
	cur->body.declare.C_AS = As;
	cur->body.declare.type = type;
	cur->body.declare.C_SC = SemiC;
	cur->body.declare.decl = decl;

	return cur;
}

Tree* addStmtSeq(Tree* stmt, char SemiC, Tree* stSeq)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_STMTSEQ;
	cur->body.statementseq.stmt = stmt;
	cur->body.statementseq.C_SC = SemiC;
	cur->body.statementseq.statSeq = stSeq;

	return cur;
}

Tree* addStmt(Tree* stmt, enum treeType stmtType)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_STMT;
	cur->body.statement.type = stmtType;
	cur->body.statement.stmt = stmt;

	return cur;
}

Tree* addWrite(char* Write, Tree* expr)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_WRITE;
	cur->body.writeint.C_WRITEINT = Write;
	cur->body.writeint.expr = expr;

	return cur;
}

Tree* addAssign2(char* Ident, char* Asgn, char* Read)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_ASSIGN;
	cur->body.assign.C_IDENT = Ident;
	cur->body.assign.C_ASGN = Asgn;
	cur->body.assign.arg3.C_READINT = Read;
	cur->body.assign.type = T_READ;

	return cur;
}

Tree* addAssign1(char* Ident, char* Asgn, Tree* expr)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_ASSIGN;
	cur->body.assign.C_IDENT = Ident;
	cur->body.assign.C_ASGN = Asgn;
	cur->body.assign.arg3.expr = expr;
	cur->body.assign.type = T_EXPR;

	return cur;
}

Tree* addExpr1(Tree* simple)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_EXPR;
	cur->body.expression.type = T_NO_OP;
	cur->body.expression.arg.simpleExpr = simple;

	return cur;
}

Tree* addExpr2(Tree* simplel, char* Op4, Tree* simpler)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_EXPR;
	cur->body.expression.type = T_OP;
	cur->body.expression.arg.exprOP.simpleExprl = simplel;
	cur->body.expression.arg.exprOP.C_OP4 = Op4;
	cur->body.expression.arg.exprOP.simpleExprr = simpler;

	return cur;
}

Tree* addSimpleExpr1(Tree* terml, char* Op3, Tree* termr)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_SIMPLE_EXPR;
	cur->body.simexpression.type = T_OP;
	cur->body.simexpression.arg.exprOP.terml = terml;
	cur->body.simexpression.arg.exprOP.C_OP3 = Op3;
	cur->body.simexpression.arg.exprOP.termr = termr;

	return cur;
}

Tree* addSimpleExpr2(Tree* term)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_SIMPLE_EXPR;
	cur->body.simexpression.type = T_NO_OP;
	cur->body.simexpression.arg.term = term;

	return cur;
}

Tree* addTerm1(Tree* factorl, char* Op2, Tree* factorr)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_TERM;
	cur->body.term.type = T_OP;
	cur->body.term.arg.exprOP.factorl = factorl;
	cur->body.term.arg.exprOP.C_OP2 = Op2;
	cur->body.term.arg.exprOP.factorr = factorr;

	return cur;
}

Tree* addTerm2(Tree* factor)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_TERM;
	cur->body.term.type = T_NO_OP;
	cur->body.term.arg.factor = factor;

	return cur;
}

Tree* addFactor(char Lp, Tree* expr, char Rp)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_FACTOR;
	cur->body.factor.C_LP = Lp;
	cur->body.factor.expr = expr;
	cur->body.factor.C_RP = Rp;

	return cur;
}

Tree* addIf(char* If, Tree* expr, char* Then, Tree* stSeq, Tree* elseCl, char* End)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_IF;
	cur->body.ifcl.C_IF = If;
	cur->body.ifcl.expr = expr;
	cur->body.ifcl.C_THEN = Then;
	cur->body.ifcl.statSeq = stSeq;
	cur->body.ifcl.elseCl = elseCl;
	cur->body.ifcl.C_END = End;

	return cur;
}

Tree* addWhile(char* While, Tree* expr, char* Do, Tree* stSeq, char* End)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_WHILE;
	cur->body.whilecl.C_WHILE = While;
	cur->body.whilecl.expr = expr;
	cur->body.whilecl.C_DO = Do;
	cur->body.whilecl.statSeq = stSeq;
	cur->body.whilecl.C_END = End;

	return cur;
}

Tree* addElseCl( char* Else, Tree* stSeq)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_ELSE;
	cur->body.elsecl.C_ELSE = Else;
	cur->body.elsecl.statSeq = stSeq;

	return cur;
}

Tree* addNumber(int num)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_NUMBER;
	cur->body.number = num;

	return cur;
}

Tree* addTerminal(char* terminal)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_TERMINAL;
	cur->body.terminal = terminal;

	return cur;
}

int printTree (Tree* root)
{
	if(NULL == root)
	{
		return -1;
	}

	switch(root->type)
	{
		case T_PROGRAM:	
				printf("%s ", root->body.program.C_PROG);
				printf("\n");
				if(NULL != root->body.program.decl)
				{
					printf("Decl(");
					printTree(root->body.program.decl);	
					printf(") ");
				}
				printf("%s ", root->body.program.C_BEGIN);
				printf("\n");
				if(NULL != root->body.program.statSeq)
				{
					printf("StmtSeq(");
					printTree(root->body.program.statSeq);	
					printf(") ");
				}
				printf("%s \n", root->body.program.C_END);
				break;

		case T_DECL:	
				printf("%s ", root->body.declare.C_VAR);
				printf("%s ", root->body.declare.C_IDENT);
				printf("%s ", root->body.declare.C_AS);
				if(NULL != root->body.declare.type)
					printTree(root->body.declare.type);	
				printf("%c", root->body.declare.C_SC);
				if(NULL != root->body.declare.decl)
				{
					printf(" Decl(");
					printTree(root->body.declare.decl);	
					printf(") ");
				}
				break;

		case T_STMTSEQ:	
				printf(" Stmt(");
				printTree(root->body.statementseq.stmt);	
				printf(") ");
				printf("%c", root->body.statementseq.C_SC);
				if(NULL != root->body.statementseq.statSeq)
				{
					printf(" StmtSeq(");
					printTree(root->body.statementseq.statSeq);	
					printf(") ");
				}
				break;

		case T_STMT:	
				if(T_WRITE == root->body.statement.type)
					printf(" WriteInt(");
				else if(T_ASSIGN == root->body.statement.type)
					printf(" Assign(");
				else if(T_IF == root->body.statement.type)
					printf(" IF(");
				else if(T_WHILE == root->body.statement.type)
					printf(" WHILE(");
				printTree(root->body.statement.stmt);	
				printf(") ");
				break;

		case T_WRITE:	
				printf("%s ", root->body.writeint.C_WRITEINT);
				printTree(root->body.writeint.expr);	
				break;

		case T_ASSIGN:	
				printf("%s ", root->body.assign.C_IDENT);
				printf("%s ", root->body.assign.C_ASGN);
				if(T_EXPR == root->body.assign.type)
				{
					printf(" Expr(");
					printTree(root->body.assign.arg3.expr);	
					printf(") ");
				}
				else
					printf("%s ", root->body.assign.arg3.C_READINT);
				break;

		case T_EXPR:	
				if(T_NO_OP == root->body.expression.type)
				{
					printf(" SimpleExpr(");
					printTree(root->body.expression.arg.simpleExpr);	
					printf(") ");
				}
				else if(T_OP == root->body.expression.type)
				{
					printf(" SimpleExprL(");
					printTree(root->body.expression.arg.exprOP.simpleExprl);	
					printf(") ");
					printf("%s ", root->body.expression.arg.exprOP.C_OP4);
					printf(" SimpleExprR(");
					printTree(root->body.expression.arg.exprOP.simpleExprr);	
					printf(") ");
				}
				break;

		case T_SIMPLE_EXPR:	
				if(T_NO_OP == root->body.simexpression.type)
				{
					printf(" Term(");
					printTree(root->body.simexpression.arg.term);	
					printf(") ");
				}
				else if(T_OP == root->body.simexpression.type)
				{
					printf(" TermL(");
					printTree(root->body.simexpression.arg.exprOP.terml);	
					printf(") ");
					printf("%s ", root->body.simexpression.arg.exprOP.C_OP3);
					printf(" TermR(");
					printTree(root->body.simexpression.arg.exprOP.termr);	
					printf(") ");
				}
				break;
	
		case T_TERM:	
				if(T_NO_OP == root->body.term.type)
				{
					printf(" Factor(");
					printTree(root->body.term.arg.factor);	
					printf(") ");
				}
				else if(T_OP == root->body.term.type)
				{
					printf(" FactorL(");
					printTree(root->body.term.arg.exprOP.factorl);	
					printf(") ");
					printf("%s ", root->body.term.arg.exprOP.C_OP2);
					printf(" FactorR(");
					printTree(root->body.term.arg.exprOP.factorr);	
					printf(") ");
				}
				break;
	
		case T_FACTOR:	
				printf("%c ", root->body.factor.C_LP);
				printf(" Expr(");
				printTree(root->body.factor.expr);	
				printf(") ");
				printf("%c ", root->body.factor.C_RP);
				break;

		case T_IF:	
				printf("%s ", root->body.ifcl.C_IF);
				printTree(root->body.ifcl.expr);	
				printf("%s ", root->body.ifcl.C_THEN);
				if(NULL != root->body.ifcl.statSeq)
				{
					printf(" StmtSeq(");
					printTree(root->body.ifcl.statSeq);	
					printf(") ");
				}
				if(NULL != root->body.ifcl.elseCl)
				{
					printf(" ElseCl(");
					printTree(root->body.ifcl.elseCl);	
					printf(") ");
				}
				printf("%s ", root->body.ifcl.C_END);
				break;

		case T_WHILE:	
				printf("%s ", root->body.whilecl.C_WHILE);
				printTree(root->body.whilecl.expr);	
				printf("%s ", root->body.whilecl.C_DO);
				if(NULL != root->body.whilecl.statSeq)
				{
					printf(" StmtSeq(");
					printTree(root->body.whilecl.statSeq);	
					printf(") ");
				}
				printf("%s ", root->body.whilecl.C_END);
				break;

		case T_ELSE:	
				printf("%s ", root->body.elsecl.C_ELSE);
				if(NULL != root->body.elsecl.statSeq)
				{
					printf(" StmtSeq(");
					printTree(root->body.elsecl.statSeq);	
					printf(") ");
				}
				break;
	
		case T_NUMBER:	
				printf("%d ", root->body.number);
				break;
	
		case T_TERMINAL:	
				printf("%s ", root->body.terminal);
				break;
	
		default:
				printf("* Undefined TYPE: %d\n", root->type);
				break;
	}
	return 1;
}

int printSym()
{
	SYMTABLE *s, *tmp = NULL;

	printf("* -----------------------------------------------------------------\n\n");
	printf("\t\t\tSymbol Table\n");
	printf("* -------------------------------------------------\n");
	printf("\tId\tLexeme\t\t\tType\n");
	printf("* -------------------------------------------------\n");
	HASH_ITER(hh, symTable, s, tmp)
	{
		printf("\t%d\t%-20s\t%-20s\n", s->index, s->key, s->type);
	}
	printf("* -----------------------------------------------------------------\n");

	return 0;
}

int defineVar(char* ident, Tree* type)
{
	SYMTABLE *s = NULL;

	printf("* %s is being defined as %s\n", ident, type->body.terminal);

	/* Defining a variable if it is not defined */
	HASH_FIND_STR( symTable, ident, s);
	if(s)
	{
		if(!strcmp("UNDEFINED", s->type))
		{
			s->type = type->body.terminal;
		}
		else
		{
			printf("*** %s is already defined as %s ***\n", ident, type->body.terminal);
			return -1;
		}
	}
	return 1;
}

#define	NIL		0
#define	CHECK_INT	1
#define	CHECK_BOOL	2

int getFactor( Tree* mFactor, int check)
{
	if(T_TERMINAL == mFactor->type)
	{
		printf("%s", mFactor->body.terminal);
		if(CHECK_INT == 1)
		{
			SYMTABLE *s = NULL;
			HASH_FIND_STR( symTable, mFactor->body.terminal, s);
			if(s)
			{
				if(strcmp("int", s->type))
				{
					printf("(*** Not a Integer ***)");
				}
			}
		}
		return NIL;
	}
	else if(T_FACTOR == mFactor->type)
	{
		printf("(");
		int ch = getExpr(mFactor->body.factor.expr);
		printf(")");
		return ch;
	}
	else if(T_NUMBER == mFactor->type)
	{
		if( 0 > mFactor->body.number || 2147483647 < mFactor->body.number)
			printf("%d (*** Out of Range ***)", mFactor->body.number);
		else
			printf("%d", mFactor->body.number);
	}
}

int getTerm( Tree* mTerm, int check)
{
	if(T_NO_OP == mTerm->body.term.type)
	{
		return getFactor(mTerm->body.term.arg.factor, check);
	}
	else if(T_OP == mTerm->body.term.type)
	{
		getFactor(mTerm->body.term.arg.exprOP.factorl, CHECK_INT);
		printf(" %s ", mTerm->body.term.arg.exprOP.C_OP2);
		getFactor(mTerm->body.term.arg.exprOP.factorr, CHECK_INT);
		return CHECK_INT;
	}
}

int getSim( Tree* mSim, int check)
{
	if(T_NO_OP == mSim->body.simexpression.type)
	{
		return getTerm(mSim->body.simexpression.arg.term, check);
	}
	else if(T_OP == mSim->body.simexpression.type)
	{
		getTerm(mSim->body.simexpression.arg.exprOP.terml, CHECK_INT);
		printf(" %s ", mSim->body.simexpression.arg.exprOP.C_OP3);
		getTerm(mSim->body.simexpression.arg.exprOP.termr, CHECK_INT);
		return CHECK_INT;
	}
}

int getExpr( Tree* mExpr)
{
	if(T_NO_OP == mExpr->body.expression.type)
	{
		return getSim(mExpr->body.expression.arg.simpleExpr, NIL);
	}
	else if(T_OP == mExpr->body.expression.type)
	{
		getSim(mExpr->body.expression.arg.exprOP.simpleExprl, CHECK_INT);
		printf(" %s ", mExpr->body.expression.arg.exprOP.C_OP4);
		getSim(mExpr->body.expression.arg.exprOP.simpleExprr, CHECK_INT);
		return CHECK_BOOL;
	}
}

int getStatSeq(Tree *mStatSeq, int level)
{
	int ch = 0;
	/* Statement Sequence Part */
	while(NULL != mStatSeq)
	{
		Tree *mStat = mStatSeq->body.statementseq.stmt;

		switch(mStat->body.statement.type)
		{
			case T_ASSIGN:;
				Tree *mAsgn = mStat->body.statement.stmt;
				
				if(T_READ == mAsgn->body.assign.type)
				{
					SYMTABLE *s = NULL;
					HASH_FIND_STR( symTable, mAsgn->body.assign.C_IDENT, s);
					if(s)
					{
						if(!strcmp("int", s->type))
						{
							printf("%*c %s = %s;\n", level, 9, mAsgn->body.assign.C_IDENT, 
									mAsgn->body.assign.arg3.C_READINT);
						}
						else
						{
							printf("%*c *** %s is not an integer ***\n", level, 9, mAsgn->body.assign.C_IDENT);
							break;
						}
					}
				}
				else if(T_EXPR == mAsgn->body.assign.type)
				{
					SYMTABLE *s = NULL;
					HASH_FIND_STR( symTable, mAsgn->body.assign.C_IDENT, s);
					if(s)
					{
						if(!strcmp("UNDEFINED", s->type))
						{
							printf("%*c *** %s is not defined ***\n", level, 9, mAsgn->body.assign.C_IDENT);
							break;
						}
					}
					printf("%*c %s = ", level, 9, mAsgn->body.assign.C_IDENT);
					ch = getExpr(mAsgn->body.assign.arg3.expr);
					if(CHECK_INT == ch)
					{
						s = NULL;
						HASH_FIND_STR( symTable, mAsgn->body.assign.C_IDENT, s);
						if(s)
						{
							if(strcmp("int", s->type))
							{
								printf(";\t*** %s is not an integer ***\n", mAsgn->body.assign.C_IDENT);
							}
							else
								printf(";\n");
						}
					}
					else if(CHECK_BOOL == ch)
					{
						s = NULL;
						HASH_FIND_STR( symTable, mAsgn->body.assign.C_IDENT, s);
						if(s)
						{
							if(strcmp("bool", s->type))
							{
								printf(";\t*** %s is not an boolean ***\n", mAsgn->body.assign.C_IDENT);
							}
							else
								printf(";\n");
						}
					}
					else
						printf(";\n");
				}
				break;

			case T_IF:;
				printf("\n");

				Tree *mIf = mStat->body.statement.stmt;
				printf("%*c if (", level, 9); 
				ch = getExpr(mIf->body.ifcl.expr);
				if(CHECK_INT == ch || NIL == ch)
				{
					printf(")\t *** Expr result is not an boolean ***\n");
				}
				else
					printf(") {\n");

				getStatSeq(mIf->body.ifcl.statSeq, level + 12);	

				Tree *mEl = mIf->body.ifcl.elseCl;
				if(NULL != mEl)
				{
					printf("%*c }\n", level, 9);
					printf("%*c else {\n", level, 9); 
					getStatSeq(mEl->body.elsecl.statSeq, level + 12);	
					printf("%*c }\n", level, 9);
				}
				else
					printf("%*c }\n", level, 9);

				break;

			case T_WHILE:;
				printf("\n");

				Tree *mWhile = mStat->body.statement.stmt;
				printf("%*c while (", level, 9); 
				ch = getExpr(mWhile->body.whilecl.expr);
				if(CHECK_INT == ch || NIL == ch)
				{
					printf(")\t *** Expr result is not an boolean ***\n");
				}
				else
					printf(") {\n");

				getStatSeq(mWhile->body.whilecl.statSeq, level + 12);	
				printf("%*c }\n", level, 9);

				break;

			case T_WRITE:;
				printf("\n");

				Tree *mWrite = mStat->body.statement.stmt;
				printf("%*c %s ", level, 9, mWrite->body.writeint.C_WRITEINT); 

				ch = getExpr(mWrite->body.writeint.expr);
				if(CHECK_BOOL == ch)
				{
					printf(";\t*** writeInt cannot write boolean ***\n");
				}
				else
					printf(";\n");
				break;

			default:
				printf("* :-|\n"); 
				break;
		}
		mStatSeq = mStatSeq->body.statementseq.statSeq;
		
	}
	return 0;
}

int genCode(Tree* root)
{
	printf("* ----------------\n");
	printf("* Code in C\n");
	printf("* ----------------\n");

	printf(" int main(int argc, char* argv[]) {\n");
	
	/* Declarations Part */
	Tree *mDecl = root->body.program.decl;
	while(NULL != mDecl)
	{
		Tree *mType = mDecl->body.declare.type;
		if(strcmp("UNDEFINED", mType->body.terminal))
			printf("\t %s %s;\n", mType->body.terminal, mDecl->body.declare.C_IDENT);

		mDecl = mDecl->body.declare.decl;
	}
	printf("\n");

	getStatSeq(root->body.program.statSeq, 0);	
	printf("\n");

	return 0;
}

%}

/* Symbols */
%union
{
int	ival;
char	cval;
char	*sval;
struct tree	*tval;
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

%type <tval> Program
%type <tval> Declarations
%type <tval> Stmtseq

%type <tval> Type
%type <tval> Stmt
%type <tval> Assignment
%type <tval> IfStmt
%type <tval> WhileStmt
%type <tval> WriteInt
%type <tval> Expr
%type <tval> SimpleExpr
%type <tval> Term
%type <tval> Factor
%type <tval> ElseCl

%start Program
%%

Program:
	PROGRAM	Declarations BEGIN_K Stmtseq END_K	{ $$ = addProg($1, $2, $3, $4, $5);
							//  printTree($$);
							  printSym();
							  genCode($$);
							}
	;

Declarations:
	VAR IDENTIFIER AS Type SC Declarations		{ if(-1 != defineVar($2, $4))
							  { 
								$$ = addDecl($1, $2, $3, $4, $5, $6); 
							  }
							  else
								$$ = $6;
							}
	| /* Epsilon */					{ $$ = NULL;}
	;

Type:
	INT						{ $$ = addTerminal($1);}
	| BOOL						{ $$ = addTerminal($1);}
	;

Stmtseq:
	Stmt SC Stmtseq					{ $$ = addStmtSeq($1, $2, $3); } 
	| /* Epsilon */					{ $$ = NULL; }
	;

Stmt:
	Assignment					{ $$ = addStmt($1, T_ASSIGN);}
	| IfStmt					{ $$ = addStmt($1, T_IF);}
	| WhileStmt					{ $$ = addStmt($1, T_WHILE);}
	| WriteInt					{ $$ = addStmt($1, T_WRITE);}
	;

Assignment:
	IDENTIFIER ASGN Expr				{ $$ = addAssign1($1, $2, $3);}
	| IDENTIFIER ASGN READINT 			{ $$ = addAssign2($1, $2, $3);}
	;

IfStmt:
	IF Expr	THEN Stmtseq ElseCl END_K		{ $$ = addIf($1, $2, $3, $4, $5, $6);}
	;

ElseCl:
	ELSE Stmtseq					{ $$ = addElseCl($1, $2);}
	| /* Epsilon */					{ $$ = NULL;}
	;

WhileStmt:
	WHILE Expr DO Stmtseq END_K   			{ $$ = addWhile($1, $2, $3, $4, $5);}
	;

WriteInt:
	WRITEINT Expr					{ $$ = addWrite($1, $2);}
	;

Expr:
	SimpleExpr					{ $$ = addExpr1($1);}
	| SimpleExpr OP4 SimpleExpr			{ $$ = addExpr2($1, $2, $3);}
	;

SimpleExpr:
	Term OP3 Term					{ $$ = addSimpleExpr1($1, $2, $3);}			
	| Term						{ $$ = addSimpleExpr2($1);}
	;

Term:
	Factor OP2 Factor				{ $$ = addTerm1($1, $2, $3);}		
	| Factor					{ $$ = addTerm2($1);}
	;

Factor:
	IDENTIFIER					{ $$ = addTerminal($1);}
	| NUMBER					{ $$ = addNumber($1);} 
	| LITERAL					{ $$ = addTerminal($1);}
	| LP Expr RP					{ $$ = addFactor($1, $2, $3);}
	;

%%

int yyerror(char *s) {
  printf("yyerror : %s\n",s);
}

int main(void) {
  yyparse();
}

