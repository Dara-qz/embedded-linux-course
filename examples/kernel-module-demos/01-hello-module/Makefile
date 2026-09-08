ifneq ($(KERNELRELEASE),)
obj-m += hello.o
hello-objs := src/hello.o
else
.PHONY: all check deploy load unload test clean

KDIR ?= $(HOME)/bbb-workspace/kernel/bb-kernel/KERNEL
ARCH ?= arm
BB_GCC := $(firstword $(wildcard $(HOME)/bbb-workspace/kernel/bb-kernel/dl/gcc-*-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc))
CROSS_COMPILE ?= $(if $(BB_GCC),$(patsubst %gcc,%,$(BB_GCC)),arm-linux-gnueabi-)

BBB_HOST ?= 192.168.7.2
BBB_USER ?= debian
BBB_DIR ?= /home/$(BBB_USER)/embedded-linux

all:
	@test -f "$(KDIR)/Makefile" || { \
	  printf '%s\n' 'Kernel tree missing. Complete Lab 01 in ~/bbb-workspace/kernel first.'; \
	  exit 1; \
	}
	$(MAKE) -C "$(KDIR)" M="$(CURDIR)" ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

check: all
	file hello.ko
	modinfo hello.ko | grep vermagic

deploy: check
	ssh $(BBB_USER)@$(BBB_HOST) 'mkdir -p $(BBB_DIR)'
	scp hello.ko $(BBB_USER)@$(BBB_HOST):$(BBB_DIR)/hello.ko

load: deploy
	ssh -t $(BBB_USER)@$(BBB_HOST) 'sudo insmod $(BBB_DIR)/hello.ko && sudo dmesg | tail -20'

unload:
	ssh -t $(BBB_USER)@$(BBB_HOST) 'sudo rmmod hello && sudo dmesg | tail -20'

test: load
	ssh -t $(BBB_USER)@$(BBB_HOST) 'lsmod | grep hello; sudo rmmod hello; sudo dmesg | tail -20'

clean:
	@test ! -f "$(KDIR)/Makefile" || $(MAKE) -C "$(KDIR)" M="$(CURDIR)" clean
	$(RM) -r .tmp_versions
	$(RM) *.o *.ko *.mod *.mod.c *.cmd .*.cmd src/*.o src/*.cmd src/.*.cmd Module.symvers modules.order
endif
