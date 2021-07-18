################################### METADATA ###################################

# Contributors: roadelou
# Contacts: 
# Creation Date: 2021-07-18
# Language: Makefile

################################### ALIASES ####################################

# The header files.
HEAD = include/*.h
#
# The flag to include the header of the project.
INC_FLAG = -I ./include
#
# The source file for the code in this project.
SRC = ./src/main.c ./src/accent.c
#
# The build directory for the project.
BUILD_DIR = ./build
#
# The compiled executable produced by the project.
EXEC = $(BUILD_DIR)/accent.elf
#
# Various error related flags.
ERR_FLAGS = -Wall -pedantic

################################### SPECIAL ####################################

.PHONY: clean

#################################### RULES #####################################

all: $(EXEC)

# We compile with clang.
$(EXEC): $(BUILD_DIR) $(SRC) $(HEAD)
	clang $(INC_FLAG) $(ERR_FLAG) $(SRC) -o $(EXEC)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm $(EXEC)

##################################### EOF ######################################
