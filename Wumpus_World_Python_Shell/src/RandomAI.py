# ======================================================================
# FILE:        RandomAI.py
#
# AUTHOR:      Abdullah Younis
#
# DESCRIPTION: This file contains the random agent class, which
#              implements the agent interface. The RandomAI will return
#              a random move at every turn of the game, with only one
#              exception. If the agent perceives glitter, it will grab
#              the gold.
#
# NOTES:       - Don't make changes to this file.
# ======================================================================

from Agent import Agent
import random

class RandomAI ( Agent ):

    def getAction ( self, stench, breeze, glitter, bump, scream ):
        if glitter:
            return Agent.Action.GRAB;

        return self.__actions [ random.randrange ( len ( self.__actions ) ) ]
    
    __actions = [
        Agent.Action.TURN_LEFT,
        Agent.Action.TURN_RIGHT,
        Agent.Action.FORWARD,
        Agent.Action.CLIMB,
        Agent.Action.SHOOT,
        Agent.Action.GRAB
    ]