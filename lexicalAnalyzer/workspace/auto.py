TYPEDEF = 1
IDENTIFIER = 2
NUMBER = 3
ASSIGN = 4
RANGE = 5
KEYWORD = 6
LCURLY = 7
RCURLY = 8
COMMA = 9
LPAREN = 10
RPAREN = 11
BAR = 12
QUOTE = 13

INITIAL_STATE = 14

HYPHEN = 15
COLON = 16 
EQUAL = 17
DOT = 18

NNUM	=	10
NLET	=	26
NSYM	=	7
NEXT	=	4

INUM	=	0 
ICAP	=	INUM + NNUM
ISMA	=	ICAP + NLET
ISYM	=	ISMA + NLET
IEXT	=	ISYM + NSYM
ITOT	=	IEXT + NEXT

print ("* Num: %d, Cap: %d, Sma: %d, Sym: %d, Ext: %d") % (INUM, ICAP, ISMA, ISYM, IEXT)
print ("* Total: %d") % (ITOT)

table = [[0 for i in range(ITOT)] for j in range(DOT-1)]

#1. Typedef State
for i in range(0, ISYM):
	table[TYPEDEF - 1][i] = 1

#2. Identifier State
for i in range(0, ISYM):
	table[IDENTIFIER - 1][i] = 2

#3. Number State
for i in range(0, ICAP):
	table[NUMBER - 1][i] = 3

#4. Assign State

#5. Range State

#6. Keyword State

#7. Lcurly State

#8. Rcurly State

#9. Comma State

#10. Lparen State

#11. Rparen State

#12. Bar State

#13. Quote State

fp = open("dfaTable", "w")

# Initial State
for i in range(0, ICAP):
	table[INITIAL_STATE - 1][i] = NUMBER 
for i in range(ICAP, ISMA):
	table[INITIAL_STATE - 1][i] = TYPEDEF
for i in range(ISMA, ISYM):
	table[INITIAL_STATE - 1][i] = IDENTIFIER
for i in range(ISYM, IEXT):
	table[INITIAL_STATE - 1][i] = (i % ISYM) + LCURLY

count = 0

# Assignment
count += 1
table[INITIAL_STATE - 1][IEXT + (COLON - INITIAL_STATE) - 1] = INITIAL_STATE + count 
count += 1
table[INITIAL_STATE - 1 + count - 1][IEXT + (COLON - INITIAL_STATE) - 1] = INITIAL_STATE + count 
count += 1
table[INITIAL_STATE - 1 + count - 1][IEXT + (EQUAL - INITIAL_STATE) - 1] = ASSIGN 

# Range
table[INITIAL_STATE - 1][IEXT + (DOT - INITIAL_STATE) - 1] = INITIAL_STATE + count 
count += 1
table[INITIAL_STATE - 1 + count - 1][IEXT + (DOT - INITIAL_STATE) - 1] = RANGE 

state = 0
newstate = 0

# Keyword
keywords = ["BEGIN", "DEFINITIONS", "AUTOMATIC", "TAGS", "VisibleString", "NumericString", "OPTIONAL", "FROM", "INTEGER", "END", "BOOLEAN", 
		"SIZE", "SEQUENCE"]
for j in range(0, len(keywords)):
        keyword = keywords[j]
        print keyword
	state = INITIAL_STATE
        for i in range(0, len(keyword)):
                if( (ord(keyword[i]) >= 65) and (90 >= ord(keyword[i])) ):
			cind = ICAP + (ord(keyword[i]) - 65)
			print "* %c points to %d" % (keyword[i], table[state - 1][cind]), 
			if( (TYPEDEF == table[state - 1][cind]) ):
				if(len(keyword) == i+1):
					print " -> Last character -> Point to KEYWORD state"
					table[state - 1][cind] = KEYWORD 
				else:
					newstate = INITIAL_STATE + count
					print " -> Create New State", newstate
					table.append([0 for k in range(ITOT)])
					for l in range(ICAP, ISMA):
						table[newstate - 1][l] = TYPEDEF
					for l in range(ISMA, ISYM):
						table[newstate - 1][l] = IDENTIFIER
					table[state - 1][cind] = INITIAL_STATE + count 
					state = INITIAL_STATE + count
					count += 1
			else:
				print " -> State Already created"
				state = table[state - 1][cind]
		else:
			cind = ISMA + (ord(keyword[i]) - 97)
			print "* %c points to %d" % (keyword[i], table[state - 1][cind]), 
			if(IDENTIFIER == table[state - 1][cind]):
				if(len(keyword) == i+1):
					print " -> Last character -> Point to KEYWORD state"
					table[state - 1][cind] = KEYWORD 
				else:
					newstate = INITIAL_STATE + count
					print " -> Create New State", newstate
					table.append([0 for k in range(ITOT)])
					for l in range(ICAP, ISMA):
						table[newstate - 1][l] = TYPEDEF
					for l in range(ISMA, ISYM):
						table[newstate - 1][l] = IDENTIFIER
					table[state - 1][cind] = INITIAL_STATE + count 
					state = INITIAL_STATE + count
					count += 1
			else:
				print " -> State Already created"
				state = table[state - 1][cind]

# Write to File 
fp.write("/\t");
for i in range(0, 10):
	fp.write(str(i) + " ");

for i in range(10, 36):
	fp.write(chr(65 + i - 10) + " ");

for i in range(36, 62):
	fp.write(chr(97 + i - 36) + " ");

fp.write("{ ");
fp.write("} ");
fp.write(", ");
fp.write("( ");
fp.write(") ");
fp.write("| ");
fp.write("\" ");

fp.write("- ");
fp.write(": ");
fp.write("= ");
fp.write(".");
fp.write("\n");

for i in range(len(table)):
	fp.write("State" + str(i+1) + "\t")
	for j in range(len(table[0])):
		fp.write( str(table[i][j]) + " " )

	fp.write("\n");

'''
print('\n'.join([''.join(['{:4}'.format(item) for item in row]) 
      for row in table]))
'''
