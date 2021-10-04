INC_DIR = ./inc
UTIL_DIR = ./util
SRC_DIR = ./src
BIN_DIR = ./bin
OBJ_DIR = $(BIN_DIR)/obj

OUT_FILE = $(BIN_DIR)/out.exe

# include the description for each module
include $(patsubst %, %/module.mk,$(SRC_DIR))

_OBJ = $(patsubst %.cpp,%.o, $(filter %.cpp, $(SRC)))
OBJ = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(_OBJ))

CXX = g++.exe

CFLAGS = -g -std=c++17 -Wall
IDFLAGS = -I. -I$(INC_DIR) -I$(UTIL_DIR)
LFLAGS = -static -static-libgcc -static-libstdc++ -lgdi32

all: $(OUT_FILE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo compiling $< to $@
	$(CXX) $(CFLAGS) $(IDFLAGS) -c $< -o $@

$(OUT_FILE): $(OBJ)
	@echo linking...
	$(CXX) $(LFLAGS) -o $(OUT_FILE) $^

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/*.exe

.PHONY: all clean
