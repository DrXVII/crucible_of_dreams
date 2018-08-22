CXX = g++
LL = g++
CC = gcc
CXX_FLAGS = -std=c++17 -Wall -Wextra
CC_FLAGS = -Wall -Wextra
LD_FLAGS =
DBG_FLAGS = -ggdb -DDEBUG=9
INCLUDE = -I inc
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf
SRC_DIR = src
OBJ_DIR = obj

_OBJ = main.o \
       win_main_menu.o \
       win_game.o \
       Timer.o \
       utils.o \
       Font_atlas.o \
       Asset_container.o \
       Tile.o \
       Button.o \
       dbg.o
OBJ = $(patsubst %, $(OBJ_DIR)/%, $(_OBJ))
NAME = crucible

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@echo "LL $@        ($^)"
	@$(LL) -o $@ $(OBJ) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "CXX $@        ($<)"
	@$(CXX) $(INCLUDE) $(CXX_FLAGS) $(DBG_FLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "CC $@        ($<)"
	@$(CC) $(INCLUDE) $(CC_FLAGS) $(DBG_FLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $@

#release -----------------------------------------------------------------------
#  nothing here yet

#other -------------------------------------------------------------------------
.PHONY: todo
todo:
	bash -c "grep "TODO" -n -A2 {inc,src}/* > todo.txt"

.PHONY: ctags
ctags:
	bash -c "ctags {src,inc}/*"

.PHONY: clean
clean:
	echo RM $(OBJ)
	rm -vf $(OBJ)
	echo RM $(NAME)
	rm -vf $(NAME)

