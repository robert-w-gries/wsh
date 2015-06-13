INCLUDE := -Iinclude -Iplatform -Iplatform/windows -Iplatform/posix
OUT_PATH := bin

CC := gcc
CFLAGS := -Wall $(INCLUDE)
RM := rm

WINDOWS := $(wildcard platform/windows/*.c)
POSIX := $(wildcard platform/posix/*.c)
SRC :=	$(wildcard platform/*.c) $(wildcard core/*.c) $(POSIX)
OBJ = ${SRC:%.c=%.o}
EXE := $(OUT_PATH)/wsh

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
	@$(RM) -f platform/*.o
	@$(RM) -f platform/windows/*.o
	@$(RM) -f platform/posix/*.o
	@$(RM) -f core/*.o
	@$(RM) -f $(OUT_PATH)/wsh
