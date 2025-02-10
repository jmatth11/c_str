CC=gcc
CFLAGS=-Wall -Werror -fPIC
OBJ=obj
BIN=bin
# grab all top level c files
SOURCES=$(wildcard *.c)
# path sub to point to obj folder
OBJECTS=$(patsubst %.c, $(OBJ)/%.o, $(SOURCES))
# files to filter out for shared/archive files
FILTER_FILES=$(OBJ)/main.o
ARCHIVE_FILES=$(filter-out $(FILTER_FILES), $(OBJECTS))
ARCHIVE_DIR=lib
ARCHIVE_NAME=lib_c_str.a
SHARED_NAME=lib_c_str.so
# executable, if used for cli
TARGET=c_str

.PHONY: all
# have to path sub the dependencies. maybe a better way?
all: $(OBJECTS) $(DEPS)
	$(CC) $(patsubst %.o, $(OBJ)/%.o, $(notdir $^)) -O2 $(CFLAGS) -o $(BIN)/$(TARGET)

.PHONY: debug
debug: $(OBJECTS) $(DEPS)
	$(CC) $(patsubst %.o, $(OBJ)/%.o, $(notdir $^)) -g $(CFLAGS) -o $(BIN)/$(TARGET)

# rule for top level source files
$(OBJ)/%.o: %.c
	@mkdir -p $(OBJ)
	@mkdir -p $(BIN)
	gcc -c -o $@ $< $(PFLAGS) $(CFLAGS) $(INCLUDES)

.PHONY: archive
# rule to create shared object and archive files
archive: $(ARCHIVE_FILES)
	mkdir -p $(ARCHIVE_DIR)
	gcc -shared -fPIC -o $(ARCHIVE_DIR)/$(SHARED_NAME) $(patsubst %.o, $(OBJ)/%.o, $(notdir $^))
	ar -r $(ARCHIVE_DIR)/$(ARCHIVE_NAME) $(patsubst %.o, $(OBJ)/%.o, $(notdir $^))

.PHONY: test
test: all
	./$(BIN)/$(TARGET)

.PHONY: clean
clean:
	rm $(BIN)/$(TARGET) $(OBJ)/*.o
