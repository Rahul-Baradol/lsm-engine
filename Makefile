# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Source directories
SRCDIR = src
BUILDDIR = build

# Find all .cc files in src/ and its subdirectories
SRC = $(shell find $(SRCDIR) -name '*.cc')

# Object files
OBJ = $(SRC:$(SRCDIR)/%.cc=$(BUILDDIR)/%.o)

# Executable
EXEC = out/app.out

# Default target
all: $(EXEC)

# Rule to link object files to create the executable
$(EXEC): $(OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJ) -o $@

# Rule to compile source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(EXEC)

# Phony targets
.PHONY: all clean
