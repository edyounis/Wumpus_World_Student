// ======================================================================
// FILE:        ManualAI.hpp
//
// AUTHOR:      Abdullah Younis
//
// DESCRIPTION: This file contains the manual agent class, which
//              implements the agent interface. The ManualAI will allow
//              you to play the game as an omniscient agent. This will
//              allow you to get a feel for the game before starting to
//              code your agent.
//
// NOTES:       - The 'Get Input' part of the code will ignore all info
//                after the first letter, as well as, all whitespace
//                before the first letter.
//
//              - The 'Print Command Menu' part of the code states that
//                'c' will return the CLIMB action. This is true,
//                however, any key other than 'w,a,d,s,g' will return
//                the CLIMB action.
//
//              - Don't make changes to this file.
// ======================================================================

#ifndef MANUALAI_LOCK
#define MANUALAI_LOCK

#include<iostream>
#include "Agent.hpp"

class ManualAI : public Agent
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
		// Print Command Menu
		std::cout << "Press 'w' to Move Forward  'a' to 'Turn Left' 'd' to 'Turn Right'" << std::endl;
		std::cout << "Press 's' to Shoot         'g' to 'Grab'      'c' to 'Climb'" << std::endl;
		
		// Get Input
		std::cout << "Please input: ";
		char userInput;
		std::cin >> userInput;
		std::cin.ignore(9999, '\n');
		
		// Return Action Associated with Input
		if ( userInput == 'w' )
			return FORWARD;
		
		if ( userInput == 'a' )
			return TURN_LEFT;
		
		if ( userInput == 'd' )
			return TURN_RIGHT;
		
		if ( userInput == 's' )
			return SHOOT;
		
		if ( userInput == 'g' )
			return GRAB;

		return CLIMB;
	}
};

#endif