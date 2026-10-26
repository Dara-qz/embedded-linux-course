# Lab 02 report

- Student name: Bezuhlova Daria
- GitHub username:Dara-qz

Replace each placeholder with your own command output. Run HOST build commands
from this lab directory and BBB module commands from `/home/debian/labs/lab02`.
Keep the complete `vermagic`, not only its release prefix.

## Prerequisites and module metadata

### BBB: `uname -r`

```text
6.12.96-bone64
```

### HOST: `cat ~/bbb-workspace/kernel/bb-kernel/KERNEL/include/config/kernel.release`

```text
6.12.96-bone64
```

### HOST: `file lab02_hello.ko`

```text
./lab02_hello.ko: ELF 32-bit LSB relocatable, ARM, EABI5 version 1 (SYSV), BuildID[sha1]=445411043228ce786366ed200bab828e486365f5, not stripped
```

### HOST: `modinfo lab02_hello.ko | grep vermagic`

```text
vermagic:       6.12.96-bone64 preempt mod_unload ARMv7 thumb2 p2v8 
```

Explain why the full kernel releases must match and whether yours match:

Kernel modules execute directly in kernel space and depend on the internal data structures, ABIs, and symbol tables of a specific kernel build. The vermagic string enforces strict runtime binary compatibility: if versions or configuration flags differ, insmod rejects the module to prevent memory corruption or a kernel panic. In our setup, both the HOST build tree and the BBB target board run kernel release 6.12.96-bone64, so they match exactly.

## Load, inspect, and unload on BBB

### `sudo insmod ./lab02_hello.ko name=Student` and `sudo dmesg | tail -20`

```text
[   20.395361] systemd[1]: Started systemd-journald.service - Journal Service.
[   21.817072] EXT4-fs (mmcblk0p3): re-mounted 82c179da-9fb5-46fc-b6b4-9da3f7562c69 r/w.
[   22.710914] systemd-journald[235]: Received client request to flush runtime journal.
[   26.500832] zram0: detected capacity change from 0 to 493568
[   27.013411] Adding 246780k swap on /dev/zram0.  Priority:100 extents:1 across:246780k SSDsc
[   30.777609] Adding 524284k swap on /dev/mmcblk0p2.  Priority:-2 extents:1 across:524284k SS
[   35.218291] cfg80211: Loading compiled-in X.509 certificates for regulatory database
[   35.247920] Loaded X.509 cert 'sforshee: 00b28ddf47aef9cea7'
[   35.275637] Loaded X.509 cert 'wens: 61c038651aabdcf94bd0ac7ff06c7248db18c600'
[   35.664813] cpsw-switch 4a100000.switch: starting ndev. mode: dual_mac
[   35.770094] SMSC LAN8710/LAN8720 4a101000.mdio:00: attached PHY driver (mii_bus:phy_addr=4a101000.mdio:00, irq=POLL)
[   36.119482] at24 2-0054: supply vcc not found, using dummy regulator
[   36.395372] at24 2-0055: supply vcc not found, using dummy regulator
[   36.585594] at24 2-0056: supply vcc not found, using dummy regulator
[   36.795421] at24 2-0057: supply vcc not found, using dummy regulator
[   37.053685] at24 0-0050: 4096 byte 24c32 EEPROM, writable, 1 bytes/write
[   40.018075] configfs-gadget.g_multi gadget.0: HOST MAC 78:04:73:41:61:a2
[   40.060319] configfs-gadget.g_multi gadget.0: MAC 78:04:73:41:61:a3
[ 5723.672035] lab02_hello: loading out-of-tree module taints kernel.
[ 5723.679061] hello_module: Hello, Student, from kernel space on BBB!
```

### `lsmod | grep lab02_hello`

```text
lab02_hello            12288  0
```

### `sudo rmmod lab02_hello` and `sudo dmesg | tail -20`

```text
[   21.817072] EXT4-fs (mmcblk0p3): re-mounted 82c179da-9fb5-46fc-b6b4-9da3f7562c69 r/w.
[   22.710914] systemd-journald[235]: Received client request to flush runtime journal.
[   26.500832] zram0: detected capacity change from 0 to 493568
[   27.013411] Adding 246780k swap on /dev/zram0.  Priority:100 extents:1 across:246780k SSDsc
[   30.777609] Adding 524284k swap on /dev/mmcblk0p2.  Priority:-2 extents:1 across:524284k SS
[   35.218291] cfg80211: Loading compiled-in X.509 certificates for regulatory database
[   35.247920] Loaded X.509 cert 'sforshee: 00b28ddf47aef9cea7'
[   35.275637] Loaded X.509 cert 'wens: 61c038651aabdcf94bd0ac7ff06c7248db18c600'
[   35.664813] cpsw-switch 4a100000.switch: starting ndev. mode: dual_mac
[   35.770094] SMSC LAN8710/LAN8720 4a101000.mdio:00: attached PHY driver (mii_bus:phy_addr=4a101000.mdio:00, irq=POLL)
[   36.119482] at24 2-0054: supply vcc not found, using dummy regulator
[   36.395372] at24 2-0055: supply vcc not found, using dummy regulator
[   36.585594] at24 2-0056: supply vcc not found, using dummy regulator
[   36.795421] at24 2-0057: supply vcc not found, using dummy regulator
[   37.053685] at24 0-0050: 4096 byte 24c32 EEPROM, writable, 1 bytes/write
[   40.018075] configfs-gadget.g_multi gadget.0: HOST MAC 78:04:73:41:61:a2
[   40.060319] configfs-gadget.g_multi gadget.0: MAC 78:04:73:41:61:a3
[ 5723.672035] lab02_hello: loading out-of-tree module taints kernel.
[ 5723.679061] hello_module: Hello, Student, from kernel space on BBB!
[ 6154.112415] hello_module: Goodbye from kernel space on BBB!
```

## Parameter tests on BBB

After implementing the student tasks, rebuild, check metadata, and copy the
module again. Unload after every successful load before testing another case.
For each case record the command, result, and relevant `dmesg` output. Capture
`echo $?` immediately after `insmod` to record its exit status.

### Valid name: `name=YourName`

```text
debian@BeagleBone:~/labs/lab02$ sudo insmod ./lab02_hello.ko name=Darinka
[sudo] password for debian: 
debian@BeagleBone:~/labs/lab02$ echo $?
0

debian@BeagleBone:~/labs/lab02$ sudo dmesg | tail -5
[   36.826190] at24 0-0050: 4096 byte 24c32 EEPROM, writable, 1 bytes/write
[   39.308960] configfs-gadget.g_multi gadget.0: HOST MAC 78:04:73:41:61:a2
[   39.349162] configfs-gadget.g_multi gadget.0: MAC 78:04:73:41:61:a3
[  853.799835] lab02_hello: loading out-of-tree module taints kernel.
[  853.806732] hello_module: Hello, Darinka, from kernel space on BBB!
```

### Invalid empty name: `name=` (must return `-EINVAL`)

```text
debian@BeagleBone:~/labs/lab02$ sudo insmod lab02_hello.ko name=
[sudo] password for debian: 
insmod: ERROR: could not insert module lab02_hello.ko: Invalid parameters
debian@BeagleBone:~/labs/lab02$ echo $?
1
debian@BeagleBone:~/labs/lab02$ sudo dmesg | tail -10
[   35.867362] cpsw-switch 4a100000.switch: starting ndev. mode: dual_mac
[   35.973816] SMSC LAN8710/LAN8720 4a101000.mdio:00: attached PHY driver (mii_bus:phy_addr=4a101000.mdio:00, irq=POLL)
[   36.144195] at24 2-0056: supply vcc not found, using dummy regulator
[   36.579712] at24 2-0057: supply vcc not found, using dummy regulator
[   36.826190] at24 0-0050: 4096 byte 24c32 EEPROM, writable, 1 bytes/write
[   39.308960] configfs-gadget.g_multi gadget.0: HOST MAC 78:04:73:41:61:a2
[   39.349162] configfs-gadget.g_multi gadget.0: MAC 78:04:73:41:61:a3
[  853.799835] lab02_hello: loading out-of-tree module taints kernel.
[  853.806732] hello_module: Hello, Darinka, from kernel space on BBB!
[  923.168783] hello_module: Goodbye from kernel space on BBB!
```

### Valid count: test `count=1` and `count=10`

```text
debian@BeagleBone:~/labs/lab02$ sudo insmod lab02_hello.ko count=1
[sudo] password for debian: 
debian@BeagleBone:~/labs/lab02$ echo $?
0
debian@BeagleBone:~/labs/lab02$ sudo dmesg | tail -3
[  645.799781] hello_module: Hello, Student, from kernel space on BBB!
[  661.651216] hello_module: Goodbye from kernel space on BBB!
[  870.945749] hello_module: Hello, Student, from kernel space on BBB!
debian@BeagleBone:~/labs/lab02$ sudo rmmod lab02_hello
debian@BeagleBone:~/labs/lab02$ sudo insmod lab02_hello.ko count=10
debian@BeagleBone:~/labs/lab02$ echo $?
0
debian@BeagleBone:~/labs/lab02$ sudo dmesg | tail -12
[  870.945749] hello_module: Hello, Student, from kernel space on BBB!
[  922.699148] hello_module: Goodbye from kernel space on BBB!
[  956.989306] hello_module: Hello, Student, from kernel space on BBB!
[  956.995740] hello_module: Hello, Student, from kernel space on BBB!
[  957.003195] hello_module: Hello, Student, from kernel space on BBB!
[  957.010736] hello_module: Hello, Student, from kernel space on BBB!
[  957.017579] hello_module: Hello, Student, from kernel space on BBB!
[  957.026866] hello_module: Hello, Student, from kernel space on BBB!
[  957.033924] hello_module: Hello, Student, from kernel space on BBB!
[  957.040724] hello_module: Hello, Student, from kernel space on BBB!
[  957.048274] hello_module: Hello, Student, from kernel space on BBB!
[  957.055268] hello_module: Hello, Student, from kernel space on BBB!
debian@BeagleBone:~/labs/lab02$ sudo rmmod lab02_hello
```

### Invalid count: test `count=0` and `count=11` (must return `-EINVAL`)

```text
debian@BeagleBone:~/labs/lab02$ sudo insmod lab02_hello.ko count=0
insmod: ERROR: could not insert module lab02_hello.ko: Invalid parameters
debian@BeagleBone:~/labs/lab02$ echo $?
1
debian@BeagleBone:~/labs/lab02$ sudo dmesg | tail -3
[  957.055268] hello_module: Hello, Student, from kernel space on BBB!
[  976.230239] hello_module: Goodbye from kernel space on BBB!
[ 1062.834206] hello_module: Invalid count 0. Must be between 1 and 10!
debian@BeagleBone:~/labs/lab02$ sudo insmod lab02_hello.ko count=11
insmod: ERROR: could not insert module lab02_hello.ko: Invalid parameters
debian@BeagleBone:~/labs/lab02$ echo $?
1
debian@BeagleBone:~/labs/lab02$ sudo dmesg | tail -3
[  976.230239] hello_module: Goodbye from kernel space on BBB!
[ 1062.834206] hello_module: Invalid count 0. Must be between 1 and 10!
[ 1118.322216] hello_module: Invalid count 11. Must be between 1 and 10!
```

## Questions

1. Why does a kernel module not have `main()`?

   A kernel module is not an executable application running in user space; it is an event-driven extension of the kernel. Instead of a single entry-exit routine managed sequentially by `main()`, it registers its functions inside the kernel and waits to be invoked when specific hardware interrupts, system calls, or kernel events occur.

2. What does `module_init()` do?

 `module_init()` is a kernel macro that designates a specific initialization function to be invoked when the module is loaded (via `insmod` or `modprobe`). It places a pointer to this entry function in a dedicated ELF section (`.init.text`), allowing the kernel to execute it during insertion and discard the initialization code from memory afterward.

3. What does `vermagic` show?

`vermagic` (version magic) is a string embedded in the `.modinfo` ELF section of the module. It specifies the exact kernel release version, target architecture, compiler ABI, and critical kernel configuration flags (such as SMP, PREEMPT, module versioning) against which the module was compiled.

4. Why can `insmod` fail with `invalid module format`?

   `insmod` returns `Exec format error` / `Invalid module format` (errno `-ENOEXEC`) when the module's `vermagic` does not match the running kernel's version and configuration, when the binary was cross-compiled for a different processor architecture (e.g., x86_64 instead of ARM), or when module symbol CRC checksums disagree (`CONFIG_MODVERSIONS`).

5. What does the `name` parameter do, and what do its permissions `0444` mean?

The `name` parameter passes a configurable string from user space into the module at load time (e.g., `insmod lab02_hello.ko name=Darinka`) to customize the greeting log. The permission `0444` (`S_IRUGO`) creates a read-only entry under `/sys/module/<module_name>/parameters/name` in sysfs, allowing the user, group, and others to read the parameter's current value, but preventing anyone from modifying it while the module is running.

Submit `src/hello.c`, `Makefile`, and this completed `report.md`. Do not commit
`.ko`, `.o`, `.mod`, `.mod.c`, `.cmd`, `Module.symvers`, or `modules.order`.
