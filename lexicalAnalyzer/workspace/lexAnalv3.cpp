#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

string token[150]; 

#define TYPEDEF		1
#define IDENTIFIER	2
#define NUMBER		3
#define ASSIGN		4
#define RANGE		5
#define KEYWORD		6
#define LCURLY		7
#define RCURLY		8
#define COMMA		9
#define LPAREN		10
#define RPAREN		11
#define BAR		12
#define QUOTE		13

#define INITIAL_STATE	14

#define INPUT		"dfaTable"

int print(string lexeme, int finS)
{
	cout << left << setw(30) << setfill(' ') << lexeme << token[finS] << endl;
}

int main(int argc, char* argv[])
{
        if( argc <= 1)
        {
                printf("* Enter Input Filename\n");
                exit(0);
        }

	fill_n(token, 150, "UNDEFINED SYMBOL");
	fill(token+18, token+98, "TypeRef");

	token[TYPEDEF] = "TypeRef";
	token[IDENTIFIER] = "Identifier";
	token[NUMBER] = "Number";
	token[ASSIGN] = "ASSIGN";
	token[RANGE] = "RANGE";
	token[KEYWORD] = "KEYWORD";
	token[LCURLY] = "LCURLY";
	token[RCURLY] = "RCURLY";
	token[COMMA] = "COMMA";
	token[LPAREN] = "LPAREN";
	token[RPAREN] = "RPAREN";
	token[BAR] = "BAR";
	token[QUOTE] = "Quote";

	int row =  -1;
	int column = -1;

	ifstream myFile;
	myFile.open(INPUT);

	string word;
	string word1;
	string line;
	string line1;

	while(getline(myFile, line1))
	{
		line = line1;
		row++;
	}

	stringstream line2(line);
	while (line2 >> word)
	{
		column++;
	}
	myFile.clear();
	myFile.seekg(0, ios::beg); 

	cout << "* Rows: "<< row << endl;
	cout << "* Columns:" << column << endl;

	int dfaTable[row][column];

	int rows = -1;
	int columns = -1;
	while(getline(myFile, line1))
	{
		if(-1 == rows)
		{
			rows++;
			continue;
		}
		stringstream line3(line1);
		while (line3 >> word1)
		{
			if(-1 == columns)
			{
				columns++;
				continue;
			}
			int val = 0;
			istringstream buffer(word1);
			buffer >> val;
			fflush(stdout);
			dfaTable[rows][columns] = val;
			columns++;
		}
		columns = -1;
		rows++;
	}

	ifstream fp;
	fp.open(argv[1]);

	char ca;
	string lexeme;
	int state = 0;
	int nxtS = INITIAL_STATE;
	int finS = INITIAL_STATE;
	int index = 0;

	cout << "---------------------------------------------------------------" << endl;
	cout << left << setw(30) << setfill(' ') << "Lexeme" << "Token Name" << endl;
	cout << "---------------------------------------------------------------" << endl;
	
	while(fp.get(ca))
	{
		if( ca >= 48 && ca <= 57 )
			index = ca - 48;
		else if( ca >= 65 && ca <= 90 )
			index = 10 + (ca - 65);
		else if( ca >= 97 && ca <= 122 )
			index = 36 + (ca - 97);
		/* { */
		else if( 123 == ca)
			index = 62;
		/* } */
		else if( 125 == ca)
			index = 63;
		/* , */
		else if( 44 == ca)
			index = 64;
		/* ( */
		else if( 40 == ca)
			index = 65;
		/* ) */
		else if( 41 == ca)
			index = 66;
		/* | */
		else if( 124 == ca)
			index = 67;
		/* " */
		else if( 34 == ca)
			index = 68;

		/* - */
		else if( 45 == ca)
			index = 69;
		/* : */
		else if( 58 == ca)
			index = 70;
		/* = */
		else if( 61 == ca)
			index = 71;
		/* . */
		else if( 46 == ca)
			index = 72;

		else if( ca <= 32)
			index = -2;
		else
			index = -1;

		if(index > 0)
		{
			finS = nxtS;
			nxtS = dfaTable[nxtS -1][index];
			if(0 == nxtS)
			{
				print(lexeme, finS);

				lexeme.clear();
				lexeme += ca;
				nxtS = dfaTable[INITIAL_STATE - 1][index];
				finS = 1;

			//	#define DE
				#ifdef DE
				printf("%c", ca);
				printf(": [%d] : [%d]\n", index, nxtS);
				fflush(stdout);
				#endif

				continue;
			}
		}
		else
		{
			finS = nxtS;
			nxtS = -1;
		}

		#ifdef DE
		printf("%c", ca);
		printf(": [%d] : [%d]\n", index, nxtS);
		fflush(stdout);
		#endif

		if(nxtS > 0)
			lexeme += ca;
		else
		{
			// First Character is Invalid
			if (lexeme.empty() && -1 == index)
				print(lexeme, finS);
			// Terminal Character is space
			else if (!lexeme.empty() && -2 == index)
				print(lexeme, finS);
			// Terminal Character is an Invalid Character
			else if (!lexeme.empty() && -1 == index)
			{
				print(lexeme, finS);
				lexeme.clear();
				lexeme = ca;
				print(lexeme, 0);
			}

			lexeme.clear();
			nxtS = INITIAL_STATE;
			finS = INITIAL_STATE;
		}
	}
	cout << "---------------------------------------------------------------" << endl;
	return 0;
}
