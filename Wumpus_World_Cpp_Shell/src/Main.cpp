// ======================================================================
// FILE:        Main.cpp
//
// AUTHOR:      Abdullah Younis
//
// DESCRIPTION: This file is the entry point for the program. The main
//              function serves a couple purposes: (1) It is the
//              interface with the command line. (2) It reads the files,
//              creates the World object, and passes that all the
//              information necessary. (3) It is in charge of outputing
//              information.
//
// NOTES:       - Syntax:
//
//                	Wumpus_World [Options] [InputFile] [OutputFile]
//
//                  Options:
//						-m Use the ManualAI instead of MyAI.
//						-r Use the RandomAI instead of MyAI.
//                      -d Debug mode, which displays the game board
//                         after every mode. Useless with -m.
//                      -h Displays help menu and quits.
//                      -v Verbose mode displays world file names before
//                         loading them.
//                      -f treats the InputFile as a folder containing
//                         worlds. This will trigger the program to
//                         display the average score and standard
//                         deviation instead of a single score. InputFile
//                         must be entered with this option.
//
//                  InputFile: A path to a valid Wumpus World File, or
//                             folder with -f. This is optional unless
//                             used with -f or OutputFile.
//
//                  OutputFile: A path to a file where the results will
//                              be written. This is optional.
//
//              - If -m and -r are turned on, -m will be turned off.
//
//              - Don't make changes to this file.
// ======================================================================
 
#include <iostream>
#include <ctime>
#include <dirent.h>
#include <cmath>
#include "World.hpp"

using namespace std;

int main ( int argc, char *argv[] )
{
	// Set random seed
	srand( time ( NULL ) );
	
	if ( argc == 1 )
	{
		// Run on a random world and exit
		World world;
		int score = world.run();
		cout << "Your agent scored: " << score << endl;
		return 0;
	}

	// Important Variables
	bool 	debug        = false;
	bool	verbose      = false;
	bool 	randomAI     = false;
	bool 	manualAI      = false;
	bool 	folder       = false;
	string	worldFile    = "";
	string	outputFile   = "";
	string 	firstToken 	 = argv[1];

	// If there are options
	if ( firstToken[0] == '-' )
	{
		// Parse Options
		for ( int index = 1; index < firstToken.size(); ++index )
		{
			switch ( firstToken[index] )
			{
				case '-':
					break;
				
				case 'f':
				case 'F':
					folder = true;
					break;
					
				case 'v':
				case 'V':
					verbose = true;
					break;
					
				case 'r':
				case 'R':
					randomAI = true;
					break;
					
				case 'm':
				case 'M':
					manualAI = true;
					break;
					
				case 'd':
				case 'D':
					debug = true;
					break;
					
				case 'h':
				case 'H':
				default:
					cout << "Wumpus_World [Options] [InputFile] [OutputFile]" << endl;
					cout << endl;
					cout << "Options:" << endl;
					cout << "\t-m Use the ManualAI instead of MyAI." << endl;
					cout << "\t-r Use the RandomAI instead of MyAI." << endl;
					cout << "\t-d Debug mode, which displays the game board" << endl;
					cout << "\t   after every mode. Useless with -m." << endl;
					cout << "\t-h Displays help menu and quits." << endl;
					cout << "\t-v Verbose mode displays world file names before" << endl;
					cout << "\t   loading them." << endl;
					cout << "\t-f treats the InputFile as a folder containing" << endl;
					cout << "\t   worlds. This will trigger the program to" << endl;
					cout << "\t   display the average score and standard" << endl;
					cout << "\t   deviation instead of a single score. InputFile" << endl;
					cout << "\t   must be entered with this option." << endl;
					cout << endl;
					cout << "InputFile: A path to a valid Wumpus World File, or" << endl;
					cout << "           folder with -f. This is optional unless" << endl;
					cout << "           used with -f." << endl;
					cout << endl;
					cout << "OutputFile: A path to a file where the results will" << endl;
					cout << "            be written. This is optional." << endl;
					cout << endl;
					return 0;
			}
		}
		
		if ( randomAI && manualAI )
		{
			// If both AI's on, turn one off and let the user know.
			manualAI = false;
			cout << "[WARNING] Manual AI and Random AI both on; Manual AI was turned off." << endl;
		}
		
		if ( argc >= 3 )
			worldFile = argv[2];
		if ( argc >= 4 )
			outputFile = argv[3];
	}
	else
	{
		if ( argc >= 2 )
			worldFile = argv[1];
		if ( argc >= 3 )
			outputFile = argv[2];
	}
	
	if ( worldFile == "" )
	{
		if ( folder )
			cout << "[WARNING] No folder specified; running on a random world." << endl;
		World world ( debug, randomAI, manualAI );
		int score = world.run();
		cout << "The agent scored: " << score << endl;
		return 0;
	}
	
	if ( folder )
	{
		DIR *dir;
		if ( ( dir = opendir (worldFile.c_str()) ) == NULL )
		{
			cout << "[ERROR] Failed to open directory." << endl;
			return 0;
		}
		
		struct dirent *ent;
		
		int		numOfScores        = 0;
		double	sumOfScores        = 0;
		double	sumOfScoresSquared = 0;
		
		while ( ( ent = readdir (dir) ) != NULL )
		{
			if ( ent->d_name[0] == '.' )
				continue;
			
			if ( verbose )
				cout << "Running world: " << ent->d_name << endl;
			
			string individualWorldFile = "./" + worldFile + "/" + ent->d_name;
			
			int score;
			try
			{
				World world ( debug, randomAI, manualAI, individualWorldFile );
				score = world.run();
			}
			catch (...)
			{
				numOfScores = 0;
				sumOfScores = 0;
				sumOfScoresSquared = 0;
				break;
			}

			numOfScores += 1;
			sumOfScores += score;
			sumOfScoresSquared += score*score;
		}
		
		closedir (dir);
		
		double avg = (float)sumOfScores / (float)numOfScores;
		double std_dev = sqrt ( (sumOfScoresSquared - ((sumOfScores*sumOfScores) / (float)numOfScores) ) / (float)numOfScores );
		
		if ( outputFile == "" )
		{
			cout << "The agent's average score: " << avg << endl;
			cout << "The agent's standard deviation: " << std_dev << endl;
		}
		else
		{
			ofstream file;
			file.open( outputFile );
			file << "SCORE: " << avg << endl;
			file << "STDEV: " << std_dev << endl;
			file.close();
		}
		return 0;
	}
	

	try
	{
		if ( verbose )
			cout << "Running world: " << worldFile << endl;
		
		World world ( debug, randomAI, manualAI, worldFile );
		int score = world.run();
		if ( outputFile == "" )
		{
			cout << "The agent scored: " << score << endl;
		}
		else
		{
			ofstream file;
			file.open ( outputFile );
			file << "SCORE: " << score << endl;
			file.close();
		}
	}
	catch ( const std::exception& e )
	{
		cout << "[ERROR] Failure to open file." << endl;
	}
	return 0;
}