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
CFLAGS = -Iinclude -fPIC

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

test:
	$(CC) $(CFLAGS) -o $(BIN_DIR)/test test.c $(LIBRARY).a

test_all:
	$(CC) $(CFLAGS) -o $(BIN_DIR)/test_all test.c $(LIBRARY).a
	./$(BIN_DIR)/test_all
	if [ $$? -eq 0 ]; then \
		echo "All tests passed successfully!"; \
	else \
		echo "Some tests failed."; \
		exit 1; \
	fi

benchmark:
	$(CC) $(CFLAGS) -o $(BIN_DIR)/benchmark benchmark.c $(LIBRARY).a
	./$(BIN_DIR)/benchmark

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(LIBRARY).a
