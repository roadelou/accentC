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
ERR_FLAG = -Wall -pedantic
#
# The location where the executable will be installed.
BINDIR = $(DESTDIR)/usr/bin
#
# Adding RPM distro C flags if they are provided.
CFLAGS = $(RPM_OPT_FLAGS) $(ERR_FLAG) $(INC_FLAG)
#
# The fakeroot used to compile the debian package.
FAKEROOT_DEBIAN = ./accent_1.0-1

################################### SPECIAL ####################################

.PHONY: clean install uninstall

#################################### RULES #####################################

all: $(EXEC)

# Using order-only dependancy for BUILDDIR.
$(EXEC): $(SRC) $(HEAD) | $(BUILDDIR)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Using order-only dependancy for BINDIR.
install: $(EXEC) | $(BINDIR)
	install -m 755 $(EXEC) $(BINDIR)/accent

debian: 
	# We start by creating the fakeroot to build the debian package.
	mkdir -p $(FAKEROOT_DEBIAN)
	# We compile the source code.
	make -j4
	# We install the code in the fakeroot.
	DESTDIR=$(FAKEROOT_DEBIAN) make install
	# We copy the package metadata inside the fakeroot.
	mkdir -p $(FAKEROOT_DEBIAN)/DEBIAN
	install -m 664 DEBIAN.control $(FAKEROOT_DEBIAN)/DEBIAN/control
	# Finally, we build the debian package itself.
	dpkg-deb --build $(FAKEROOT_DEBIAN)

uninstall:
	rm -f $(BINDIR)/accent

clean:
	rm -f $(EXEC)
	rm -rf $(FAKEROOT_DEBIAN)
	rm -f *.deb

##################################### EOF ######################################
