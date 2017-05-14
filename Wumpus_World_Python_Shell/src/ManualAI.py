# ======================================================================
# FILE:        ManualAI.py
#
# AUTHOR:      Abdullah Younis
#
# DESCRIPTION: This file contains the manual agent class, which
#              implements the agent interface. The ManualAI will allow
#              you to play the game as an omniscient agent. This will
#              allow you to get a feel for the game before starting to
#              code your agent.
#
# NOTES:       - The 'Get Input' part of the code will ignore all info
#                after the first letter, as well as, all whitespace
#                before the first letter.
#
#              - The 'Print Command Menu' part of the code states that
#                'c' will return the CLIMB action. This is true,
#                however, any key other than 'w,a,d,s,g' will return
#                the CLIMB action.
#
#              - Don't make changes to this file.
# ======================================================================

from Agent import Agent

class ManualAI ( Agent ):

    def getAction ( self, stench, breeze, glitter, bump, scream ):
        # Print Command Menu
        print ( "Press 'w' to Move Forward  'a' to 'Turn Left' 'd' to 'Turn Right'" )
        print ( "Press 's' to Shoot         'g' to 'Grab'      'c' to 'Climb'" )
        
        #Get Input
        userInput = input ( 'Please input: ' ).strip()
        while not userInput:
            userInput = input().strip()
        
        # Return Action Associated with Input
        if userInput[0] == 'w':
            return Agent.Action.FORWARD
            
        if userInput[0] == 'a':
            return Agent.Action.TURN_LEFT
            
        if userInput[0] == 'd':
            return Agent.Action.TURN_RIGHT
            
        if userInput[0] == 's':
            return Agent.Action.SHOOT
            
        if userInput[0] == 'g':
            return Agent.Action.GRAB
            
        return Agent.Action.CLIMB