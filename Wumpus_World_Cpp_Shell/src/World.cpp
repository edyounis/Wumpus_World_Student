// ======================================================================
// FILE:        World.cpp
//
// AUTHOR:      Abdullah Younis
//
// DESCRIPTION: This file contains the world class, which is responsible
//              for everything game related.
//
// NOTES:       - Don't make changes to this file.
// ======================================================================

#include "World.hpp"

using namespace std;

// ===============================================================
// =				Constructor and Destructor
// ===============================================================	

World::World ( bool _debug, bool _randomAI, bool _manualAI, string filename )
{
	// Operation Flags
	debug        = _debug;
	manualAI     = _manualAI;
	
	// Agent Initialization
	goldLooted   = false;
	hasArrow     = true;
	bump         = false;
	scream       = false;
	score        = 0;
	agentDir     = 0;
	agentX       = 0;
	agentY       = 0;
	lastAction   = Agent::CLIMB;
	
	if ( _randomAI )
		agent = new RandomAI();
	else if ( _manualAI )
		agent = new ManualAI();
	else
		agent = new MyAI();
	
	// Board Initialization
	if ( filename != "" )
	{
		ifstream file;
		file.open(filename);
		
		file >> colDimension >> rowDimension;
		if (file.fail())
			throw exception();

		board = new Tile*[colDimension];
		for ( int index = 0; index < colDimension; ++index )
			board[index] = new Tile[rowDimension];

		addFeatures ( file );
		file.close();
	}
	else
	{
		colDimension = 4;
		rowDimension = 4;
		
		board = new Tile*[colDimension];
		for ( int index = 0; index < colDimension; ++index )
			board[index] = new Tile[rowDimension];
			
		addFeatures ( );
	}
}

World::~World()
{
	for ( int index = 0; index < colDimension; ++index )
		delete [] board[index];
	
	delete [] board;
	delete agent;
}

// ===============================================================
// =					Engine Function
// ===============================================================	

int World::run ( void )
{	
	while ( score >= -1000 )
	{
		if ( debug || manualAI )
		{
			printWorldInfo();
			
			if ( !manualAI )
			{
				// Pause the game, only if manualAI isn't on
				// because manualAI pauses for us
				cout << "Press ENTER to continue..." << endl;
				cin.ignore( 999, '\n');
			}
		}
		
		// Get the move
		lastAction = agent->getAction
		(
			board[agentX][agentY].stench,
			board[agentX][agentY].breeze,
			board[agentX][agentY].gold,
			bump,
			scream
		);

		// Make the move
		--score;
		bump   = false;
		scream = false;
		
		switch ( lastAction )
		{
			case Agent::TURN_LEFT:
				if (--agentDir > 3) agentDir = 3;	// This works because size_t is unsigned
				break;
				
			case Agent::TURN_RIGHT:
				if (++agentDir > 3) agentDir = 0;
				break;
				
			case Agent::FORWARD:
				if ( agentDir == 0 && agentX+1 < colDimension )
					++agentX;
				else if ( agentDir == 1 && agentY-1 < rowDimension ) // This still works because size_t
					--agentY;
				else if ( agentDir == 2 && agentX-1 < colDimension ) // gets big, instead of going negative
					--agentX;
				else if ( agentDir == 3 && agentY+1 < rowDimension )
					++agentY;
				else
					bump = true;
				
				if ( board[agentX][agentY].pit || board[agentX][agentY].wumpus )
				{
					score -= 1000;
					if (debug) printWorldInfo();
					return score;
				}
				break;
			
			case Agent::SHOOT:
				if ( hasArrow )
				{
					hasArrow = false;
					score -= 10;
					if ( agentDir == 0 )
					{
						for ( size_t x = agentX; x < colDimension; ++x )
							if ( board[x][agentY].wumpus )
							{
								board[x][agentY].wumpus = false;
								board[x][agentY].stench = true;
								scream = true;
							}
					}
					else if ( agentDir == 1 )
					{
						for ( size_t y = agentY; y < rowDimension; --y )
							if ( board[agentX][y].wumpus )
							{
								board[agentX][y].wumpus = false;
								board[agentX][y].stench = true;
								scream = true;
							}
					}
					else if ( agentDir == 2 )
					{
						for ( size_t x = agentX; x < colDimension; --x )
							if ( board[x][agentY].wumpus )
							{
								board[x][agentY].wumpus = false;
								board[x][agentY].stench = true;
								scream = true;
							}
					}
					else if ( agentDir == 3 )
					{
						for ( size_t y = agentY; y < rowDimension; ++y )
							if ( board[agentX][y].wumpus )
							{
								board[agentX][y].wumpus = false;
								board[agentX][y].stench = true;
								scream = true;
							}
					}
				}
				break;
				
			case Agent::GRAB:
				if ( board[agentX][agentY].gold )
				{
					board[agentX][agentY].gold = false;
					goldLooted = true;
				}
				break;
				
			case Agent::CLIMB:
				if ( agentX == 0 && agentY == 0 )
				{
					if ( goldLooted )
						score += 1000;
					if (debug) printWorldInfo();
					return score;
				}
				break;
		}
	}
	return score;
}

// ===============================================================
// =				World Generation Functions
// ===============================================================

void World::addFeatures ( void )
{		
	// Generate pits
	for ( int r = 0; r < rowDimension; ++r )
		for ( int c = 0; c < colDimension; ++c )
			if ( (c != 0 || r != 0) && randomInt(10) < 2 )
				addPit ( c, r );
	
	// Generate wumpus
	int wc = randomInt(colDimension);
	int wr = randomInt(rowDimension);
	
	while ( wc == 0 && wr == 0 )
	{
		wc = randomInt(colDimension);
		wr = randomInt(rowDimension);
	}
	
	addWumpus ( wc, wr );
	
	// Generate gold
	int gc = randomInt(colDimension);
	int gr = randomInt(rowDimension);
		
	while ( gc == 0 && gr == 0 )
	{
		gc = randomInt(colDimension);
		gr = randomInt(rowDimension);
	}
	
	addGold ( gc, gr );
}	

void World::addFeatures ( ifstream &file )
{
	int c, r;
	
	// Add the Wumpus
	file >> c >> r;
	if (file.fail())
		throw exception();
	addWumpus ( c, r );
	
	// Add the Gold
	file >> c >> r;
	if (file.fail())
		throw exception();
	addGold ( c, r );
	
	// Add the Pits
	int numOfPits;
	file >> numOfPits;
	if (file.fail())
		throw exception();
	
	while ( numOfPits > 0 && !file.eof() )
	{
		--numOfPits;
		file >> c >> r;
		if (file.fail())
			throw exception();
		addPit ( c, r );
	}
}

void World::addPit ( size_t c, size_t r )
{
	if ( isInBounds(c, r) )
	{
		board[c][r].pit = true;
		addBreeze ( c+1, r );
		addBreeze ( c-1, r );
		addBreeze ( c, r+1 );
		addBreeze ( c, r-1 );
	}
}

void World::addWumpus ( size_t c, size_t r )
{
	if ( isInBounds(c, r) )
	{
		board[c][r].wumpus = true;
		addStench ( c+1, r );
		addStench ( c-1, r );
		addStench ( c, r+1 );
		addStench ( c, r-1 );
	}
}

void World::addGold ( size_t c, size_t r )
{
	if ( isInBounds(c, r) )
		board[c][r].gold = true;
}

void World::addStench ( size_t c, size_t r )
{
	if ( isInBounds(c, r) )
		board[c][r].stench = true;
}

void World::addBreeze ( size_t c, size_t r )
{
	if ( isInBounds(c, r) )
		board[c][r].breeze = true;
}

bool World::isInBounds ( size_t c, size_t r )
{
	return ( c < colDimension && r < rowDimension );
}

// ===============================================================
// =				World Printing Functions
// ===============================================================

void World::printWorldInfo ( void )
{
	printBoardInfo();
	printAgentInfo();
}

void World::printBoardInfo ( void )
{
	for ( int r = rowDimension-1; r >= 0; --r )
	{
		for ( int c = 0; c < colDimension; ++c )
			printTileInfo ( c, r );
		cout << endl << endl;
	}
}

void World::printTileInfo ( size_t c, size_t r )
{
	string tileString = "";
	
	if (board[c][r].pit)    tileString.append("P");
	if (board[c][r].wumpus) tileString.append("W");
	if (board[c][r].gold)   tileString.append("G");
	if (board[c][r].breeze) tileString.append("B");
	if (board[c][r].stench) tileString.append("S");
	
	if ( agentX == c && agentY == r )
		tileString.append("@");
	
	tileString.append(".");
	
	cout << setw(8) << tileString;
}

void World::printAgentInfo ( void )
{
	cout << "Score: "       << score    << endl;
	cout << "AgentX: "      << agentX   << endl;
	cout << "AgentY: "      << agentY   << endl;
	printDirectionInfo();
	printActionInfo();
	printPerceptInfo();
}

void World::printDirectionInfo ( void )
{
	switch (agentDir)
	{
		case 0:
			cout << "AgentDir: Right" << endl;
			break;
			
		case 1:
			cout << "AgentDir: Down" << endl;
			break;
			
		case 2:
			cout << "AgentDir: Left" << endl;
			break;
			
		case 3:
			cout << "AgentDir: Up" << endl;
			break;
			
		default:
			cout << "AgentDir: Invalid" << endl;
	}
}

void World::printActionInfo ( void )
{
	switch (lastAction)
	{
		case Agent::TURN_LEFT:
			cout << "Last Action: Turned Left" << endl;
			break;
			
		case Agent::TURN_RIGHT:
			cout << "Last Action: Turned Right" << endl;
			break;
			
		case Agent::FORWARD:
			cout << "Last Action: Moved Forward" << endl;
			break;
			
		case Agent::SHOOT:
			cout << "Last Action: Shot the arrow" << endl;
			break;
			
		case Agent::GRAB:
			cout << "Last Action: Grabbed" << endl;
			break;
			
		case Agent::CLIMB:
			cout << "Last Action: Climbed" << endl;
			break;
			
		default:
			cout << "Last Action: Invalid" << endl;
	}
}

void World::printPerceptInfo ( void )
{
	string perceptString = "Percepts: ";
	
	if (board[agentX][agentY].stench) perceptString.append("Stench, ");
	if (board[agentX][agentY].breeze) perceptString.append("Breeze, ");
	if (board[agentX][agentY].gold)   perceptString.append("Glitter, ");
	if (bump)                         perceptString.append("Bump, ");
	if (scream)                       perceptString.append("Scream");
	
	if ( perceptString[perceptString.size()-1] == ' '
			&& perceptString[perceptString.size()-2] == ',' )
	{
		perceptString.pop_back();
		perceptString.pop_back();
	}
	
	cout << perceptString << endl;
}

// ===============================================================
// =					Helper Functions
// ===============================================================

int World::randomInt ( int limit )
{
	return rand() % limit;
}