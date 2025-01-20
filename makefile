#The target library
LIBRARY = cutils

# The directories containing source files
SRC_DIR = src

# The directory for object files
OBJ_DIR = obj

# The directory for the built binary
BIN_DIR = bin

# The C compiler to use
CC = gcc

# The C flags to use
CFLAGS = -Iinclude -fPIC -g 

# The source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# The object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# memory checking
MEMCHECK = 0

# The default target
all: $(LIBRARY)

# Build the library
$(LIBRARY): $(OBJECTS)
	ar rcs $(LIBRARY).a $(OBJECTS)

# Build the object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -D MEMCHECK=$(MEMCHECK)

bundle:
	cat $(SOURCES) > cutils.c

test:
	$(CC) -DMEMCHECK=1 $(CFLAGS) -o $(BIN_DIR)/test test.c $(LIBRARY).a
	bin/test

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(LIBRARY).a
