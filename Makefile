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
BUILDDIR = ./build
#
# The compiled executable produced by the project.
EXEC = $(BUILDDIR)/accent.elf
#
# Various error related flags.
ERR_FLAGS = -Wall -pedantic
#
# The location where the executable will be installed.
BINDIR = $(DESTDIR)/usr/bin

################################### SPECIAL ####################################

.PHONY: clean install uninstall

#################################### RULES #####################################

all: $(EXEC)

# We compile with clang.
$(EXEC): $(BUILDDIR) $(SRC) $(HEAD)
	clang $(INC_FLAG) $(ERR_FLAG) $(SRC) -o $(EXEC)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

install: $(EXEC) $(BINDIR)
	install -m 755 $(EXEC) $(BINDIR)/accent

uninstall:
	rm -f $(BINDIR)/accent

clean:
	rm $(EXEC)

##################################### EOF ######################################
