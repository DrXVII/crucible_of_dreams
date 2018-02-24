SRC = src/*.cpp
INCLUDE = -I inc

CXX = g++

#COMPILER_FLAGS specifies the additional compilation options we are using
# -w suppress all warnings
COMPILER_FLAGS = -std=c++14

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = crucible

#This is the target that compiles our executable
all : $(SRC)
	$(CXX) $(SRC) $(INCLUDE) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

debug : $(OBJS)
	$(CXX) -ggdb $(SRC) $(INCLUDE) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
