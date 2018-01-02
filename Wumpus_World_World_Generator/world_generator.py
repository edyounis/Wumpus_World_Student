# ======================================================================
# FILE:        Generator.py
#
# AUTHOR:      Abdullah Younis
#
# DESCRIPTION: This file contains the Wumpus World Generator script. 
# ======================================================================

import sys
import random

def randomInt ( limit ):
	return random.randrange(limit)
	
def genWorld ( colDimension, rowDimension, filename ):
	wc = 0
	wr = 0
	gc = 0
	gr = 0
	pits = []
	
	# Generate pits
	for r in range (rowDimension):
		for c in range (colDimension):
			if (c != 0 or r != 0) and randomInt(10) < 2:
				pits.append((r,c))

	# Generate wumpus and gold
	wc = randomInt(colDimension)
	wr = randomInt(rowDimension)
	gc = randomInt(colDimension)
	gr = randomInt(rowDimension)

	while wc == 0 and wr == 0:
		wc = randomInt(colDimension)
		wr = randomInt(rowDimension)

	while gc == 0 and gr == 0:
		gc = randomInt(colDimension)
		gr = randomInt(rowDimension)
	
	file = open(filename, "w")
	file.write( str(colDimension) + "\t" + str(rowDimension) + "\n" )
	file.write( str(wc) + "\t" + str(wr) + "\n" )
	file.write( str(gc) + "\t" + str(gr) + "\n" )

	file.write( str(len(pits)) + "\n" )
	for pit in pits:
		file.write( str(pit[0]) + "\t" + str(pit[1]) + "\n" )
	
	file.close();
	

if len(sys.argv) != 5:
	print ( "Usage: World_Generator Base_File_Name #ofWorlds rowDim colDim" )
	exit(0)

baseFileName = sys.argv[1]
numOfFiles   = int(sys.argv[2])
colDimension = int(sys.argv[3])
rowDimension = int(sys.argv[4])
	
for i in range(numOfFiles):
	print ( "Creating world number: " + str(i) + "." )
	genWorld( colDimension, rowDimension, baseFileName + "_" + str(i) + ".txt" )
