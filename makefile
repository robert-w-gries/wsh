INCLUDE := -Iinclude -Iplatform -Iplatform/windows -Iplatform/posix
OUT_PATH := bin

CC := gcc
CFLAGS := -Wall $(INCLUDE)

WINDOWS := $(wildcard platform/windows/*.c)
POSIX := $(wildcard platform/posix/*.c)
SRC :=	$(wildcard platform/*.c) $(wildcard core/*.c)

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
	@$(RM) platform/windows/*.o
	@$(RM) platform/posix/*.o
	@$(RM) core/*.o
	@$(RM) $(EXE_PATH)
