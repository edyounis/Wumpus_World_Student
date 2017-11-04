# ======================================================================
# FILE:        Makefile
#
# AUTHOR:      Abdullah Younis, Matthew Wo
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
#              - make clean_o    - deletes all the object files in bin
#
#              - make clean_gch  - deletes all of the precompiled headers
#
#              - make clean      - deletes everything inside bin
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
SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
EXECUTABLE = Wumpus_World
BIN_DIR = bin
DOC_DIR = doc

CC = g++
FLAGS = -g -c -std=c++0x

OBJECTS = $(patsubst $(SOURCE_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SOURCES))

all: dir $(BIN_DIR)/$(EXECUTABLE) clean_o clean_gch

dir:
	mkdir -p $(BIN_DIR)
	mkdir -p $(DOC_DIR)

$(BIN_DIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

$(OBJECTS): $(BIN_DIR)/%.o : $(SOURCE_DIR)/%.cpp
	$(CC) $(FLAGS) $< -o $@

clean_o:
	rm -f $(BIN_DIR)/*.o

clean_gch:
	rm -f $(SOURCE_DIR)/*.gch

clean:
	rm -f $(BIN_DIR)/*

submission: all
	@rm -f *.zip
	@echo ""
	@read -p "Enter Team Name (No spaces, '_', '/', '*'): " teamName; \
	 echo ""; \
	 read -p "Enter Student ID Number: " idNumber; \
	 echo ""; \
	 read -p "Enter Team Name: " teamName; \
	 echo ""; \
	 zip -rqq $${lastName}_$${idNumber}_$${teamName}.zip $(SOURCE_DIR) $(BIN_DIR) $(DOC_DIR)
