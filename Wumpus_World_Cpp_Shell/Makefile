# ======================================================================
# FILE:        Makefile
#
# AUTHOR:      Abdullah Younis
#
# DESCRIPTION: This file contains useful commands for this project. You
#              may use the following commands:
#
#              - make            - compiles the project and places
#                                  the executable in the bin folder
#
#              - make submission - creates the the submission, you will
#                                  submit.
#
#              - Don't make changes to this file.
# ======================================================================

RAW_SOURCES = \
	Agent.hpp\
	Main.cpp\
	MyAI.cpp\
	MyAI.hpp\
	RandomAI.hpp\
	ManualAI.hpp\
	World.cpp\
	World.hpp

SOURCE_DIR = src
BIN_DIR = bin
DOC_DIR = doc
SOURCES = $(foreach s, $(RAW_SOURCES), $(SOURCE_DIR)/$(s))

all: $(SOURCES)
	@rm -rf $(BIN_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(DOC_DIR)
	@g++ -std=c++0x $(SOURCES) -o $(BIN_DIR)/Wumpus_World

submission: all
	@rm -f *.zip
	@echo ""
	@read -p "Enter Last Name: " lastName; \
	 echo ""; \
	 read -p "Enter Student ID Number: " idNumber; \
	 echo ""; \
	 read -p "Enter Team Name: " teamName; \
	 echo ""; \
	 zip -rqq $${lastName}_$${idNumber}_$${teamName}.zip $(SOURCE_DIR) $(BIN_DIR) $(DOC_DIR)
