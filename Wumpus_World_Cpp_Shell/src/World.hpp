// ======================================================================
// FILE:        World.hpp
//
// AUTHOR:      Abdullah Younis
//
// DESCRIPTION: This file contains the world class, which is responsible
//              for everything game related.
//
// NOTES:       - Don't make changes to this file.
// ======================================================================

#ifndef WORLD_LOCK
#define WORLD_LOCK

#include<iomanip>
#include<string>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<exception>
#include"Agent.hpp"
#include"ManualAI.hpp"
#include"RandomAI.hpp"
#include"MyAI.hpp"

class World
{
public:

	// Constructor
	World ( bool debug = false, bool randomAI = false, bool manualAI = false, std::string filename = "" );
	
	// Destructor
	~World();
	
	// Engine Function
	int	run	( void );
	
private:
	// Tile Structure
	struct Tile
	{
		bool pit    = false;
		bool wumpus = false;
		bool gold   = false;
		bool breeze = false;
		bool stench = false;
	};
	
	// Operation Variables
	bool 	debug;			// If true, displays board info after every move
	bool	manualAI;		// If true, alters the behavior of debug for flow purposes
	
	// Agent Variables
	Agent* 	agent;			// The agent
	int 	score;			// The agent's score
	bool	goldLooted;		// True if gold was successfuly looted
	bool	hasArrow;		// True if the agent can shoot
	bool	bump;			// Bump percept flag
	bool	scream;			// Scream percept flag
	size_t	agentDir;		// The direction the agent is facing: 0 - right, 1 - down, 2 - left, 3 - up
	size_t	agentX;			// The column where the agent is located ( x-coord = col-coord )
	size_t	agentY;			// The row where the agent is located ( y-coord = row-coord )

	Agent::Action	lastAction;	// The last action the agent made
	
	// Board Variables
	size_t	colDimension;	// The number of columns the game board has
	size_t	rowDimension;	// The number of rows the game board has
	Tile**	board;			// The game board
	
	// World Generation Functions
	void 	addFeatures	( void );					// Populates the board with random features
	void	addFeatures ( std::ifstream &file );	// Populates the board with features specified in file
	void 	addPit 		( size_t c, size_t r );
	void 	addWumpus	( size_t c, size_t r );
	void 	addGold		( size_t c, size_t r );
	void 	addStench	( size_t c, size_t r );
	void 	addBreeze	( size_t c, size_t r );
	bool 	isInBounds	( size_t c, size_t r );
	
	// World Printing Functions
	void	printWorldInfo		( void );
	void	printBoardInfo		( void );
	void	printTileInfo		( size_t c, size_t r );
	void	printAgentInfo		( void );
	void	printDirectionInfo	( void );
	void	printActionInfo		( void );
	void	printPerceptInfo	( void );

	// Helper Functions
	int		randomInt	( int limit );		// Randomly generate a int in the range [0, limit)
};

#endif /* WORLD_LOCK */