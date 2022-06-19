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

COBS_INC := cobs-c
COBS_SRC := cobs-c/cobsr.c

all:
	make cobs
	make $(BIN)/$(EXECUTABLE)

run:
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp $(RING_SRC)/*.c $(DEBUG_SRC)/*.c $(BIN)/*.a
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -I$(DEBUG_INC) -I$(RING_INC) -I$(COBS_INC) $^ -o $@ $(LIBRARIES)

clean:
	-rm *.out
	-rm $(BIN)/*

cobs: $(COBS_SRC)
	gcc -c -I$(COBS_INC) $^ -o $(BIN)/$@.a
