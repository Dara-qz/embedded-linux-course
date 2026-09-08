# Lab 02 — First External Linux Kernel Module

Complete Lab 01 first. This guide assumes working SSH and a kernel tree whose
full release matches the kernel running on the BeagleBone Black.

Work in `classroom-templates/lab02-first-kernel-module/` on branch `lab02`
in your personal course fork. Before starting, follow the
[student workflow](../../docs/student-workflow.md) to set up instructor review.

## Command labels

- **[HOST]** — your Linux PC.
- **[BBB]** — the BeagleBone Black.
- Use `hostname` and `uname -m` whenever you are unsure which shell you are in.

## 1. Goals

You will learn to:

- explain the difference between a user program and a kernel module;
- write module initialization and cleanup functions;
- build a `.ko` using the kernel build system;
- inspect its architecture and `vermagic`;
- copy, load, inspect, and unload it on the BBB;
- read module messages from the kernel log.

## 2. Mandatory prerequisite check

On **[BBB]**:

```bash
uname -r
uname -m
ip addr show usb0
```

Write down the complete `uname -r`, then return to **[HOST]** with `exit`.
On HOST, check the shared workspace created in Lab 01:

```bash
test -f ~/bbb-workspace/kernel/bb-kernel/KERNEL/Makefile && echo 'Kernel tree exists'
cat ~/bbb-workspace/kernel/bb-kernel/KERNEL/include/config/kernel.release
ls -lh ~/bbb-workspace/kernel/bb-kernel/deploy
```

The two full release strings must be identical. A shared `6.12` prefix is not
enough: for example, `6.12.93-bone63` and `6.12.95-bone64` do not match.

> Stop if they differ. Ask the instructor for the course-pinned `bb-kernel`
> commit matching the assigned image. Never force-load a mismatched module.

## 3. User program versus kernel module

A normal program can be built directly:

```bash
# From your Lab 01 repository, using its user-space source:
mkdir -p build
arm-linux-gnueabihf-gcc src/hello.c -o build/hello
```

A kernel module runs inside the kernel. It does not use the normal C library and
must be built by the matching configured kernel build system:

```text
src/hello.c -> kernel build system -> lab02_hello.ko -> insmod -> code runs in kernel
```

A module bug can crash the whole board. Only load the module you built and
checked in this lab.

## 4. Inspect the starter files

This lab directory contains:

```text
lab02-first-kernel-module/
├── README.md
├── Makefile
├── report.md
├── .gitignore
└── src/
    └── hello.c
```

**[HOST]**, open a terminal in this lab directory (the directory containing
this README and Makefile):

```bash
pwd
ls -la
sed -n '1,200p' src/hello.c
sed -n '1,240p' Makefile
```

Write your work in this lab directory and record results in `report.md`.
The shared kernel tree stays outside your course fork.

### Important parts of `src/hello.c`

The Linux headers provide the kernel module API:

```c
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
```

Metadata describes the module:

```c
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Lab 02 hello module for BeagleBone Black");
MODULE_VERSION("1.0");
```

`hello_init()` runs during `insmod`; `hello_exit()` runs during `rmmod`.
`pr_info()` writes to the kernel log, which is read with `dmesg`.

```c
module_init(hello_init);
module_exit(hello_exit);
```

The starter also demonstrates a string parameter named `name`, passed as:

```bash
sudo insmod lab02_hello.ko name=Student
```

### Important parts of the Makefile

```makefile
MODULE_NAME = lab02_hello
obj-m += $(MODULE_NAME).o
$(MODULE_NAME)-objs := src/hello.o
```

This tells Kbuild to compile `src/hello.c` to `src/hello.o` and link it into
the loadable module `lab02_hello.ko`.

```text
KDIR          matching configured kernel tree
M             external-module source directory
ARCH=arm      target architecture
CROSS_COMPILE ARM compiler prefix
```

The build is equivalent to:

```bash
make -C ~/bbb-workspace/kernel/bb-kernel/KERNEL M="$PWD" \
  ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- modules
```

Recipe lines below Makefile targets must begin with a TAB, not spaces.

## 5. Use the correct compiler

The `bb-kernel` build downloads the compiler used for the kernel under
`~/bbb-workspace/kernel/bb-kernel/dl`. The lab Makefile uses the prefix
`arm-linux-gnueabi-`, so put that downloaded compiler on your HOST `PATH`
before building.

Find it:

```bash
find ~/bbb-workspace/kernel/bb-kernel/dl -type f -name arm-linux-gnueabi-gcc
```

A typical result is:

```text
~/bbb-workspace/kernel/bb-kernel/dl/gcc-14.3.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc
```

Use the directory containing the compiler found above; adjust the version if
needed. Run this in the same HOST shell as the build commands:

```bash
export PATH="$HOME/bbb-workspace/kernel/bb-kernel/dl/gcc-14.3.0-nolibc/arm-linux-gnueabi/bin:$PATH"
command -v arm-linux-gnueabi-gcc
arm-linux-gnueabi-gcc --version
```

Repeat the PATH setup when opening a new shell. The compiler prefix ends with a
dash and does not include `gcc`. As an alternative to PATH, override it when
invoking `make`:

```bash
make CROSS_COMPILE=/absolute/path/to/arm-linux-gnueabi-
```

## 6. Build on HOST

```bash
make clean
make
```

Normal output contains stages similar to:

```text
CC [M]  src/hello.o
LD [M]  lab02_hello.o
MODPOST Module.symvers
CC [M]  lab02_hello.mod.o
LD [M]  lab02_hello.ko
```

Check the artifact:

```bash
ls -lh lab02_hello.ko
file lab02_hello.ko
```

Expected keywords are `ELF 32-bit`, `relocatable`, `ARM`, and `EABI5`. A `.ko`
is not a user executable, so do not run `./lab02_hello.ko`.

## 7. Check metadata and `vermagic`

**[HOST]**

```bash
modinfo lab02_hello.ko
modinfo lab02_hello.ko | grep vermagic
```

Example only:

```text
vermagic: 6.12.93-bone63 preempt mod_unload ARMv7 thumb2 p2v8
```

Your exact release may differ. The release at the start of `vermagic` must equal
`uname -r` on your BBB. Record the complete `vermagic` in `report.md`.

## 8. Copy the module to BBB

On **[HOST]**, create the destination and copy the module manually:

```bash
ssh debian@192.168.7.2 'mkdir -p /home/debian/labs/lab02'
scp lab02_hello.ko debian@192.168.7.2:/home/debian/labs/lab02/
```

## 9. Check again on BBB before loading

```bash
ssh debian@192.168.7.2
cd /home/debian/labs/lab02
uname -r
modinfo ./lab02_hello.ko | grep vermagic
file ./lab02_hello.ko
```

Do not continue if the full releases differ.

## 10. Load the module

**[BBB]**

```bash
sudo insmod ./lab02_hello.ko name=Student
sudo dmesg | tail -20
```

Expected module message:

```text
hello_module: Hello, Student, from kernel space on BBB!
```

You may also see `loading out-of-tree module taints kernel`. That is normal for
this lab because the module was built outside the main kernel source tree.

Do not run `insmod` a second time while the module is loaded; it will report
`File exists`.

## 11. Inspect the loaded module

**[BBB]**

```bash
lsmod | grep lab02_hello
modinfo ./lab02_hello.ko
cat /sys/module/lab02_hello/parameters/name
```

`lsmod` should show a line beginning with `lab02_hello`.

## 12. Unload the module

**[BBB]**

```bash
sudo rmmod lab02_hello
sudo dmesg | tail -20
lsmod | grep lab02_hello || echo 'module unloaded'
```

Use the module name `lab02_hello` with `rmmod`, not the filename `lab02_hello.ko`.
Expected log message:

```text
hello_module: Goodbye from kernel space on BBB!
```

## 13. Student tasks

1. Change `MODULE_AUTHOR("Student")` to your name.
2. Explain the existing `name` parameter and its permissions `0444`.
3. Test `name=YourName` and confirm it in `dmesg`.
4. Test an empty name after unloading the module:

   ```bash
   sudo insmod lab02_hello.ko name=
   sudo dmesg | tail -20
   ```

   The initialization must reject it with `-EINVAL`.

5. Add an unsigned integer parameter `count`, valid from 1 to 10.
6. Print the greeting `count` times. Reject invalid values with `-EINVAL`.
7. Test valid and invalid values and unload after each successful load.

## 14. Common problems

### `arm-linux-gnueabi-gcc: Command not found`

Finish Lab 01's kernel build, locate the compiler with `find`, and pass its
absolute prefix through `CROSS_COMPILE=...-`.

### The compiler differs from the one used to build the kernel

Use the compiler downloaded by this exact `bb-kernel` build, not an unrelated
HOST compiler.

### Unsupported `-ftrivial-auto-var-init` or `-mstack-protector-guard`

The selected compiler is too old for the kernel configuration. Use the
`bb-kernel` toolchain.

### `invalid module format`

Compare:

```bash
# HOST
modinfo lab02_hello.ko | grep vermagic

# BBB
uname -r
sudo dmesg | tail -30
```

Rebuild against the matching configured tree. Never force-load the module.

### `Operation not permitted`

Use `sudo insmod ./lab02_hello.ko`. If it remains, check whether the board image
enforces signed modules or another security policy.

### `File exists`

The module is already loaded:

```bash
lsmod | grep lab02_hello
sudo rmmod lab02_hello
```

### `rmmod: Module lab02_hello is in use`

Close any users of the module before unloading it. Do not force removal.

### Exact kernel headers are unavailable through `apt`

Use the matching `~/bbb-workspace/kernel/bb-kernel/KERNEL` tree built on HOST.
Headers from a different release are not a substitute.

## 15. Submission

Submit a PR from `lab02` to `master` **in your own fork**, following the
[student workflow](../../docs/student-workflow.md). Include the files and
report evidence listed below, and send the instructor the PR URL. If a
classroom platform or LMS is used, submit that URL there as well.

The lab is accepted only after `@ant112342` approves the PR. Address review
comments on the same branch and merge only after approval of the current work.

- `src/hello.c`, `Makefile`, and completed `report.md` with your name and
  GitHub username;
- BBB `uname -r`, `file lab02_hello.ko`, and the complete module `vermagic`;
- `lsmod` output and relevant load/unload `dmesg` lines;
- valid `name`/`count` tests and invalid-input tests;
- a short explanation of why a module must match its running kernel.

Do not commit `.ko`, `.o`, `.cmd`, `Module.symvers`, or `modules.order`.

## 16. Success checklist

```text
[ ] HOST kernel release equals BBB uname -r
[ ] lab02_hello.ko is a 32-bit ARM relocatable ELF
[ ] vermagic matches the running kernel
[ ] insmod calls hello_init()
[ ] dmesg contains the greeting
[ ] lsmod shows lab02_hello
[ ] rmmod calls hello_exit()
[ ] dmesg contains the goodbye message
```

## 17. Next topics

- character devices and `/dev` nodes;
- `open`, `release`, `read`, and `write` callbacks;
- platform drivers and Device Tree;
- GPIO, interrupts, I2C, and SPI.
