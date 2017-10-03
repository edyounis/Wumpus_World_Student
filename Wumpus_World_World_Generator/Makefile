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

BIN_DIR = bin
SRC_DIR = src

all: compile
	@-rm -rf Worlds
	@-mkdir Worlds
	@echo ""
	@read -p "Enter Row Dimension: " rDim; \
	 echo ""; \
	 read -p "Enter Column Dimension: " cDim; \
	 echo ""; \
	 read -p "How many worlds created?: " count; \
	 echo ""; \
	 bin/World_Generator Worlds/world $${count} $${rDim} $${cDim}

tournamentSet: compile
	@-rm -rf Worlds
	@-mkdir Worlds
	@bin/World_Generator Worlds/world4x4 500 4 4
	@bin/World_Generator Worlds/world4x5 500 4 5
	@bin/World_Generator Worlds/world4x6 500 4 6
	@bin/World_Generator Worlds/world4x7 500 4 7
	@bin/World_Generator Worlds/world5x4 500 5 4
	@bin/World_Generator Worlds/world5x5 500 5 5
	@bin/World_Generator Worlds/world5x6 500 5 6
	@bin/World_Generator Worlds/world5x7 500 5 7
	@bin/World_Generator Worlds/world6x4 500 6 4
	@bin/World_Generator Worlds/world6x5 500 6 5
	@bin/World_Generator Worlds/world6x6 500 6 6
	@bin/World_Generator Worlds/world6x7 500 6 7
	@bin/World_Generator Worlds/world7x4 500 7 4
	@bin/World_Generator Worlds/world7x5 500 7 5
	@bin/World_Generator Worlds/world7x6 500 7 6
	@bin/World_Generator Worlds/world7x7 500 7 7

compile:
	@-rm -rf $(BIN_DIR)
	@-mkdir -p $(BIN_DIR)
	@-g++ -std=c++0x src/*.cpp -o bin/World_Generator
