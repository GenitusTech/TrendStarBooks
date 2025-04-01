CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c11
INCLUDES = -I./src
LIBS = -lcurl -lcjson -lwebsockets -lmariadb

# Enable all warnings + treat them as errors
STRICT_CFLAGS = $(CFLAGS) -Wconversion -Wshadow -Wstrict-prototypes -Wmissing-prototypes

# Source files
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)
EXEC = trendstarbooks_service_api

# Static analyzers
ANALYZE = splint cppcheck clang

.PHONY: all build analyze clean

all: clean build analyze

build: $(OBJ)
	$(CC) $(STRICT_CFLAGS) $(INCLUDES) -o $(EXEC) $(OBJ) $(LIBS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(STRICT_CFLAGS) $(INCLUDES) -c $< -o $@

analyze:
	@echo "=== Running Splint ==="
	splint $(INCLUDES) $(SRC)
	@echo "=== Running Cppcheck ==="
	cppcheck --enable=all --suppress=missingIncludeSystem $(INCLUDES) $(SRC_DIR)
	@echo "=== Running Clang Analyzer ==="
	clang --analyze $(INCLUDES) $(SRC)

clean:
	clear
	rm -f $(OBJ) $(EXEC)
