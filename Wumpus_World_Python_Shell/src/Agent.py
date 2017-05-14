# ======================================================================
# FILE:        Agent.py
#
# AUTHOR:      Abdullah Younis
#
# DESCRIPTION: This file contains the abstract agent class, which
#              details the interface for a wumpus agent. The actuators
#              are listed in the 'Action' enum, while the sensors are
#              parameters to the abstract function 'getAction'. Any
#              agent will need to implement the getAction function,
#              which returns an Action for every turn in the game.
#
# NOTES:       - An agent is anything that can be viewed as perceiving
#                its environment through sensors and acting upon that
#                environment through actuators
#
#              - Throughout this project Agent and AI are
#                interchangeable
#
#              - Don't make changes to this file.
# ======================================================================

from abc import ABCMeta, abstractmethod
from enum import Enum

class Agent ( metaclass=ABCMeta ):

    # Actuators
    class Action ( Enum ):
        TURN_LEFT  = 1
        TURN_RIGHT = 2
        FORWARD    = 3
        SHOOT      = 4
        GRAB       = 5
        CLIMB      = 6

    @abstractmethod
    def getAction ( self,
    
        # Sensors
        stench,
        breeze,
        glitter,
        bump,
        scream
    ):
        pass