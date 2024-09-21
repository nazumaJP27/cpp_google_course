# Makefile for the test exe

# Compiler
CXX = g++
CXXFLAGS = -Wall

# Directories
SRC_DIR = src
OBJ_DIR = obj
H_DIR = include
BIN_DIR = bin

# Target exe
TARGET = $(BIN_DIR)/test-atm.exe

# Source files
SRCS = $(SRC_DIR)/ATM.cpp $(SRC_DIR)/CardReader.cpp $(SRC_DIR)/CashDispenser.cpp $(SRC_DIR)/Money.cpp \
       $(SRC_DIR)/OperatorPanel.cpp $(SRC_DIR)/Account.cpp $(SRC_DIR)/test-ATM.cpp

# Object files
OBJS = $(OBJ_DIR)/ATM.o $(OBJ_DIR)/CardReader.o $(OBJ_DIR)/CashDispenser.o $(OBJ_DIR)/Money.o \
       $(OBJ_DIR)/OperatorPanel.o $(OBJ_DIR)/Account.o $(OBJ_DIR)/test-ATM.o

# Linking
$(TARGET) : $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile source files
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

# Create obj/ and bin/ directory if they don't exist
$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(BIN_DIR) :
	mkdir $(BIN_DIR)

clean :
	rm -f $(OBJ_DIR)/*.o $(TARGET)
# for windows
clean_win :
	rmdir /Q /S $(OBJ_DIR) | rmdir /Q /S $(BIN_DIR)
