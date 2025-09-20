# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Output program name
TARGET = excel

# Source files
SRCS = main.cpp excel.cpp
OBJS = $(SRCS:.cpp=.o)

# Build rule
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile each .cpp into .o
%.o: %.cpp excel.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
