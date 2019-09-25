CXX=g++
CXX_FLAGS=-I. -Wall -Werror -g -ggdb

# https://stackoverflow.com/questions/714100/os-detecting-makefile
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	CXXFLAGS += -no-pie
endif
ifeq ($(UNAME), Darwin)
	CXXFLAGS += -std=c++11
endif

# https://stackoverflow.com/questions/2394609/makefile-header-dependencies

BUILD_DIR = ./build
CPP = $(wildcard canvas/*.cpp) \
	$(wildcard geometry/*.cpp) \
	$(wildcard lighting/*.cpp) \
	$(wildcard math/*.cpp)

OBJ = $(CPP:%.cpp=$(BUILD_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

test : $(BUILD_DIR)/bin/test
first-image: $(BUILD_DIR)/bin/first-image

# Actual target of the binary - depends on all .o files.
$(BUILD_DIR)/bin/test : tests/tests.o $(OBJ)
    # Create build directories - same structure as sources.
	mkdir -p $(@D)
    # Just link all the object files.
	$(CXX) $(CXX_FLAGS) $^ -o $@

# Actual target of the binary - depends on all .o files.
$(BUILD_DIR)/bin/first-image : tests/first-image.cpp $(OBJ)
    # Create build directories - same structure as sources.
	mkdir -p $(@D)
    # Just link all the object files.
	$(CXX) $(CXX_FLAGS) $^ -o $@

# Build target for every single object file.
# The potential dependency on header files is covered
# by calling `-include $(DEP)`.
$(BUILD_DIR)/%.o : %.cpp
	mkdir -p $(@D)
    # The -MMD flags additionaly creates a .d file with
    # the same name as the .o file.
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@

# Include all .d files
-include $(DEP)

.PHONY : clean
clean :
    # This should remove all generated files.
	-rm -rf $(BUILD_DIR)/ $(OBJ) $(DEP)
	-rm -rf $(BUILD_DIR)/bin
