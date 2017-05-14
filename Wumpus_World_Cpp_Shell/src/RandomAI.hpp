// ======================================================================
// FILE:        RandomAI.hpp
//
// AUTHOR:      Abdullah Younis
//
// DESCRIPTION: This file contains the random agent class, which
//              implements the agent interface. The RandomAI will return
//              a random move at every turn of the game, with only one
//              exception. If the agent perceives glitter, it will grab
//              the gold.
//
// NOTES:       - Don't make changes to this file.
// ======================================================================

#ifndef RANDOMAI_LOCK
#define RANDOMAI_LOCK

#include <cstdlib>
#include "Agent.hpp"

class RandomAI : public Agent
{
public:

	Action getAction
	(
		bool stench,
		bool breeze,
		bool glitter,
		bool bump,
		bool scream
	)
	{
		if ( glitter )
			return GRAB;
		
		return actions [ rand() % 6 ];
	}
	
private:

	const Action actions[6] =
	{
		TURN_LEFT,
		TURN_RIGHT,
		FORWARD,
		SHOOT,
		GRAB,
		CLIMB
	};
};

#endif