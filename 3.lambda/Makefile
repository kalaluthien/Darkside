
TARGET := test3.out

# compiler settings
CC := gcc
CFLAGS := -g -O3 -std=c99

# dir settings
ROOT_DIR := .
INC_PATH := $(ROOT_DIR)/include
SRC_PATH := $(ROOT_DIR)/src
OBJ_PATH := $(ROOT_DIR)/obj
BIN_PATH := $(ROOT_DIR)/bin

# deps settings
INCS := -I$(INC_PATH)
SRCS := $(wildcard $(SRC_PATH)/*.c)
OBJS := $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRCS))

LIBS := -ldl
DEFS :=

.PHONY: all clean

all: $(TARGET)

# link
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_PATH)
	$(CC) -o $(BIN_PATH)/$@ $^ $(INCS) $(LIBS) $(CFLAGS)

# compile
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) -c -o $@ $^ $(INCS) $(DEFS) $(CFLAGS)

clean:
	rm -f ./.func_*.so | true
	rm -f $(OBJ_PATH)/*.o | true
	rm -f $(BIN_PATH)/$(TARGET) | true
