# ======================================================================
# FILE:        Makefile
#
# AUTHOR:      Abdullah Younis
#
# DESCRIPTION: This file contains useful commands for this project. You
#              may use the following commands:
#
#              - make            	- Generate a set of worlds.
#
#              - make tournamentSet - Generates the same set of worlds
#                                  	  used in the tournament.
# ======================================================================


all:
	@-rm -rf Worlds
	@-mkdir Worlds
	@echo ""
	@read -p "Enter Row Dimension: " rDim; \
	 echo ""; \
	 read -p "Enter Column Dimension: " cDim; \
	 echo ""; \
	 read -p "How many worlds created?: " count; \
	 echo ""; \
	 python3 world_generator.py Worlds/world $${count} $${rDim} $${cDim}

tournamentSet:
	@-rm -rf Worlds
	@-mkdir Worlds
	@python3 world_generator.py Worlds/world4x4 2500 4 4
	@python3 world_generator.py Worlds/world4x5 500 4 5
	@python3 world_generator.py Worlds/world4x6 500 4 6
	@python3 world_generator.py Worlds/world4x7 500 4 7
	@python3 world_generator.py Worlds/world5x4 500 5 4
	@python3 world_generator.py Worlds/world5x5 500 5 5
	@python3 world_generator.py Worlds/world5x6 500 5 6
	@python3 world_generator.py Worlds/world5x7 500 5 7
	@python3 world_generator.py Worlds/world6x4 500 6 4
	@python3 world_generator.py Worlds/world6x5 500 6 5
	@python3 world_generator.py Worlds/world6x6 500 6 6
	@python3 world_generator.py Worlds/world6x7 500 6 7
	@python3 world_generator.py Worlds/world7x4 500 7 4
	@python3 world_generator.py Worlds/world7x5 500 7 5
	@python3 world_generator.py Worlds/world7x6 500 7 6
	@python3 world_generator.py Worlds/world7x7 500 7 7
