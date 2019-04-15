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
       Level.o \
       Viewport.o \
       win_main_menu.o \
       win_game.o \
       Timer.o \
       utils.o \
       Font_atlas.o \
       Asset_container.o \
       Tile.o \
       Tilemap.o \
       Button.o \
       version.o \
       dbg.o
OBJ = $(patsubst %, $(OBJ_DIR)/%, $(_OBJ))
NAME = crucible

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@echo "LL $@"
	@$(LL) -o $@ $(OBJ) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "CXX $@"
	@$(CXX) $(INCLUDE) $(CXX_FLAGS) $(DBG_FLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "CC $@"
	@$(CC) $(INCLUDE) $(CC_FLAGS) $(DBG_FLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $@

#release -----------------------------------------------------------------------
#  nothing here yet

#docs --------------------------------------------------------------------------
DOC_DIR = devdoc
DOC_SRC_LATEX_DIR = devdoc/latex
BUILD_TOOLS_DIR = buildtools
LATEX_COMP = $(BUILD_TOOLS_DIR)/latex_gen.sh
DOCS = $(DOC_DIR)/design_doc.pdf

docs: $(DOCS)	

$(DOC_DIR)/design_doc.pdf: $(DOC_SRC_LATEX_DIR)/design_doc.tex
	@echo "LaTeX: $@"
	$(LATEX_COMP) $<
	mv $(patsubst %.tex, %.pdf, $<) $@

.PHONY: clean_docs
clean_docs:
	rm -fv $(DOCS)

#other -------------------------------------------------------------------------
.PHONY: todo
todo:
	bash -c "grep "TODO" -n -A2 {inc,src}/* > todo.txt"

.PHONY: ctags
ctags:
	bash -c "ctags -R {src,inc}"

.PHONY: clean
clean:
	echo RM $(OBJ)
	rm -vf $(OBJ)
	echo RM $(NAME)
	rm -vf $(NAME)

