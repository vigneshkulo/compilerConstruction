import random

fp = open("dfaTable", "w")

fp.write("/\t");
for j in range(48, 58):
	fp.write("%c " % (j));
for j in range(65, 91):
	fp.write("%c " % (j));
for j in range(97, 123):
	fp.write("%c " % (j));
fp.write("\" ");
fp.write("( ");
fp.write(") ");
fp.write(", ");
fp.write("- ");
fp.write(": ");
fp.write("= ");
fp.write("{ ");
fp.write("| ");
fp.write("} ");
fp.write(".");
fp.write("\n");

fp.write("State1\t");
for j in range(48, 58):
	fp.write("4 ");
fp.write("43 "); # A
fp.write("29 "); # B
fp.write("2 "); # C
fp.write("33 "); # D
fp.write("94 "); # E
fp.write("85 "); # F
fp.write("2 "); # G
fp.write("2 "); # H
fp.write("88 "); # I
fp.write("2 "); # J
fp.write("2 "); # K
fp.write("2 "); # L
fp.write("2 "); # M
fp.write("66 "); # N
fp.write("78 "); # O
fp.write("2 "); # P
fp.write("2 "); # Q
fp.write("2 "); # R
fp.write("19 "); # S
fp.write("51 "); # T
fp.write("2 "); # U
fp.write("54 "); # V
fp.write("2 "); # W
fp.write("2 "); # X
fp.write("2 "); # Y
fp.write("2 "); # Z

for j in range(97, 123):
	fp.write("3 ");
fp.write("5 ");
fp.write("6 ");
fp.write("7 ");
fp.write("8 ");
fp.write("9 ");
fp.write("10 ");
fp.write("11 ");
fp.write("12 ");
fp.write("13 ");
fp.write("14 ");
fp.write("17 ");
fp.write("\n");

fp.write("State2\t");
for j in range(48, 58):
	fp.write("2 ");
for j in range(65, 91):
	fp.write("2 ");
for j in range(97, 123):
	fp.write("2 ");
fp.write("- " * 11);
fp.write("\n");

fp.write("State3\t");
for j in range(48, 58):
	fp.write("3 ");
for j in range(65, 91):
	fp.write("3 ");
for j in range(97, 123):
	fp.write("3 ");
fp.write("- " * 11);
fp.write("\n");

fp.write("State4\t");
for j in range(48, 58):
	fp.write("4 ");
for j in range(65, 91):
	fp.write("- ");
for j in range(97, 123):
	fp.write("- ");
fp.write("- " * 11);
fp.write("\n");

fp.write("State5\t");
fp.write("- " * 73);
fp.write("\n");

fp.write("State6\t");
fp.write("- " * 73);
fp.write("\n");

fp.write("State7\t");
fp.write("- " * 73);
fp.write("\n");

fp.write("State8\t");
fp.write("- " * 73);
fp.write("\n");

fp.write("State9\t");
fp.write("- " * 73);
fp.write("\n");

fp.write("State10\t");
for j in range(48, 58):
	fp.write("- ");
for j in range(65, 91):
	fp.write("- ");
for j in range(97, 123):
	fp.write("- ");
fp.write("- ");
fp.write("- ");
fp.write("- ");
fp.write("- ");
fp.write("- ");
fp.write("15 ");
fp.write("- ");
fp.write("- ");
fp.write("- ");
fp.write("- ");
fp.write("- ");
fp.write("\n");

fp.write("State11\t");
fp.write("- " * 73);
fp.write("\n");

fp.write("State12\t");
fp.write("- " * 73);
fp.write("\n");

fp.write("State13\t");
fp.write("- " * 73);
fp.write("\n");

fp.write("State14\t");
fp.write("- " * 73);
fp.write("\n");

fp.write("State15\t");
for j in range(48, 58):
	fp.write("- ");
for j in range(65, 91):
	fp.write("- ");
for j in range(97, 123):
	fp.write("- ");
fp.write("- ");
fp.write("- ");
fp.write("- ");
fp.write("- ");
fp.write("- ");
fp.write("- ");
fp.write("16 ");
fp.write("- ");
fp.write("- ");
fp.write("- ");
fp.write("- ");
fp.write("\n");

fp.write("State16\t");
fp.write("- " * 73);
fp.write("\n");

fp.write("State17\t");
fp.write("- " * 72);
fp.write("18 ");
fp.write("\n");

fp.write("State18\t");
fp.write("- " * 73);
fp.write("\n");

fp.write("State19\t");
fp.write("2 " * 14);
fp.write("23 "); # E
fp.write("2 " * 3);
fp.write("20 "); # I
fp.write("2 " * 44);
fp.write("- " * 17);
fp.write("\n");

# SIZE
fp.write("State20\t");
fp.write("2 " * 35);
fp.write("21 "); # Z
fp.write("2 " * 26);
fp.write("- " * 11);
fp.write("\n");

fp.write("State21\t");
fp.write("2 " * 14);
fp.write("22 "); # E
fp.write("2 " * 47);
fp.write("- " * 11);
fp.write("\n");

fp.write("State22\t");
fp.write("- " * 73);
fp.write("\n");

# SEQUENCE
fp.write("State23\t");
fp.write("2 " * 26);
fp.write("24 "); # Q
fp.write("2 " * 35);
fp.write("- " * 11);
fp.write("\n");

fp.write("State24\t");
fp.write("2 " * 30);
fp.write("25 "); # U
fp.write("2 " * 31);
fp.write("- " * 11);
fp.write("\n");

fp.write("State25\t");
fp.write("2 " * 14);
fp.write("26 "); # E
fp.write("2 " * 47);
fp.write("- " * 11);
fp.write("\n");

fp.write("State26\t");
fp.write("2 " * 23);
fp.write("27 "); # N
fp.write("2 "* 38);
fp.write("- " * 11);
fp.write("\n");

fp.write("State27\t");
fp.write("2 " * 12);
fp.write("28 "); # C
fp.write("2 " * 49);
fp.write("- " * 11);
fp.write("\n");

fp.write("State28\t");
fp.write("2 " * 14);
fp.write("22 "); # E
fp.write("2 " * 47);
fp.write("- " * 11);
fp.write("\n");

# BEGIN
fp.write("State29\t");
fp.write("2 " * 14);
fp.write("30 "); # E
fp.write("2 " * 9);
fp.write("96 "); # O
fp.write("2 " * 37);
fp.write("- " * 11);
fp.write("\n");

st = 29
keywords = ["EGIN", "DEFINITIONS", "AUTOMATIC", "TAGS", "VisibleString", "NumericString", "OPTIONAL", "FROM", "INTEGER", "END", "OOLEAN"]
for j in range(0, len(keywords)):
	keyword = keywords[j] 
	print keyword, st + 1
	for i in range(1, len(keyword)):
		st = st + 1
		stName = "State" + str(st)
		fp.write(stName + "\t");
		fp.write("2 " * 10);

		if( (ord(keyword[i]) >= 65) and (90 >= ord(keyword[i])) ):
			fp.write("2 " * (ord(keyword[i]) - 65));
			if (len(keyword) - 1 == i):
				fp.write( "22 ");
			else:
				fp.write( str(st + 1) + " ");
			fp.write("2 " * (90 - ord(keyword[i])));
			fp.write("2 " * 26);
		else:
			fp.write("2 " * 26);
			fp.write("2 " * (ord(keyword[i]) - 97));
			if (len(keyword) - 1 == i):
				fp.write( "22 ");
			else:
				fp.write( str(st + 1) + " ");
			fp.write("2 " * (122 - ord(keyword[i])));

		fp.write("- " * 11);
		fp.write("\n");

fp.close()
