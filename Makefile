CC = g++

MBL  = ./src/*
GCA  = ./lib/gca-plus/*

MBL_LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
GCA_LINKER_FLAGS = -lusb-1.0

# * you may have to replace ```-IC:\msys64\mingw32\include\SDL2``` and ```-LC:\msys64\mingw32\lib``` 
# with your own install directories if you chose something other than the default install locations
INCLUDE_PATHS = -IC:\msys64\mingw32\include\SDL2 
LIBRARY_PATHS = -LC:\msys64\mingw32\lib


DEBUG = -g

#todo: fix code so we ccan remove -w (supresses all warnings, project does not currently compile without it)
DEV_FLAGS = -w $(DEBUG)
RELEASE_FLAGS = -w -Wl,-subsystem,windows
 
STD = -std=c++17 

OUT = ./bin/game.exe

all : 
	$(CC) $(DEV_FLAGS) $(GCA) $(GCA_LINKER_FLAGS) $(MBL)  \
	$(INCLUDE_PATHS) $(LIBRARY_PATHS) $(MBL_LINKER_FLAGS) \
	$(STD) -o $(OUT)