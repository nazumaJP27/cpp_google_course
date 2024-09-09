# Compiler
CXX = g++
CXXFLAGS = -Wall

# Directories
SRC_DIR = src
OBJ_DIR = obj
H_DIR = include
BIN_DIR = bin

# Target executable
TARGET = $(BIN_DIR)/composer-DB.exe

# Source files
SRCS = $(SRC_DIR)/Composer.cpp $(SRC_DIR)/Database.cpp $(SRC_DIR)/composer-DB.cpp

# Object files
OBJS = $(OBJ_DIR)/Composer.o $(OBJ_DIR)/Database.o $(OBJ_DIR)/composer-DB.o

# Linking 
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

# Create obj/ and bin/ directory if they don't exist
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(BIN_DIR):
	mkdir $(BIN_DIR)

# Clean
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
# for Windows
clean_win: 
	rmdir /Q /S $(OBJ_DIR) 
	rmdir /Q /S $(BIN_DIR)
