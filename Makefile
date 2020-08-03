
################################################################################
# Makefile                                                                     #
################################################################################

# Executable Names
C_PAR_EXE   := gauss
C_SER_EXE   := gaussS

# Source and Object Directories
C_SRC_DIR   := src/c
C_OBJ_DIR   := obj/c
CPP_SRC_DIR := src/c++
CPP_OBJ_DIR := obj/c++

# Files for Serial and Parallel Executables
C_COM_NAMES := gauss.c pgmTools.c
C_SER_NAMES := mainSerial.c $(C_COM_NAMES)
C_PAR_NAMES := mainOMP.c $(C_COM_NAMES)

# Flags and Libraries
CFLAGS      := -std=c99 -Wall -Wextra -fopenmp -O3
CPPFLAGS    := -I.
LDFLAGS     := -fopenmp
LDLIBS      := -lm

# Translation to Directory Paths - DON'T TOUCH!
C_SER_SRC   := $(patsubst %.c,$(C_SRC_DIR)/%.c,$(C_SER_NAMES))
C_SER_OBJ   := $(patsubst %.c,$(C_OBJ_DIR)/%.o,$(C_SER_NAMES))
C_PAR_SRC   := $(patsubst %.c,$(C_SRC_DIR)/%.c,$(C_PAR_NAMES))
C_PAR_OBJ   := $(patsubst %.c,$(C_OBJ_DIR)/%.o,$(C_PAR_NAMES))

################################################################################
# Make All

all: $(C_PAR_EXE) $(C_SER_EXE)

################################################################################
# Make C Parallel Executable

$(C_PAR_EXE): $(C_PAR_OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

################################################################################
# Make C Serial Baseline Executable

$(C_SER_EXE): $(C_SER_OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

################################################################################
# Make Objects

$(C_OBJ_DIR)/%.o: $(C_SRC_DIR)/%.c | $(C_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(C_OBJ_DIR):
	mkdir -p $@

################################################################################
#  Clean

clean:
	$(RM) -r $(C_OBJ_DIR)
	$(RM) -r $(CPP_OBJ_DIR)
	$(RM) $(C_PAR_EXE)
	$(RM) $(C_SER_EXE)

.PHONY: all clean

#########################################################



# END Makefile  - EWG SDG
