.PHONY: all deploy test clean

CROSS_COMPILE ?= arm-linux-gnueabihf-
CC := $(CROSS_COMPILE)gcc
CFLAGS ?= -O2 -Wall -Wextra
TARGET := build/hello

BBB_HOST ?= 192.168.7.2
BBB_USER ?= debian
BBB_DIR ?= /home/$(BBB_USER)/embedded-linux

all: $(TARGET)

$(TARGET): src/hello.c
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@

deploy: $(TARGET)
	ssh $(BBB_USER)@$(BBB_HOST) 'mkdir -p $(BBB_DIR)'
	scp $(TARGET) $(BBB_USER)@$(BBB_HOST):$(BBB_DIR)/hello-user

test: deploy
	ssh $(BBB_USER)@$(BBB_HOST) '$(BBB_DIR)/hello-user'

clean:
	rm -f $(TARGET)
