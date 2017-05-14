// ======================================================================
// FILE:        RandomAI.java
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

import java.util.Random;

public class RandomAI extends Agent
{
	
	public Action getAction
	(
		boolean stench,
		boolean breeze,
		boolean glitter,
		boolean bump,
		boolean scream
	)
	{
		if ( glitter )
			return Action.GRAB;
		
		return actions [ rand.nextInt ( actions.length ) ];
	}
	
	private final Action[] actions =
	{
		Action.TURN_LEFT,
		Action.TURN_RIGHT,
		Action.FORWARD,
		Action.SHOOT,
		Action.GRAB,
		Action.CLIMB
	};
	
	private Random rand = new Random();
	
}