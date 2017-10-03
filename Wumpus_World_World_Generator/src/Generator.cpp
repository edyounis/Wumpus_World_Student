// ======================================================================
// FILE:        Generator.cpp
//
// AUTHOR:      Abdullah Younis
//
// DESCRIPTION: This file contains the Wumpus World Generator script. 
// ======================================================================

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

// Randomly generate a int between 0 and limit-1
int randomInt ( int limit )
{
	return rand()%limit;
}
	
void genWorld ( int colDimension, int rowDimension, string filename )
{
	int wc, wr = 0;
	int gc, gr = 0;
	int numPits = 0;
	int pitx[256];
	int pity[256];
		
	// Generate pits
	for ( int r = 0; r < rowDimension; ++r )
		for ( int c = 0; c < colDimension; ++c )
			if ( (c != 0 || r != 0) && randomInt(10) < 2 )
			{
				pitx[numPits] = r;
				pity[numPits++] = c;
			}
		
	// Generate wumpus and gold
	wc = randomInt(colDimension);
	wr = randomInt(rowDimension);
	gc = randomInt(colDimension);
	gr = randomInt(rowDimension);
		
	while ( wc == 0 && wr == 0 )
	{
		wc = randomInt(colDimension);
		wr = randomInt(rowDimension);
	}
		
	while ( gc == 0 && gr == 0 )
	{
		gc = randomInt(colDimension);
		gr = randomInt(rowDimension);
	}
	
	ofstream file;
	file.open( filename );
	
	file << colDimension << '\t' << rowDimension;
	file << "\r\n" << wc << '\t' << wr;
	file << "\r\n" << gc << '\t' << gr;
	file << "\r\n" << numPits;
	for ( int i = 0; i < numPits; ++i )
		file << "\r\n" << pitx[i] << '\t' << pity[i];
	
	file.close();
}
	
int main ( int argc, char *argv[] )
{
	string baseFileName;
	int numOfFiles;
	int rowDimension;
	int colDimension;
	
	if ( argc == 5 )
	{
		try
		{
			baseFileName = argv[1];
			numOfFiles = atoi(argv[2]);
			colDimension = atoi(argv[3]);
			rowDimension = atoi(argv[4]);
		}
		catch ( const std::exception& e )
		{
			cout << "Usage: World_Generator Base_File_Name #ofWorlds rowDim colDim" << endl;
			return 0;
		}
	}
	else
	{
		cout << "Usage: World_Generator Base_File_Name #ofWorlds rowDim colDim" << endl;
		return 0;
	}

	srand( time(NULL) );	// Set random seed
	for (int i = 0; i < numOfFiles; ++i )
	{
		cout << "Creating world number: " << i << "." << endl;
		stringstream ss;
		ss << baseFileName << "_" << i << ".txt";
		genWorld( colDimension, rowDimension, ss.str() );
	}
	return 0;
}