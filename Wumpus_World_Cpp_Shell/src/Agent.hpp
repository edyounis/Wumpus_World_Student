// ======================================================================
// FILE:        Agent.hpp
//
// AUTHOR:      Abdullah Younis
//
// DESCRIPTION: This file contains the abstract agent class, which
//              details the interface for a wumpus agent. The actuators
//              are listed in the 'Action' enum, while the sensors are
//              parameters to the abstract function 'getAction'. Any
//              agent will need to implement the getAction function,
//              which returns an Action for every turn in the game.
//
// NOTES:       - An agent is anything that can be viewed as perceiving
//                its environment through sensors and acting upon that
//                environment through actuators
//
//              - Throughout this project Agent and AI are
//                interchangeable
//
//              - Don't make changes to this file.
// ======================================================================

#ifndef AGENT_LOCK
#define AGENT_LOCK

class Agent
{
public:

	// Actuators
	enum Action
	{
		TURN_LEFT,
		TURN_RIGHT,
		FORWARD,
		SHOOT,
		GRAB,
		CLIMB
	};
	
	virtual Action getAction
	(
		// Sensors
		bool stench,
		bool breeze,
		bool glitter,
		bool bump,
		bool scream
		
	) = 0;
};

#endif