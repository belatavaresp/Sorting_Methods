# CC and flags
CC = g++
CXXFLAGS = -std=c++11 -g -Wall

# folders
INCLUDE_FOLDER = ./headers/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./

# all sources, objs, and header files
MAIN = main
TARGET = run
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))

# compile
$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

all: $(OBJ)
	$(CC) $(CXXFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ) 

clean:
	@rm -rf $(OBJ_FOLDER)* $(BIN_FOLDER)*

run:
	@$(BIN_FOLDER)$(TARGET)