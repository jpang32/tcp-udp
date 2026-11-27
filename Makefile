CC     ?= cc
CFLAGS ?= -Wall -Wextra -g

# Debug build: no optimization so stepping through code matches the source,
# full debug info, and DEBUG defined for any #ifdef DEBUG blocks.
DEBUG_CFLAGS ?= -Wall -Wextra -g3 -O0 -fno-omit-frame-pointer -DDEBUG

SERVER_TARGET = server
SERVER_SRCS   = server.c

STRUCT_TARGET = struct_practice
STRUCT_SRCS = struct_practice.c

SERVER_DEBUG_TARGET = server_debug
STRUCT_DEBUG_TARGET = struct_practice_debug

.PHONY: all run clean debug

# Default goal: build everything with the normal flags.
all: $(SERVER_TARGET) $(STRUCT_TARGET)

$(SERVER_TARGET): $(SERVER_SRCS)
	$(CC) $(CFLAGS) -o $@ $^

$(STRUCT_TARGET): $(STRUCT_SRCS)
	$(CC) $(CFLAGS) -o $@ $^

server_run: $(SERVER_TARGET)
	./$(SERVER_TARGET)

struct_run: $(STRUCT_TARGET)
	./$(STRUCT_TARGET)

# Build every target with debug flags (kept separate from the normal build).
debug: $(SERVER_DEBUG_TARGET) $(STRUCT_DEBUG_TARGET)

$(SERVER_DEBUG_TARGET): $(SERVER_SRCS)
	$(CC) $(DEBUG_CFLAGS) -o $@ $^

$(STRUCT_DEBUG_TARGET): $(STRUCT_SRCS)
	$(CC) $(DEBUG_CFLAGS) -o $@ $^

clean:
	rm -f $(SERVER_TARGET) $(STRUCT_TARGET) $(SERVER_DEBUG_TARGET) $(STRUCT_DEBUG_TARGET)
