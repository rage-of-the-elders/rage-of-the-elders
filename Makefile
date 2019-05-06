######################## MY MAKEFILE ########################

# COMPILER= g++
# RMDIR = rm -rdf
# RM = rm -f

# RUN = ./

# DEP_FLAGS = -M -MT $@ -MT $(BIN_PATH)/$(*F).o -MP -MF $@
# LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
# INC_PATHS = -I $(INC_PATH) $(addprefix -I,$(SDL_INC_PATH))
# FLAGS = -std=c++11 -Wall -pedantic -Wextra -Wno-unused-parameter -Werror=init-self
# DFLAGS = -ggdb -O0 -DDEBUG
# RFLAGS = -O3 -mtune=native

# INC_PATH = include
# SRC_PATH = src
# BIN_PATH = bin
# DEP_PATH = dep
# ASSETS_PATH = assets
# # SDL_PATHS =

# CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
# INC_FILES = $(wildcard $(SRC_PATH)/*.h)
# FILE_NAMES = $(sort $(notdir $(CPP_FILES:.cpp=)) $(notdir $(INC_FILES:.h=)))
# DEP_FILES = $(addprefix $(DEP_PATH)/, $(addsuffix .d,$(FILE_NAMES)))
# OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))

# EXEC = GAME

# ifeq ($(OS), Windows_NT)

# RUN =

# RMDIR = rd /s /q

# RM = del /q

# SDL_PATHS = C:/Sdl/x86_64-w64-mingw32 C:/Tools/msys64/mingw64

# SDL_INC_PATH += $(addsuffix /include, $(SDL_PATHS))
# LINK_PATH = $(addprefix -L,$(addsuffix /lib,$(SDL_PATHS)))
# FLAGS += -mwindows
# DFLAGS += -mconsole
# LIBS := -lmingw32 - lSDL2main $(LIBS)

# EXEC := $(EXEC).exe

# else

# UNAME_S := $(shell uname -s)

# ifeq ($(UNAME_S), Darwin)

# LIBS = -lm -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf

# endif
# endif

# all: $(EXEC)

# $(EXEC): $(OBJ_FILES)
# 	$(COMPILER) -o $@ $^ $(LINK_PATH) $(LIBS) $(FLAGS)

# $(BIN_PATH)/%.o: $(DEP_PATH)/%.d | folders
# 	$(COMPILER) $(INC_PATHS) $(addprefix $(SRC_PATH)/,$(notdir $(<:.d=.cpp))) -c $(FLAGS) -o $@

# $(DEP_PATH)/%.d: $(SRC_PATH)/%.cpp | folders
# 	$(COMPILER) $(INC_PATHS) $< $(DEP_FLAGS) $(FLAGS)

# .SECONDEXPANSION:
# -include $$(DEP_FILES)

# clean:
# 	-$(RMDIR) $(DEP_PATH)
# 	-$(RMDIR) $(BIN_PATH)
# 	-$(RM) $(EXEC)

# run:
# 	$(RUN)$(EXEC)

# release: FLAGS += $(RFLAGS)
# release: $(EXEC)

# debug: FLAGS += $(DFLAGS)
# debug: $(EXEC)

# folders:
# ifeq ($(OS), Windows_NT)
# 	@if NOT exist $(DEP_PATH) ( mkdir $(DEP_PATH) )
# 	@if NOT exist $(BIN_PATH) ( mkdir $(BIN_PATH) )
# 	@if NOT exist $(INC_PATH) ( mkdir $(INC_PATH) )
# 	@if NOT exist $(SRC_PATH) ( mkdir $(SRC_PATH) )
# else
# 	@mkdir -p $(DEP_PATH) $(BIN_PATH) $(INC_PATH) $(SRC_PATH)
# endif

# print-% : ; @echo $* = $($*)

# help:
# ifeq ($(OS), Windows_NT)
# 	@echo.
# endif
# 	@echo Available targets:
# 	@echo - release:	Builds the release version
# 	@echo - debug:		Builds the debug version
# 	@echo - clean:		Cleans generated files
# 	@echo - folders:	Generates project directories
# 	@echo - help:		Shows this help
# ifeq ($(OS), Windows_NT)
# 	@echo.
# endif

# .PRECIOUS: $(DEP_FILES)
# .PHONY: release debug clean folders help



######################## MAKEFILE MONITOR ########################

CC = g++
RMDIR = rm -rf
RM = rm -f

RUN = ./

DEP_FLAGS = -MT $@ -MMD -MP -MF $(DEP_PATH)/$*.d

DIRECTIVES = -std=c++11 -Wall -Wextra -c -I $(HEADER_PATH)

LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

HEADER_PATH = include
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep

CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))
DEP_FILES = $(wildcard $(DEP_PATH)/*.d)

EXEC = GAME

ifeq ($(OS),Windows_NT)

RMDIR = rd /s /q
RM = del

RUN =

SDL_PATH = C:\SDL2\SDL2-2.0.5\x86_64-w64-mingw32

DIRECTIVES += -I $(SDL_PATH)\include\SDL2

LIBS = -L $(SDL_PATH)\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

EXEC := $(EXEC).exe

else
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
LIBS = -lm -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf
endif
endif

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LIBS)

$(BIN_PATH)/%.o: $(SRC_PATH)/%.cpp

ifeq ($(OS), Windows_NT)
	@if not exist $(DEP_PATH) @mkdir $(DEP_PATH)
	@if not exist $(BIN_PATH) @mkdir $(BIN_PATH)
else
	@mkdir -p $(DEP_PATH) $(BIN_PATH)
endif

	$(CC) $(DEP_FLAGS) -c -o $@ $< $(DIRECTIVES)

print-% : ; @echo $* = $($*)

debug: DIRECTIVES += -ggdb -O0 -DDEBUG
debug: all

dev: debug run

gdb: RUN := gdb $(RUN)
gdb: dev

release: DIRECTIVES += -Ofast -mtune=native
release: all

run:
	$(RUN)$(EXEC)

go: all run

clean:
	$(RMDIR) $(BIN_PATH) $(DEP_PATH)

notes: todo

todo:
	@echo "Searching notes..."
	@grep --color --exclude='Makefile' --exclude='LICENSE' --exclude-dir='.git' --exclude-dir='assets' -rni 'TODO\|FIXME\|TO DO\|FIX ME' .
.PRECIOUS: $(DEP_PATH)/%.D

.PHONY: debug clean release

-include $(DEP_FILES)