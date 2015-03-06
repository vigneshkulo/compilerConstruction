table = [['-' for i in range(73)] for j in range(20)]

#1. Typedef State
for i in range(0, 62):
	table[0][i] = 1

#2. Identifier State
for i in range(0, 62):
	table[1][i] = 2

#3. Number State
for i in range(0, 10):
	table[2][i] = 3

#4. Assign State

#5. Range State

#6. Keyword State

#7. Quote State

#8. Lparen State

#9. Rparen State

#10. Comma State

#11. Hyphen State

#12. Colon State
	table[11][67] = 4

#13. Equals State
#14. Lcurly State
#15. Bar State
#16. Rcurly State

fp = open("New", "w")

# Initial State
for i in range(0, 10):
	table[16][i] = 3 
for i in range(10, 36):
	table[16][i] = 1
for i in range(36, 62):
	table[16][i] = 2
for i in range(62, 73):
	table[16][i] = (i % 62) + 7


# Write to File 
fp.write("/\t");
for i in range(0, 10):
	fp.write(str(i) + " ");

for i in range(10, 36):
	fp.write(chr(65 + i - 10) + " ");

for i in range(36, 62):
	fp.write(chr(97 + i - 36) + " ");

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

for i in range(len(table)):
	fp.write("State" + str(i+1) + "\t")
	for j in range(len(table[0])):
		fp.write( str(table[i][j]) + " " )

	fp.write("\n");

'''
print('\n'.join([''.join(['{:4}'.format(item) for item in row]) 
      for row in table]))
'''
