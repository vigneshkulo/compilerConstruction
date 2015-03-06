#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;
int main()
{
	int row =  -1;
	int column = -1;

	ifstream myFile;
	myFile.open("dfaTable");

	string word;
	string word1;
	string line;
	string line1;

	while(getline(myFile, line1))
	{
		line = line1;
	//	cout << line1 << endl;
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
		//	printf("[%d,%d:", rows, columns);
		//	cout << word1 << "]" << endl;
			fflush(stdout);
			dfaTable[rows][columns] = val;
			columns++;
		}
	//	printf("\n");
		columns = -1;
		rows++;
	}

	#if 0
	for(int i=0; i < rows; i++ )
	{
		for(int j=0; j < column; j++ )
		{
			printf("%d ", dfaTable[i][j]);	
		}
		printf("\n");
	}
	#endif

	ifstream fp;
	fp.open("input");

	char ca;
	string lexeme;
	int state = 0;
	int nxtS = 1;
	int finS = 1;
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
		else if( 34 == ca)
			index = 62;
		else if( 40 == ca)
			index = 63;
		else if( 41 == ca)
			index = 64;
		else if( 44 == ca)
			index = 65;
		else if( 45 == ca)
			index = 66;
		else if( 58 == ca)
			index = 67;
		else if( 61 == ca)
			index = 68;
		else if( 123 == ca)
			index = 69;
		else if( 124 == ca)
			index = 70;
		else if( 125 == ca)
			index = 71;
		else if( 46 == ca)
			index = 72;
		else
			index = -1;

		if(-1 != index)
		{
			finS = nxtS;
			nxtS = dfaTable[nxtS -1][index];
			if(0 == nxtS)
			{
				if(2 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "TypeRef" << endl;
				if(3 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "Identifier" << endl;
				if(4 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "Number" << endl;
				if(5 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "QUOTE" << endl;
				if(6 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "LPAREN" << endl;
				if(7 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "RPAREN" << endl;
				if(8 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "COMMA" << endl;
				if(9 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "HYPHEN" << endl;
				if(10 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "COLON" << endl;
				if(11 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "EQUALS" << endl;
				if(12 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "LCURLY" << endl;
				if(13 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "BAR" << endl;
				if(14 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "RCURLY" << endl;
				if(16 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "Assignment" << endl;
				if(18 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "Range separator" << endl;
				if(22 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "Keyword" << endl;

				lexeme.clear();
				lexeme += ca;
				nxtS = dfaTable[0][index];
				finS = 1;

				#if 0
				printf("%c", ca);
				printf(": [%d] : [%d]\n", index, nxtS);
				fflush(stdout);
				#endif

				continue;
			}
		}
		else
		{
			finS =nxtS;
			nxtS = -1;
		}

		#if 0
		printf("%c", ca);
		printf(": [%d] : [%d]\n", index, nxtS);
		fflush(stdout);
		#endif

		if(nxtS > 0)
			lexeme += ca;
		else
		{
			if(lexeme.length() > 1)
			{
				if(2 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "TypeRef" << endl;
				if(3 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "Identifier" << endl;
				if(4 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "Number" << endl;
				if(16 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "Assignment" << endl;
				if(18 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "Range separator" << endl;
				if(22 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "Keyword" << endl;
			}
			else
			{
				if(5 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "QUOTE" << endl;
				if(6 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "LPAREN" << endl;
				if(7 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "RPAREN" << endl;
				if(8 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "COMMA" << endl;
				if(9 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "HYPHEN" << endl;
				if(10 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "COLON" << endl;
				if(11 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "Assignment" << endl;
				if(12 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "LCURLY" << endl;
				if(13 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "BAR" << endl;
				if(14 == finS)
					cout << left << setw(30) << setfill(' ') << lexeme << "RCURLY" << endl;
			}
			lexeme.clear();
			nxtS = 1;
			finS = 1;
		}
	}
	cout << "---------------------------------------------------------------" << endl;
	return 0;
}
