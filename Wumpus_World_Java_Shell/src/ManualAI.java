// ======================================================================
// FILE:        ManualAI.java
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

import java.util.Scanner;

public class ManualAI extends Agent
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
		// Print Command Menu
		System.out.println ( "Press 'w' to Move Forward  'a' to 'Turn Left' 'd' to 'Turn Right'" );
		System.out.println ( "Press 's' to Shoot         'g' to 'Grab'      'c' to 'Climb'" );
		
		Scanner in = new Scanner(System.in);
		// Get Input
		System.out.print ( "Please input: " );
		String userInput = in.next();

		// Return Action Associated with Input
		if ( userInput.charAt(0) == 'w' )
			return Action.FORWARD;
		
		if ( userInput.charAt(0) == 'a' )
			return Action.TURN_LEFT;
		
		if ( userInput.charAt(0) == 'd' )
			return Action.TURN_RIGHT;
		
		if ( userInput.charAt(0) == 's' )
			return Action.SHOOT;
		
		if ( userInput.charAt(0) == 'g' )
			return Action.GRAB;
		
		return Action.CLIMB;
	}
	
	
}