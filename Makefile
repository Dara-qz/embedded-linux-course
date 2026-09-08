.PHONY: help user user-deploy module module-deploy clean

BBB_HOST ?= 192.168.7.2
BBB_USER ?= debian
BBB_DIR ?= /home/$(BBB_USER)/embedded-linux

help:
	@printf '%s\n' \
	  'make user          Cross-compile the hello user program' \
	  'make user-deploy   Copy and run it on the BBB' \
	  'make module        Build the hello external kernel module' \
	  'make module-deploy Copy the module to the BBB' \
	  'make clean         Remove example build output'

user:
	$(MAKE) -C examples/userspace-programs/01-hello-user

user-deploy:
	$(MAKE) -C examples/userspace-programs/01-hello-user deploy BBB_HOST=$(BBB_HOST) BBB_USER=$(BBB_USER) BBB_DIR=$(BBB_DIR)

module:
	$(MAKE) -C examples/kernel-module-demos/01-hello-module

module-deploy:
	$(MAKE) -C examples/kernel-module-demos/01-hello-module deploy BBB_HOST=$(BBB_HOST) BBB_USER=$(BBB_USER) BBB_DIR=$(BBB_DIR)

clean:
	$(MAKE) -C examples/userspace-programs/01-hello-user clean
	$(MAKE) -C examples/kernel-module-demos/01-hello-module clean
