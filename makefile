INCLUDE := -Iinclude -Iplatform -Iutil
OUT_PATH := bin

CC := gcc
CFLAGS := -Wall $(INCLUDE)

WINDOWS := platform/wsh_windows.c
POSIX := platform/wsh_posix.c
SRC := $(wildcard core/*.c) $(wildcard util/*.c)

RM := 
EXE := 
ifeq ($(OS),Windows_NT)
	RM := del
	SRC += $(WINDOWS)
    EXE = $(OUT_PATH)/wsh.exe
else
	RM := rm -f
	SRC += $(POSIX)
    EXE = $(OUT_PATH)/wsh
endif

OBJ = ${SRC:%.c=%.o}

%.o: %.c
	@echo Compiling $@
	@$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: all
all: $(EXE)

$(EXE): $(OBJ)
	@echo Creating binary $@
	@$(CC) $(INCLUDE) $(OBJ) -o $@

.PHONY: clean
clean:
	@echo Cleaning all objects
	@$(RM) platform/*.o
	@$(RM) core/*.o
	@$(RM) $(EXE_PATH)
