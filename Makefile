########################################################################
########################### Makefile ###################################
########################################################################

# Compiler settings
CC = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lncursesw

# Project structure
APPNAME = out/menu
EXT = .cpp
SRCDIR = src
OBJDIR = obj

# Source and object files
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)

# Safe remove
RM = rm -f

########################################################################
########################## Build Rules #################################
########################################################################

# Build everything
all: $(OBJDIR) $(dir $(APPNAME)) $(APPNAME)

# Link the final binary
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile .cpp to .o
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

# Generate dependency files
%.d: $(SRCDIR)/%$(EXT)
	@$(CC) $(CXXFLAGS) -MM $< -MT $(@:%.d=$(OBJDIR)/%.o) > $@

# Include generated dependencies
-include $(DEP)

########################################################################
###################### Directory Setup #################################
########################################################################

# Ensure build dirs exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(dir $(APPNAME)):
	mkdir -p $(dir $(APPNAME))

########################################################################
######################### Clean Targets ################################
########################################################################

.PHONY: clean cleandep run

clean:
	$(RM) $(OBJ) $(DEP) $(APPNAME)

cleandep:
	$(RM) $(DEP)

run: all
	./test.sh
