CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Weffc++ -Wold-style-cast

TEST_TARGET := time_test
TESTDIR := tests
TOOLDIR := tool
BUILDDIR := build
SRCDIR := src
INCDIR := include
# Source files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)


# Include directories
INCLUDES := -I$(INCDIR)

TEST_SOURCES := $(wildcard $(TESTDIR)/*.cpp)
TOOL_SOURCES := $(wildcard $(TOOLDIR)/*.cpp)
TOOL_OBJECTS :=  $(patsubst $(TOOLDIR)/%.cpp,$(TOOLDIR)/%.o,$(TOOL_SOURCES))

.PHONY: print clean
print:
	@echo $(BUILDDIR)/%.o

tool: $(TOOL_OBJECTS)

$(TOOLDIR)/%.o: $(TOOLDIR)/%.cpp $(TOOLDIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $(TOOLDIR)/%.cpp

test: $(TEST_TARGET)
	
$(TEST_TARGET): $(SOURCES) $(TOOL_OBJECTS) $(TEST_SOURCES)
	$(CXX) $(CXXFLAGS)   $(SOURCES) $(TOOL_OBJECTS) $(TEST_SOURCES) -o $(TEST_TARGET)


clean:
	@rm -rf $(BUILDDIR)/*.o $(TEST_TARGET)