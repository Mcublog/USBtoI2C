CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++2a -ggdb -Wformat=0

BIN		:= bin
SRC		:= App
INCLUDE	:= App

LIBRARIES	:=
EXECUTABLE	:= main

DEBUG_INC := $(SRC)/debug
DEBUG_SRC := $(SRC)/debug

RING_INC := Ring-Buffer
RING_SRC := Ring-Buffer

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp $(RING_SRC)/*.c $(DEBUG_SRC)/*.c
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -I$(DEBUG_INC) -I$(RING_INC) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
