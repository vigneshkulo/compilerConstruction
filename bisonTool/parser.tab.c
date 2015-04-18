/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h" 


FILE *fp = NULL;
extern SYMTABLE *symTable;

char *tokens[] = { "INTEGER", "BOOLEAN", "UNDEFINED"};

enum resultType { R_INT, R_BOOL, R_UNDEF}; 
enum treeType { T_PROGRAM, T_DECL, T_STMTSEQ, T_TERMINAL, T_STMT, T_ASSIGN, T_IF, T_WHILE, T_WRITE, T_READ, T_EXPR, 
		T_OP, T_NO_OP, T_SIMPLE_EXPR, T_TERM, T_FACTOR, T_NUMBER, T_ELSE, T_IDENT, T_LIT, T_PAR_EXPR};

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
				struct {
					char C_LP;
					struct tree* expr;
					char C_RP;
				}parenExpr;
			}arg;
			enum resultType res;
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

Tree* addIdent(char* ident)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_FACTOR;
	cur->body.factor.type = T_IDENT;
	cur->body.factor.arg.ident = ident;
	cur->body.factor.res = R_UNDEF;

	return cur;
}

Tree* addLiteral(char* literal)
{
	Tree *cur = (Tree*) malloc (sizeof(Tree));

	cur->type = T_FACTOR;
	cur->body.factor.type = T_LIT;
	cur->body.factor.arg.literal = literal;
	cur->body.factor.res = R_UNDEF;

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
			printf("error: redefinition of ‘%s’\n", ident);
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
	if(T_NUMBER == mFactor->type)
	{
		#ifdef DE
		printf("-> Number ");
		#endif

		if( 0 > mFactor->body.number || 2147483647 < mFactor->body.number)
		{
			printf("error: integer constant is too large for its type: %d\n", mFactor->body.number);
		}
		else
			fprintf(fp, "%d", mFactor->body.number);

		mFactor->body.factor.res = R_INT;
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
				#ifdef DE
				printf("-> INT ");
				#endif
				return 1;
			}
			else if(!strcmp("bool", s->type))
			{
				mFactor->body.factor.res = R_BOOL;
				#ifdef DE
				printf("-> BOOL ");
				#endif
				return 2;
			}
		}
	}
	else if(T_PAR_EXPR == mFactor->body.factor.type)
	{
		#ifdef DE
		printf("-> ( ");
		#endif
		fprintf(fp, "(");
		getExpr(mFactor->body.factor.arg.parenExpr.expr);
		#ifdef DE
		printf(")");
		#endif
		fprintf(fp, ")");
		mFactor->body.factor.res = mFactor->body.factor.arg.parenExpr.expr->body.expression.res;
	}
}

int getTerm( Tree* mTerm, int check)
{
	if(T_NO_OP == mTerm->body.term.type)
	{
		#ifdef DE
		printf("-> Factor ");
		#endif
		getFactor(mTerm->body.term.arg.factor, check);
		#ifdef DE
		printf("{%d}", mTerm->body.term.arg.factor->body.factor.res);
		#endif
		mTerm->body.term.res = mTerm->body.term.arg.factor->body.factor.res;
	}
	else if(T_OP == mTerm->body.term.type)
	{
		Tree* mLeft  = mTerm->body.term.arg.exprOP.factorl;
		Tree* mRight = mTerm->body.term.arg.exprOP.factorr;

		getFactor( mLeft, CHECK_INT);
		fprintf(fp, " %s ", mTerm->body.term.arg.exprOP.C_OP2);
		getFactor( mRight, CHECK_INT);

		if(R_INT != mLeft->body.factor.res && R_INT != mRight->body.factor.res)
		{
			printf("error: Both operands of '"); 
			printTree(mTerm);
			printf("' are not Integers\n");
		}
		else if(R_INT != mLeft->body.factor.res)
		{
			printf("error: Left operand of '"); 
			printTree(mTerm);
			printf("' : '");
			printTree(mLeft);
			printf("' is not an Integer\n");
		}
		else if(R_INT != mRight->body.factor.res)
		{
			printf("error: Right operand of '"); 
			printTree(mTerm);
			printf("' : '");
			printTree(mRight);
			printf("' is not an Integer\n");
		}
		else if(R_UNDEF == mTerm->body.term.res)
		{
			mTerm->body.term.res = R_INT;
		}
		return CHECK_INT;
	}
}

int getSim( Tree* mSim, int check)
{
	if(T_NO_OP == mSim->body.simexpression.type)
	{
		#ifdef DE
		printf("-> Term ");
		#endif
		getTerm(mSim->body.simexpression.arg.term, check);
		mSim->body.simexpression.res = mSim->body.simexpression.arg.term->body.term.res;
	}
	else if(T_OP == mSim->body.simexpression.type)
	{
		Tree* mLeft  = mSim->body.simexpression.arg.exprOP.terml;
		Tree* mRight = mSim->body.simexpression.arg.exprOP.termr;

		#ifdef DE
		printf("-> ( TermL ");
		#endif

		getTerm( mLeft, CHECK_INT);

		#ifdef DE
		printf(" ) ( TermR ");
		#endif

		fprintf(fp, " %s ", mSim->body.simexpression.arg.exprOP.C_OP3);
		getTerm( mRight, CHECK_INT);

		#ifdef DE
		printf(" )");
		#endif

		if(R_INT != mLeft->body.term.res && R_INT != mRight->body.term.res)
		{
			printf("error: Both operands of '"); 
			printTree(mSim);
			printf("' are not Integers\n");
		}
		else if(R_INT != mLeft->body.term.res)
		{
			printf("error: Left operand of '"); 
			printTree(mSim);
			printf("' : '");
			printTree(mLeft);
			printf("' is not an Integer\n");
		}
		else if(R_INT != mRight->body.term.res)
		{
			printf("error: Right operand of '"); 
			printTree(mSim);
			printf("' : '");
			printTree(mRight);
			printf("' is not an Integer\n");
		}
		else if(R_UNDEF == mSim->body.simexpression.res)
		{
			mSim->body.simexpression.res = R_INT;
		}

		#ifdef DE
		printf("{%d}", mSim->body.simexpression.res);
		#endif
		return CHECK_INT;
	}
}

int getExpr( Tree* mExpr)
{
	if(T_NO_OP == mExpr->body.expression.type)
	{
		#ifdef DE
		printf(" Expr -> SimpleExpr ");
		#endif
		getSim(mExpr->body.expression.arg.simpleExpr, NIL);
		mExpr->body.expression.res = mExpr->body.expression.arg.simpleExpr->body.simexpression.res;
		#ifdef DE
		printf("{%d}", mExpr->body.expression.res);
		#endif
		if(R_BOOL == mExpr->body.expression.res)
			return CHECK_BOOL;
	}
	else if(T_OP == mExpr->body.expression.type)
	{
		Tree* mLeft  = mExpr->body.expression.arg.exprOP.simpleExprl;
		Tree* mRight = mExpr->body.expression.arg.exprOP.simpleExprr;

		#ifdef DE
		printf(" Expr -> ( SimpleExprL ");
		#endif
		getSim( mLeft, CHECK_INT);
		#ifdef DE
		printf(" ) ( SimpleExprR ");
		#endif
		fprintf(fp, " %s ", mExpr->body.expression.arg.exprOP.C_OP4);
		getSim( mRight, CHECK_INT);
		#ifdef DE
		printf(" )");
		#endif

		if(R_INT != mLeft->body.simexpression.res && R_INT != mRight->body.simexpression.res)
		{
			printf("error: Both operands of '"); 
			printTree(mExpr);
			printf("' are not Integers\n");
		}
		else if(R_INT != mLeft->body.simexpression.res)
		{
			printf("error: Left operand of '"); 
			printTree(mExpr);
			printf("' : '");
			printTree(mLeft);
			printf("' is not an Integer\n");
		}
		else if(R_INT != mRight->body.simexpression.res)
		{
			printf("error: Right operand of '"); 
			printTree(mExpr);
			printf("' : '");
			printTree(mRight);
			printf("' is not an Integer\n");
		}
		else if(R_UNDEF == mExpr->body.expression.res)
		{
			mExpr->body.expression.res = R_BOOL;
		}
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
							fprintf(fp, "%*c %s = %s;\n", level, 9, mAsgn->body.assign.C_IDENT, 
									mAsgn->body.assign.arg3.C_READINT);
						}
						else
						{
							printf("error: readInt operand '%s' is not an integer\n", mAsgn->body.assign.C_IDENT);
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
							printf("error: operand '%s' undeclared\n", mAsgn->body.assign.C_IDENT);
							break;
						}
					}
					fprintf(fp, "%*c %s = ", level, 9, mAsgn->body.assign.C_IDENT);
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
								printf("error: assigning a boolean to a non-boolean variable '%s' in '", 
									mAsgn->body.assign.C_IDENT);
								printTree(mAsgn);
								printf("'\n");
							}
							else
								fprintf(fp, ";\n");
						}
					}
					else
						fprintf(fp, ";\n");
				}
				break;

			case T_IF:;
				fprintf(fp, "\n");

				Tree *mIf = mStat->body.statement.stmt;
				fprintf(fp, "%*c if (", level, 9); 
				ch = getExpr(mIf->body.ifcl.expr);
				if(CHECK_INT == ch || NIL == ch)
				{
					printf("error: expression guarding 'if' is not boolean: '");
					printTree(mIf->body.ifcl.expr);
					printf("'\n");
				}
				else
					fprintf(fp, ") {\n");

				getStatSeq(mIf->body.ifcl.statSeq, level + 12);	

				Tree *mEl = mIf->body.ifcl.elseCl;
				if(NULL != mEl)
				{
					fprintf(fp, "%*c }\n", level, 9);
					fprintf(fp, "%*c else {\n", level, 9); 
					getStatSeq(mEl->body.elsecl.statSeq, level + 12);	
					fprintf(fp, "%*c }\n", level, 9);
				}
				else
					fprintf(fp, "%*c }\n", level, 9);

				break;

			case T_WHILE:;
				fprintf(fp, "\n");

				Tree *mWhile = mStat->body.statement.stmt;
				fprintf(fp, "%*c while (", level, 9); 
				ch = getExpr(mWhile->body.whilecl.expr);
				if(CHECK_INT == ch || NIL == ch)
				{
					printf("error: expression guarding 'while' is not boolean: '");
					printTree(mWhile->body.whilecl.expr);
					printf("'\n");
				}
				else
					fprintf(fp, ") {\n");

				getStatSeq(mWhile->body.whilecl.statSeq, level + 12);	
				fprintf(fp, "%*c }\n", level, 9);

				break;

			case T_WRITE:;
				fprintf(fp, "\n");

				Tree *mWrite = mStat->body.statement.stmt;
				fprintf(fp, "%*c %s ", level, 9, mWrite->body.writeint.C_WRITEINT); 

				ch = getExpr(mWrite->body.writeint.expr);
				if(CHECK_BOOL == ch)
				{
					printf("error: writeInt cannot write into a boolean: '");
					printTree(mWrite->body.writeint.expr);
					printf("'\n");
				}
				else
					fprintf(fp, ";\n");
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
char*
inter
=
2500
;
	fp = fopen("a.out", "w+");
//	fp = stdout; 
	fprintf(fp, " int main(int argc, char* argv[]) {\n");
	
	/* Declarations Part */
	Tree *mDecl = root->body.program.decl;
	while(NULL != mDecl)
	{
		Tree *mType = mDecl->body.declare.type;
		if(-1 != defineVar(mDecl->body.declare.C_IDENT, mType))
			fprintf(fp, "\t %s %s;\n", mType->body.terminal, mDecl->body.declare.C_IDENT);

		mDecl = mDecl->body.declare.decl;
	}
	fprintf(fp, "\n");

	getStatSeq(root->body.program.statSeq, 0);	
	fprintf(fp, "\n");

	return 0;
}


#line 1209 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    LP = 258,
    RP = 259,
    SC = 260,
    ASGN = 261,
    OP2 = 262,
    OP3 = 263,
    OP4 = 264,
    IF = 265,
    THEN = 266,
    ELSE = 267,
    BEGIN_K = 268,
    END_K = 269,
    WHILE = 270,
    DO = 271,
    PROGRAM = 272,
    VAR = 273,
    AS = 274,
    INT = 275,
    BOOL = 276,
    READINT = 277,
    WRITEINT = 278,
    LITERAL = 279,
    NUMBER = 280,
    IDENTIFIER = 281
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 1146 "parser.y" /* yacc.c:355  */

int	ival;
char	cval;
char	*sval;
struct tree	*tval;

#line 1283 "parser.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 1298 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   46

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  29
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  57

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,  1203,  1203,  1212,  1213,  1217,  1218,  1222,  1223,  1227,
    1228,  1229,  1230,  1234,  1235,  1239,  1243,  1244,  1248,  1252,
    1256,  1257,  1261,  1262,  1266,  1267,  1271,  1272,  1273,  1274
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LP", "RP", "SC", "ASGN", "OP2", "OP3",
  "OP4", "IF", "THEN", "ELSE", "BEGIN_K", "END_K", "WHILE", "DO",
  "PROGRAM", "VAR", "AS", "INT", "BOOL", "READINT", "WRITEINT", "LITERAL",
  "NUMBER", "IDENTIFIER", "$accept", "Program", "Declarations", "Type",
  "Stmtseq", "Stmt", "Assignment", "IfStmt", "ElseCl", "WhileStmt",
  "WriteInt", "Expr", "SimpleExpr", "Term", "Factor", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281
};
# endif

#define YYPACT_NINF -24

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-24)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -13,   -11,     8,   -17,    -1,   -24,    -9,     5,   -19,     0,
       0,     0,     7,     2,    25,   -24,   -24,   -24,   -24,   -24,
     -24,    27,     0,   -24,   -24,   -24,    22,    26,    28,    30,
      18,   -24,    -3,   -24,     5,   -11,    34,     5,     0,     0,
       0,     5,   -24,   -24,   -24,   -24,   -24,    29,   -24,   -24,
     -24,    31,     5,    32,   -24,   -24,   -24
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     4,     0,     0,     0,     1,     0,     8,     0,     0,
       0,     0,     0,     0,     0,     9,    10,    11,    12,     5,
       6,     0,     0,    28,    27,    26,     0,    20,    23,    25,
       0,    19,     0,     2,     8,     4,     0,     8,     0,     0,
       0,     8,    14,    13,     7,     3,    29,    17,    21,    22,
      24,     0,     8,     0,    18,    16,    15
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -24,   -24,     4,   -24,   -23,   -24,   -24,   -24,   -24,   -24,
     -24,    -5,     6,     1,     3
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     4,    21,    13,    14,    15,    16,    53,    17,
      18,    26,    27,    28,    29
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      22,    19,    20,    22,     1,    30,    31,     3,     5,     6,
       8,    44,     7,    32,    47,     9,    33,    36,    51,    42,
      10,    23,    24,    25,    23,    24,    25,    43,    11,    55,
      34,    12,    35,    37,    41,    38,    39,    40,    46,    45,
      49,    52,     0,    50,    48,    54,    56
};

static const yytype_int8 yycheck[] =
{
       3,    20,    21,     3,    17,    10,    11,    18,     0,    26,
      19,    34,    13,     6,    37,    10,    14,    22,    41,    22,
      15,    24,    25,    26,    24,    25,    26,    32,    23,    52,
       5,    26,     5,    11,    16,     9,     8,     7,     4,    35,
      39,    12,    -1,    40,    38,    14,    14
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    17,    28,    18,    29,     0,    26,    13,    19,    10,
      15,    23,    26,    31,    32,    33,    34,    36,    37,    20,
      21,    30,     3,    24,    25,    26,    38,    39,    40,    41,
      38,    38,     6,    14,     5,     5,    38,    11,     9,     8,
       7,    16,    22,    38,    31,    29,     4,    31,    39,    40,
      41,    31,    12,    35,    14,    31,    14
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    27,    28,    29,    29,    30,    30,    31,    31,    32,
      32,    32,    32,    33,    33,    34,    35,    35,    36,    37,
      38,    38,    39,    39,    40,    40,    41,    41,    41,    41
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     6,     0,     1,     1,     3,     0,     1,
       1,     1,     1,     3,     3,     6,     2,     0,     5,     2,
       1,     3,     3,     1,     3,     1,     1,     1,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 1203 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addProg((yyvsp[-4].sval), (yyvsp[-3].tval), (yyvsp[-2].sval), (yyvsp[-1].tval), (yyvsp[0].sval));
							//  printTree($$);
							//  printSym();
							  genCode((yyval.tval));
							  printSym();
							}
#line 2408 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 1212 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addDecl((yyvsp[-5].sval), (yyvsp[-4].sval), (yyvsp[-3].sval), (yyvsp[-2].tval), (yyvsp[-1].cval), (yyvsp[0].tval));}
#line 2414 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 1213 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = NULL;}
#line 2420 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 1217 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addTerminal((yyvsp[0].sval));}
#line 2426 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 1218 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addTerminal((yyvsp[0].sval));}
#line 2432 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 1222 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addStmtSeq((yyvsp[-2].tval), (yyvsp[-1].cval), (yyvsp[0].tval)); }
#line 2438 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 1223 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = NULL; }
#line 2444 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 1227 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addStmt((yyvsp[0].tval), T_ASSIGN);}
#line 2450 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 1228 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addStmt((yyvsp[0].tval), T_IF);}
#line 2456 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 1229 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addStmt((yyvsp[0].tval), T_WHILE);}
#line 2462 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 1230 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addStmt((yyvsp[0].tval), T_WRITE);}
#line 2468 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 1234 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addAssign1((yyvsp[-2].sval), (yyvsp[-1].sval), (yyvsp[0].tval));}
#line 2474 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 1235 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addAssign2((yyvsp[-2].sval), (yyvsp[-1].sval), (yyvsp[0].sval));}
#line 2480 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 1239 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addIf((yyvsp[-5].sval), (yyvsp[-4].tval), (yyvsp[-3].sval), (yyvsp[-2].tval), (yyvsp[-1].tval), (yyvsp[0].sval));}
#line 2486 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 1243 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addElseCl((yyvsp[-1].sval), (yyvsp[0].tval));}
#line 2492 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 1244 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = NULL;}
#line 2498 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 1248 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addWhile((yyvsp[-4].sval), (yyvsp[-3].tval), (yyvsp[-2].sval), (yyvsp[-1].tval), (yyvsp[0].sval));}
#line 2504 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 1252 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addWrite((yyvsp[-1].sval), (yyvsp[0].tval));}
#line 2510 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 1256 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addExpr1((yyvsp[0].tval));}
#line 2516 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 1257 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addExpr2((yyvsp[-2].tval), (yyvsp[-1].sval), (yyvsp[0].tval));}
#line 2522 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 1261 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addSimpleExpr1((yyvsp[-2].tval), (yyvsp[-1].sval), (yyvsp[0].tval));}
#line 2528 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 1262 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addSimpleExpr2((yyvsp[0].tval));}
#line 2534 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 1266 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addTerm1((yyvsp[-2].tval), (yyvsp[-1].sval), (yyvsp[0].tval));}
#line 2540 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 1267 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addTerm2((yyvsp[0].tval));}
#line 2546 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 1271 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addIdent((yyvsp[0].sval));}
#line 2552 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 1272 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addNumber((yyvsp[0].ival));}
#line 2558 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 1273 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addLiteral((yyvsp[0].sval));}
#line 2564 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 1274 "parser.y" /* yacc.c:1646  */
    { (yyval.tval) = addFactor((yyvsp[-2].cval), (yyvsp[-1].tval), (yyvsp[0].cval));}
#line 2570 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2574 "parser.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1277 "parser.y" /* yacc.c:1906  */


int yyerror(char *s) {
  printf("yyerror : %s\n",s);
}

int main(void) {
  yyparse();
}

