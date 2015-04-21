%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h" 

/* Global variables */
FILE *fp = NULL;
char ipFile[10] = "input";
char opFile[10] = "output.c";

/* Shared Global variables for Lex and Bison */
extern int lineNum;
extern SYMTABLE *symTable;

enum resultType { R_INT, R_BOOL, R_UNDEF}; 
enum treeType { T_PROGRAM, T_DECL, T_STMTSEQ, T_TERMINAL, T_STMT, T_ASSIGN, T_IF, T_WHILE, T_WRITE, T_READ, T_EXPR, 
		T_OP, T_NO_OP, T_SIMPLE_EXPR, T_TERM, T_FACTOR, T_NUMBER, T_ELSE, T_IDENT, T_LIT, T_PAR_EXPR};

typedef struct ADDLINE {
	char* ident;
	int line;
} ADDLINE;

/* Node Structure */
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
			int line;
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
			int line;
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
			enum resultType res;
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
			enum resultType res;
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
			enum resultType res;
		}term;

		struct{
			enum treeType type;
			union{
				char* ident;
				char* literal;
				int number;
				struct {
					char C_LP;
					struct tree* expr;
					char C_RP;
				}parenExpr;
			}arg;
			enum resultType res;
			int line;
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

Tree* addDecl(char* Var, char* Ident, char* As, Tree* type, char SemiC, Tree* decl, int line)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_DECL;
	cur->body.declare.C_VAR = Var;
	cur->body.declare.C_IDENT = Ident;
	cur->body.declare.C_AS = As;
	cur->body.declare.type = type;
	cur->body.declare.C_SC = SemiC;
	cur->body.declare.decl = decl;
	cur->body.declare.line = line;

	return cur;
}

Tree* modDecl(Tree* cur, Tree* decl)
{
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

Tree* addAssign2(char* Ident, char* Asgn, char* Read, int line)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_ASSIGN;
	cur->body.assign.C_IDENT = Ident;
	cur->body.assign.C_ASGN = Asgn;
	cur->body.assign.arg3.C_READINT = Read;
	cur->body.assign.type = T_READ;
	cur->body.assign.line = line;

	return cur;
}

Tree* addAssign1(char* Ident, char* Asgn, Tree* expr, int line)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_ASSIGN;
	cur->body.assign.C_IDENT = Ident;
	cur->body.assign.C_ASGN = Asgn;
	cur->body.assign.arg3.expr = expr;
	cur->body.assign.type = T_EXPR;
	cur->body.assign.line = line;

	return cur;
}

Tree* addExpr1(Tree* simple)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_EXPR;
	cur->body.expression.type = T_NO_OP;
	cur->body.expression.arg.simpleExpr = simple;
	cur->body.expression.res = R_UNDEF;

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
	cur->body.expression.res = R_UNDEF;

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
	cur->body.simexpression.res = R_UNDEF;

	return cur;
}

Tree* addSimpleExpr2(Tree* term)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_SIMPLE_EXPR;
	cur->body.simexpression.type = T_NO_OP;
	cur->body.simexpression.arg.term = term;
	cur->body.simexpression.res = R_UNDEF;

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
	cur->body.term.res = R_UNDEF;

	return cur;
}

Tree* addTerm2(Tree* factor)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_TERM;
	cur->body.term.type = T_NO_OP;
	cur->body.term.arg.factor = factor;
	cur->body.term.res = R_UNDEF;

	return cur;
}

Tree* addIdent(char* ident, int line)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_FACTOR;
	cur->body.factor.type = T_IDENT;
	cur->body.factor.arg.ident = ident;
	cur->body.factor.res = R_UNDEF;
	cur->body.factor.line = line;

	return cur;
}

Tree* addLiteral(char* literal, int line)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_FACTOR;
	cur->body.factor.type = T_LIT;
	cur->body.factor.arg.literal = literal;
	cur->body.factor.res = R_UNDEF;
	cur->body.factor.line = line;

	return cur;
}

Tree* addNumber(int num, int line)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_FACTOR;
	cur->body.factor.type = T_NUMBER;
	cur->body.factor.arg.number = num;
	cur->body.factor.res = R_UNDEF;
	cur->body.factor.line = line;

	return cur;
}

Tree* addFactor(char Lp, Tree* expr, char Rp)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_FACTOR;
	cur->body.factor.type = T_PAR_EXPR;
	cur->body.factor.arg.parenExpr.C_LP = Lp;
	cur->body.factor.arg.parenExpr.expr = expr;
	cur->body.factor.arg.parenExpr.C_RP = Rp;
	cur->body.factor.res = R_UNDEF;

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
					#ifdef PR
					printf(" Expr(");
					#endif
					printTree(root->body.assign.arg3.expr);	
					#ifdef PR
					printf(") ");
					#endif
				}
				else
					printf("%s ", root->body.assign.arg3.C_READINT);
				break;

		case T_EXPR:	
				if(T_NO_OP == root->body.expression.type)
				{
					#ifdef PR
					printf(" SimpleExpr(");
					#endif
					printTree(root->body.expression.arg.simpleExpr);	
					#ifdef PR
					printf(") ");
					#endif
				}
				else if(T_OP == root->body.expression.type)
				{
					#ifdef PR
					printf(" SimpleExprL(");
					#endif
					printTree(root->body.expression.arg.exprOP.simpleExprl);	
					#ifdef PR
					printf(") ");
					#endif
					printf("%s ", root->body.expression.arg.exprOP.C_OP4);
					#ifdef PR
					printf(" SimpleExprR(");
					#endif
					printTree(root->body.expression.arg.exprOP.simpleExprr);	
					#ifdef PR
					printf(") ");
					#endif
				}
				break;

		case T_SIMPLE_EXPR:	
				if(T_NO_OP == root->body.simexpression.type)
				{
					#ifdef PR
					printf(" Term(");
					#endif
					printTree(root->body.simexpression.arg.term);	
					#ifdef PR
					printf(") ");
					#endif
				}
				else if(T_OP == root->body.simexpression.type)
				{
					#ifdef PR
					printf(" TermL(");
					#endif
					printTree(root->body.simexpression.arg.exprOP.terml);	
					#ifdef PR
					printf(") ");
					#endif
					printf("%s ", root->body.simexpression.arg.exprOP.C_OP3);
					#ifdef PR
					printf(" TermR(");
					#endif
					printTree(root->body.simexpression.arg.exprOP.termr);	
					#ifdef PR
					printf(") ");
					#endif
				}
				break;
	
		case T_TERM:	
				if(T_NO_OP == root->body.term.type)
				{
					#ifdef PR
					printf(" Factor(");
					#endif
					printTree(root->body.term.arg.factor);	
					#ifdef PR
					printf(") ");
					#endif
				}
				else if(T_OP == root->body.term.type)
				{
					#ifdef PR
					printf(" FactorL(");
					#endif
					printTree(root->body.term.arg.exprOP.factorl);	
					#ifdef PR
					printf(") ");
					#endif
					printf("%s ", root->body.term.arg.exprOP.C_OP2);
					#ifdef PR
					printf(" FactorR(");
					#endif
					printTree(root->body.term.arg.exprOP.factorr);	
					#ifdef PR
					printf(") ");
					#endif
				}
				break;
	
		case T_FACTOR:	
				if(T_IDENT == root->body.factor.type)
				{
					printf("%s ", root->body.factor.arg.ident);
				}
				else if(T_LIT == root->body.factor.type)
				{
					printf("%s ", root->body.factor.arg.literal);
				}
				else if(T_NUMBER == root->body.factor.type)
				{
					printf("%d ", root->body.factor.arg.number);
				}
				else if(T_PAR_EXPR == root->body.factor.type)
				{
					printf("%c ", root->body.factor.arg.parenExpr.C_LP);
					#ifdef PR
					printf(" Expr(");
					#endif
					printTree(root->body.factor.arg.parenExpr.expr);	
					#ifdef PR
					printf(") ");
					#endif
					printf("%c ", root->body.factor.arg.parenExpr.C_RP);
				}
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
	
		case T_TERMINAL:	
				printf("%s ", root->body.terminal);
				break;
	
		default:
				printf("* Undefined TYPE: %d\n", root->type);
				break;
	}
	return 1;
}

int printLine (Tree* root)
{
	int ret = 0;
	if(NULL == root)
	{
		return -1;
	}

	switch(root->type)
	{
		case T_EXPR:	
				if(T_NO_OP == root->body.expression.type)
				{
					ret = printLine(root->body.expression.arg.simpleExpr);	
				}
				else if(T_OP == root->body.expression.type)
				{
					ret = printLine(root->body.expression.arg.exprOP.simpleExprl);	
					printLine(root->body.expression.arg.exprOP.simpleExprr);	
				}
				break;

		case T_SIMPLE_EXPR:	
				if(T_NO_OP == root->body.simexpression.type)
				{
					ret = printLine(root->body.simexpression.arg.term);	
				}
				else if(T_OP == root->body.simexpression.type)
				{
					ret = printLine(root->body.simexpression.arg.exprOP.terml);	
					printLine(root->body.simexpression.arg.exprOP.termr);	
				}
				break;
	
		case T_TERM:	
				if(T_NO_OP == root->body.term.type)
				{
					ret = printLine(root->body.term.arg.factor);	
				}
				else if(T_OP == root->body.term.type)
				{
					ret = printLine(root->body.term.arg.exprOP.factorl);	
					printLine(root->body.term.arg.exprOP.factorr);	
				}
				break;
	
		case T_FACTOR:	
				if(T_IDENT == root->body.factor.type || T_LIT == root->body.factor.type || T_NUMBER == root->body.factor.type)
				{
					ret = root->body.factor.line;
				}
				else if(T_PAR_EXPR == root->body.factor.type)
				{
					ret = printLine(root->body.factor.arg.parenExpr.expr);	
				}
				break;

		default:
				printf("* Undefined TYPE: %d\n", root->type);
				ret = 0;
				break;
	}
	return ret;
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

int defineVar(char* ident, Tree* type, int line)
{
	SYMTABLE *s = NULL;

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
			printf("%s: %d: error: redefinition of ‘%s’\n", ipFile, line, ident);
			return -1;
		}
	}
	return 1;
}

#define	NIL		0
#define	CHECK_INT	1
#define	CHECK_BOOL	2
#define	CHECK_UNDEF	3

int getFactor( Tree* mFactor)
{
	int ret = 0;
	if(T_NUMBER == mFactor->body.factor.type)
	{
		if( 0 > mFactor->body.factor.arg.number || 2147483647 < mFactor->body.factor.arg.number)
		{
			printf("%s: %d:error: integer constant is invalid for its type: %d\n", ipFile, mFactor->body.factor.line, 
				mFactor->body.factor.arg.number);
		}
		else
			fprintf(fp, "%d", mFactor->body.factor.arg.number);

		mFactor->body.factor.res = R_INT;
		return CHECK_INT;
	}
	else if(T_IDENT == mFactor->body.factor.type)
	{
		fprintf(fp, "%s", mFactor->body.factor.arg.ident);
		SYMTABLE *s = NULL;
		HASH_FIND_STR( symTable, mFactor->body.factor.arg.ident, s);
		if(s)
		{
			if(!strcmp("int", s->type))
			{
				mFactor->body.factor.res = R_INT;
				return CHECK_INT;
			}
			else if(!strcmp("bool", s->type))
			{
				mFactor->body.factor.res = R_BOOL;
				return CHECK_BOOL;
			}
		}
	}
	else if(T_LIT == mFactor->body.factor.type)
	{
		fprintf(fp, "%s", mFactor->body.factor.arg.literal);
		mFactor->body.factor.res = R_BOOL;
		return CHECK_BOOL;
	}
	else if(T_PAR_EXPR == mFactor->body.factor.type)
	{
		fprintf(fp, "(");
		ret = getExpr(mFactor->body.factor.arg.parenExpr.expr);
		fprintf(fp, ")");
		mFactor->body.factor.res = mFactor->body.factor.arg.parenExpr.expr->body.expression.res;
		return ret;
	}
}

int getTerm( Tree* mTerm)
{
	int err = 0;
	int ret = 0;
	if(T_NO_OP == mTerm->body.term.type)
	{
		ret = getFactor(mTerm->body.term.arg.factor);
		mTerm->body.term.res = mTerm->body.term.arg.factor->body.factor.res;
		return ret;
	}
	else if(T_OP == mTerm->body.term.type)
	{
		Tree* mLeft  = mTerm->body.term.arg.exprOP.factorl;
		Tree* mRight = mTerm->body.term.arg.exprOP.factorr;

		getFactor( mLeft);

		if(!strcmp("div", mTerm->body.term.arg.exprOP.C_OP2))
		{
			fprintf(fp, " / ");

			/* Check for Divide by Zero */
			if(T_NUMBER == mRight->body.factor.type)
			{
				if( 0 == mRight->body.factor.arg.number)
				{
					printf("%s: %d: warning: division by zero: '", ipFile, printLine(mRight)); 
					printTree(mTerm);
					printf("'\n");
				}
			}
		}
		else if(!strcmp("mod", mTerm->body.term.arg.exprOP.C_OP2))
		{
			fprintf(fp, " %% ");
		}
		else 
			fprintf(fp, " %s ", mTerm->body.term.arg.exprOP.C_OP2);

		getFactor( mRight);

		if(R_INT != mLeft->body.factor.res)
		{
			printf("%s: %d: error: Left operand of '", ipFile, printLine(mLeft)); 
			printTree(mTerm);
			printf("' : '");
			printTree(mLeft);
			printf("' is not an Integer\n");
			err = 1;
		}
		if(R_INT != mRight->body.factor.res)
		{
			printf("%s: %d: error: Right operand of '", ipFile, printLine(mRight)); 
			printTree(mTerm);
			printf("' : '");
			printTree(mRight);
			printf("' is not an Integer\n");
			err = 1;
		}
		if(R_UNDEF == mTerm->body.term.res && 1 != err)
		{
			mTerm->body.term.res = R_INT;
			return CHECK_INT;
		}
		else 
			return CHECK_UNDEF;
	}
}

int getSim( Tree* mSim)
{
	int err = 0;
	int ret = 0;
	if(T_NO_OP == mSim->body.simexpression.type)
	{
		ret = getTerm(mSim->body.simexpression.arg.term);
		mSim->body.simexpression.res = mSim->body.simexpression.arg.term->body.term.res;
		return ret;
	}
	else if(T_OP == mSim->body.simexpression.type)
	{
		Tree* mLeft  = mSim->body.simexpression.arg.exprOP.terml;
		Tree* mRight = mSim->body.simexpression.arg.exprOP.termr;

		getTerm( mLeft);
		fprintf(fp, " %s ", mSim->body.simexpression.arg.exprOP.C_OP3);
		getTerm( mRight);

		if(R_INT != mLeft->body.term.res)
		{
			printf("%s: %d: error: Left operand of '", ipFile, printLine(mLeft)); 
			printTree(mSim);
			printf("' : '");
			printTree(mLeft);
			printf("' is not an Integer\n");
			err = 1;
		}
		if(R_INT != mRight->body.term.res)
		{
			printf("%s: %d: error: Right operand of '", ipFile, printLine(mRight)); 
			printTree(mSim);
			printf("' : '");
			printTree(mRight);
			printf("' is not an Integer\n");
			err = 1;
		}
		if(R_UNDEF == mSim->body.simexpression.res && 1 != err)
		{
			mSim->body.simexpression.res = R_INT;
			return CHECK_INT;
		}
		else
			return CHECK_UNDEF;
	}
}

int getExpr( Tree* mExpr)
{
	int err = 0;
	int ret = 0;
	if(T_NO_OP == mExpr->body.expression.type)
	{
		ret = getSim(mExpr->body.expression.arg.simpleExpr);
		mExpr->body.expression.res = mExpr->body.expression.arg.simpleExpr->body.simexpression.res;
		if(R_BOOL == mExpr->body.expression.res)
		{
			return CHECK_BOOL;
		}
		else
			return ret;
	}
	else if(T_OP == mExpr->body.expression.type)
	{
		Tree* mLeft  = mExpr->body.expression.arg.exprOP.simpleExprl;
		Tree* mRight = mExpr->body.expression.arg.exprOP.simpleExprr;

		getSim( mLeft);

		if(!strcmp("=", mExpr->body.expression.arg.exprOP.C_OP4))
		{
			fprintf(fp, " == ");
		}
		else
			fprintf(fp, " %s ", mExpr->body.expression.arg.exprOP.C_OP4);

		getSim( mRight);

		if(R_INT != mLeft->body.simexpression.res)
		{
			printf("%s: %d: error: Left operand of '", ipFile, printLine(mLeft)); 
			printTree(mExpr);
			printf("' : '");
			printTree(mLeft);
			printf("' is not an Integer\n");
			err = 1;
		}
		if(R_INT != mRight->body.simexpression.res)
		{
			printf("%s: %d: error: Right operand of '", ipFile, printLine(mRight)); 
			printTree(mExpr);
			printf("' : '");
			printTree(mRight);
			printf("' is not an Integer\n");
			err = 1;
		}
		if(R_UNDEF == mExpr->body.expression.res && 1 != err)
		{
			mExpr->body.expression.res = R_BOOL;
			return CHECK_BOOL;
		}
		else
			return CHECK_UNDEF;
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
							fprintf(fp, "%*cscanf(\"%%d\", &%s);\n", level, 9, mAsgn->body.assign.C_IDENT);
						}
						else
						{
							printf("%s: %d: error: readInt operand '%s' is not an integer\n", 
								ipFile, mAsgn->body.assign.line, mAsgn->body.assign.C_IDENT);
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
							printf("%s: %d: error: operand '%s' undeclared\n", ipFile,
								mAsgn->body.assign.line, mAsgn->body.assign.C_IDENT);
							break;
						}
					}
					fprintf(fp, "%*c%s = ", level, 9, mAsgn->body.assign.C_IDENT);
					ch = 0;
					ch = getExpr(mAsgn->body.assign.arg3.expr);
					if(CHECK_INT == ch)
					{
						s = NULL;
						HASH_FIND_STR( symTable, mAsgn->body.assign.C_IDENT, s);
						if(s)
						{
							if(strcmp("int", s->type))
							{
							printf("%s: %d: error: assigning an integer to a non-integer variable '%s' in '", 
								ipFile, mAsgn->body.assign.line, mAsgn->body.assign.C_IDENT);
								printTree(mAsgn);
								printf("'\n");
							}
							else
								fprintf(fp, ";\n");
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
							printf("%s: %d: error: assigning a boolean to a non-boolean variable '%s' in '", 
								ipFile, mAsgn->body.assign.line, mAsgn->body.assign.C_IDENT);
								printTree(mAsgn);
								printf("'\n");
							}
							else
								fprintf(fp, ";\n");
						}
					}
					else if(CHECK_UNDEF == ch)
					{
						printf("%s: %d: error: assigning an 'undefined' type to a variable '%s' in '", 
							ipFile, mAsgn->body.assign.line, mAsgn->body.assign.C_IDENT);
							printTree(mAsgn);
							printf("'\n");
					}
					else
						fprintf(fp, ";\n");
				}
				break;

			case T_IF:;
				fprintf(fp, "\n");

				Tree *mIf = mStat->body.statement.stmt;
				fprintf(fp, "%*cif (", level, 9); 
				ch = getExpr(mIf->body.ifcl.expr);
				if(CHECK_INT == ch || NIL == ch)
				{
					printf("%s: %d: error: expression guarding 'if' is not boolean: '", ipFile,
						printLine(mIf->body.ifcl.expr));
					printTree(mIf->body.ifcl.expr);
					printf("'\n");
				}
				else
					fprintf(fp, ") {\n");

				getStatSeq(mIf->body.ifcl.statSeq, level + 12);	

				Tree *mEl = mIf->body.ifcl.elseCl;
				if(NULL != mEl)
				{
					fprintf(fp, "%*c}\n", level, 9);
					fprintf(fp, "%*celse {\n", level, 9); 
					getStatSeq(mEl->body.elsecl.statSeq, level + 12);	
					fprintf(fp, "%*c}\n", level, 9);
				}
				else
					fprintf(fp, "%*c}\n", level, 9);

				break;

			case T_WHILE:;
				fprintf(fp, "\n");

				Tree *mWhile = mStat->body.statement.stmt;
				fprintf(fp, "%*cwhile (", level, 9); 
				ch = getExpr(mWhile->body.whilecl.expr);
				if(CHECK_INT == ch || NIL == ch)
				{
					printf("%s: %d: error: expression guarding 'while' is not boolean: '", ipFile,
						printLine(mWhile->body.whilecl.expr));
					printTree(mWhile->body.whilecl.expr);
					printf("'\n");
				}
				else
					fprintf(fp, ") {\n");

				getStatSeq(mWhile->body.whilecl.statSeq, level + 12);	
				fprintf(fp, "%*c}\n", level, 9);

				break;

			case T_WRITE:;
				fprintf(fp, "\n");

				Tree *mWrite = mStat->body.statement.stmt;
				fprintf(fp, "%*cprintf(\"%%d\\n\", ", level, 9); 

				ch = getExpr(mWrite->body.writeint.expr);
				if(CHECK_BOOL == ch)
				{
					printf("%s: %d: error: writeInt cannot write into a boolean: '", ipFile, 
						printLine(mWrite->body.writeint.expr));
					printTree(mWrite->body.writeint.expr);
					printf("'\n");
				}
				else if(R_UNDEF == mWrite->body.writeint.expr->body.expression.res)	
				{	
					printf("%s: %d: error: writeInt cannot write into a undefined type: '", ipFile, 
						printLine(mWrite->body.writeint.expr));
					printTree(mWrite->body.writeint.expr);
					printf("'\n");
				}
				else
					fprintf(fp, ");\n");
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
	fp = fopen(opFile, "w+");

	fprintf(fp, "#include <stdio.h>\n");
	fprintf(fp, "#include <stdlib.h>\n");
	fprintf(fp, "\n");
	fprintf(fp, "int main(int argc, char* argv[]) {\n");
	
	/* Declarations Part */
	Tree *mDecl = root->body.program.decl;
	while(NULL != mDecl)
	{
		Tree *mType = mDecl->body.declare.type;
		if(-1 != defineVar(mDecl->body.declare.C_IDENT, mType, mDecl->body.declare.line))
		{
			if(!strcmp(mType->body.terminal, "int"))
				fprintf(fp, "\t%s %s = 0;\n", mType->body.terminal, mDecl->body.declare.C_IDENT);
			else if(!strcmp(mType->body.terminal, "bool"))
				fprintf(fp, "\t%s %s = false;\n", mType->body.terminal, mDecl->body.declare.C_IDENT);
		}

		mDecl = mDecl->body.declare.decl;
	}
	fprintf(fp, "\n");

	/* Statement Sequence Part */
	getStatSeq(root->body.program.statSeq, 0);	

	fprintf(fp, "\nreturn 0;\n");
	fprintf(fp, "}");

	return 0;
}

int freeMem(Tree* root)
{
	if(NULL == root)
	{
		return -1;
	}

	switch(root->type)
	{
		case T_PROGRAM:	
				free(root->body.program.C_PROG);
				if(NULL != root->body.program.decl)
				{
					freeMem(root->body.program.decl);	
				}
				free(root->body.program.C_BEGIN);
				if(NULL != root->body.program.statSeq)
				{
					freeMem(root->body.program.statSeq);	
				}
				free(root->body.program.C_END);
				free(root);
				break;

		case T_DECL:	
				free(root->body.declare.C_IDENT);
				free(root->body.declare.C_AS);
				if(NULL != root->body.declare.type)
					freeMem(root->body.declare.type);	
				if(NULL != root->body.declare.decl)
				{
					freeMem(root->body.declare.decl);	
				}
				free(root);
				break;

		case T_STMTSEQ:	
				freeMem(root->body.statementseq.stmt);	
				if(NULL != root->body.statementseq.statSeq)
				{
					freeMem(root->body.statementseq.statSeq);	
				}
				free(root);
				break;

		case T_STMT:	
				freeMem(root->body.statement.stmt);	
				free(root);
				break;

		case T_WRITE:	
				free(root->body.writeint.C_WRITEINT);
				freeMem(root->body.writeint.expr);	
				free(root);
				break;

		case T_ASSIGN:	
				free( root->body.assign.C_IDENT);
				free( root->body.assign.C_ASGN);

				if(T_EXPR == root->body.assign.type)
				{
					freeMem(root->body.assign.arg3.expr);	
				}
				else
					free( root->body.assign.arg3.C_READINT);
				free(root);
				break;

		case T_EXPR:	
				if(T_NO_OP == root->body.expression.type)
				{
					freeMem(root->body.expression.arg.simpleExpr);	
				}
				else if(T_OP == root->body.expression.type)
				{
					freeMem(root->body.expression.arg.exprOP.simpleExprl);	
					free( root->body.expression.arg.exprOP.C_OP4);
					freeMem(root->body.expression.arg.exprOP.simpleExprr);	
				}
				free(root);
				break;

		case T_SIMPLE_EXPR:	
				if(T_NO_OP == root->body.simexpression.type)
				{
					freeMem(root->body.simexpression.arg.term);	
				}
				else if(T_OP == root->body.simexpression.type)
				{
					freeMem(root->body.simexpression.arg.exprOP.terml);	
					free( root->body.simexpression.arg.exprOP.C_OP3);
					freeMem(root->body.simexpression.arg.exprOP.termr);	
				}
				free(root);
				break;
	
		case T_TERM:	
				if(T_NO_OP == root->body.term.type)
				{
					freeMem(root->body.term.arg.factor);	
				}
				else if(T_OP == root->body.term.type)
				{
					freeMem(root->body.term.arg.exprOP.factorl);	
					free( root->body.term.arg.exprOP.C_OP2);
					freeMem(root->body.term.arg.exprOP.factorr);	
				}
				free(root);
				break;
	
		case T_FACTOR:	
				if(T_IDENT == root->body.factor.type)
				{
					free( root->body.factor.arg.ident);
				}
				else if(T_LIT == root->body.factor.type)
				{
					free( root->body.factor.arg.literal);
				}
				else if(T_PAR_EXPR == root->body.factor.type)
				{
					freeMem(root->body.factor.arg.parenExpr.expr);	
				}
				free(root);
				break;

		case T_IF:	
				free( root->body.ifcl.C_IF);
				freeMem(root->body.ifcl.expr);	
				free( root->body.ifcl.C_THEN);
				if(NULL != root->body.ifcl.statSeq)
				{
					freeMem(root->body.ifcl.statSeq);	
				}
				if(NULL != root->body.ifcl.elseCl)
				{
					freeMem(root->body.ifcl.elseCl);	
				}
				free( root->body.ifcl.C_END);
				free(root);
				break;

		case T_WHILE:	
				free( root->body.whilecl.C_WHILE);
				freeMem(root->body.whilecl.expr);	
				free( root->body.whilecl.C_DO);
				if(NULL != root->body.whilecl.statSeq)
				{
					freeMem(root->body.whilecl.statSeq);	
				}
				free( root->body.whilecl.C_END);
				free(root);
				break;

		case T_ELSE:	
				free( root->body.elsecl.C_ELSE);
				if(NULL != root->body.elsecl.statSeq)
				{
					freeMem(root->body.elsecl.statSeq);	
				}
				free(root);
				break;
	
		case T_TERMINAL:	
				free( root->body.terminal);
				free(root);
				break;
	
		default:
				printf("* Undefined TYPE: %d\n", root->type);
				break;
	}
	return 1;
}

%}

/* Symbols */
%union
{
int	ival;
char	cval;
char	*sval;
struct tree	*tval;
struct ADDLINE	*sline;
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

%type <tval> Declare
%type <sline> Ident

%start Program
%%

Program:
	PROGRAM	Declarations BEGIN_K Stmtseq END_K	{ $$ = addProg($1, $2, $3, $4, $5);
							  genCode($$);
							  printSym();
							  freeMem($$);
							}
	;

Declarations:
	Declare Declarations				{ $$ = modDecl($1, $2);}
	| /* Epsilon */					{ $$ = NULL;}
	;

Declare:
	VAR Ident AS Type SC				{ $$ = addDecl($1, $2->ident, $3, $4, $5, NULL, $2->line); free($2);}
	;

Ident:
	IDENTIFIER					{ $$ = (ADDLINE*) malloc(sizeof(ADDLINE));
							  $$->ident = $1;
							  $$->line = lineNum; }
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
	Ident ASGN Expr					{ $$ = addAssign1($1->ident, $2, $3, $1->line); free($1);}
	| Ident ASGN READINT 				{ $$ = addAssign2($1->ident, $2, $3, $1->line); free($1);}
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
	IDENTIFIER					{ $$ = addIdent($1, lineNum);}
	| NUMBER					{ $$ = addNumber($1, lineNum);} 
	| LITERAL					{ $$ = addLiteral($1, lineNum);}
	| LP Expr RP					{ $$ = addFactor($1, $2, $3);}
	;

%%

int yyerror(char *s) {
  printf("yyerror : %s\n",s);
}

int main(void) {
  yyparse();
}

