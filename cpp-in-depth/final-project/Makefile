# Compiler
CXX = g++
CXXFLAGS = -g -Wall

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
H_DIR = include

# Target executable
TARGET = ${BIN_DIR}/test-project.exe

# Source files
SRCS = ${SRC_DIR}/Document.cpp ${SRC_DIR}/utils.cpp ${SRC_DIR}/test-project.cpp

# Object files
OBJS = ${SRCS:${SRC_DIR}/%.cpp=${OBJ_DIR}/%.o}

# Linking
${TARGET}: ${OBJS} | ${BIN_DIR}
	${CXX} ${CXXFLAGS} $^ -o $@

# Compile source files to object files
${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp | ${OBJ_DIR}
	${CXX} ${CXXFLAGS} -c $^ -o $@

# Create OBJ_DIR and BIN_DIR
${OBJ_DIR}:
	mkdir $@
${BIN_DIR}:
	mkdir $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
clean_win:
	rmdir /S /Q ${OBJ_DIR} | rmdir /S /Q ${BIN_DIR}