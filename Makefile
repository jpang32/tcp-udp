CC     ?= cc
CFLAGS ?= -Wall -Wextra -g

TARGET = server
SRCS   = server.c

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
