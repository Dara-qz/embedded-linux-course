CC = arm-linux-gnueabihf-gcc
CFLAGS = -O2 -Wall -Wextra

TARGET = build/hello
SRCS = src/hello.c

.PHONY: all clean

all:
	mkdir -p build
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -rf build
