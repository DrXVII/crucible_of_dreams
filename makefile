CXX = g++
LL = g++
CC = gcc
CXX_FLAGS = -std=c++17 #-Wall
CC_FLAGS = -Wall
DBG_FLAGS = -ggdb
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf
SRC_DIR = src
INCLUDE = -I inc
OBJ_DIR = obj
OBJ = $(OBJ_DIR)/main.o\
      $(OBJ_DIR)/Timer.o
NAME = crucible

all: $(NAME)

$(NAME): $(OBJ)
	echo "LL $@ ($^)"
	$(LL) $(INCLUDE) $(CXX_FLAGS) -o $@ $(OBJ) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(OBJ_DIR)
	echo "CXX $@ ($<)"
	$(CXX) $(INCLUDE) $(CXX_FLAGS) $(DBG_FLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	echo "CC $@ ($<)"
	$(CC) $(INCLUDE) $(CC_FLAGS) $(DBG_FLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $@

#release -----------------------------------------------------------------------
#  nothing here yet

#other -------------------------------------------------------------------------
clean:
	echo RM $(OBJ)
	rm -vf $(OBJ)
	echo RM $(NAME)
	rm -vf $(NAME)

.PHONY: all clean
