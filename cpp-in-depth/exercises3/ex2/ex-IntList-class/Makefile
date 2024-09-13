# Compiler
CXX = g++
CXXFLAGS = -Wall

# Target executable
TARGET = test-class.exe

# Source files
SRCS = IntList.cpp test-class.cpp

# Linking 
$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean
clean:
	rm -f $(TARGET)
# for Windows
clean_win: 
	del $(TARGET)
