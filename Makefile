CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++2a -ggdb -Wformat=0

BIN		:= bin
SRC		:= App
DESKTOP_SRC	:= targets/desktop
INCLUDE	:= App

LIBRARIES	:=
EXECUTABLE	:= pc_core_app

DEBUG_INC := $(SRC)/debug
DEBUG_SRC := $(SRC)/debug

RING_INC := Ring-Buffer
RING_SRC := Ring-Buffer

COBS_INC := cobs-c
COBS_SRC := cobs-c/cobsr.c

all:
	make cobs
	make $(BIN)/$(EXECUTABLE)

cobs: $(COBS_SRC)
	gcc -c -I$(COBS_INC) $^ -o $(BIN)/$@.a

$(BIN)/$(EXECUTABLE): $(DESKTOP_SRC)/*.cpp $(SRC)/*.cpp $(RING_SRC)/*.c $(DEBUG_SRC)/*.c $(BIN)/*.a
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -I$(DEBUG_INC) -I$(RING_INC) -I$(COBS_INC) $^ -o $@ $(LIBRARIES)

clean:
	-rm *.out
	-rm $(BIN)/*

rebuild: clean
	clear
	make cobs
	make $(BIN)/$(EXECUTABLE)

run: rebuild
	$(BIN)/$(EXECUTABLE)

run_tty: rebuild
	$(BIN)/$(EXECUTABLE) /dev/ttyS10

nullmodem:
	-socat PTY,link=/dev/ttyS10,raw,echo=0 PTY,link=/dev/ttyS11,raw,echo=0 &
	-sleep 0.1
	-chmod 777 /dev/ttyS11 /dev/ttyS10
