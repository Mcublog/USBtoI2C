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

LOG_INC := $(DEBUG_INC)/log_libs.h
LOG_SRC := $(DEBUG_SRC)/log_libs.c

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp $(RING_SRC)/*.c
	$(CXX) $(CXX_FLAGS) $(LOG_SRC) -I$(INCLUDE) -I$(DEBUG_INC) -I$(RING_INC) $(LOG_INC) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
