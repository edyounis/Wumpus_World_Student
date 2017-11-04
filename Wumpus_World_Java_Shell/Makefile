# ======================================================================
# FILE:        Makefile
#
# AUTHOR:      Abdullah Younis
#
# DESCRIPTION: This file contains useful commands for this project. You
#              may use the following commands:
#
#              - make            - compiles the project and places
#                                  the jar file in the bin folder
#
#              - make submission - creates the the submission, you will
#                                  submit.
# ======================================================================

RAW_SOURCES = \
	Agent.java\
	Main.java\
	MyAI.java\
	RandomAI.java\
	ManualAI.java\
	World.java

SOURCE_DIR = src
BIN_DIR = bin
DOC_DIR = doc
SOURCES = $(foreach s, $(RAW_SOURCES), $(SOURCE_DIR)/$(s))

all: $(SOURCES)
	@rm -rf $(BIN_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(DOC_DIR)
	@javac $(SOURCES) -d $(BIN_DIR)
	@rm -f $(BIN_DIR)/Wumpus_World.jar
	@jar -cvfe bin/Wumpus_World.jar Main -C $(BIN_DIR) . > /dev/null
	@rm -f $(BIN_DIR)/*.class

submission: all
	@rm -f *.zip
	@echo ""
	@read -p "Enter Team Name (No spaces, '_', '/', '*'): " teamName; \
	 echo ""; \
	 zip -rqq s_$${teamName}.zip $(SOURCE_DIR) $(BIN_DIR) $(DOC_DIR)

