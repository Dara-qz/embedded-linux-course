# Lab 01 report

- Student name: Даша
- GitHub username: Dara-qz
- Image filename: am335x-debian-12.9-minimal-armhf-2025-01-08-4gb.img.xz
- SHA-256 (paste the checksum and state whether it matches the lab): Matches the verified sha256sum from the lab instructions.

Replace each placeholder with your own command output. Label HOST and BBB
results. Do not include passwords or private keys.
## Running Linux on BBB

### BBB: `uname -r`

```text
6.12.96-bone64

### BBB: `cat /etc/os-release`

PRETTY_NAME="Debian GNU/Linux 13 (trixie)"
NAME="Debian GNU/Linux"
VERSION_ID="13"
VERSION="13 (trixie)"
VERSION_CODENAME=trixie
DEBIAN_VERSION_FULL=13.6
ID=debian
HOME_URL="[https://www.debian.org/](https://www.debian.org/)"
SUPPORT_URL="[https://www.debian.org/support](https://www.debian.org/support)"
BUG_REPORT_URL="[https://bugs.debian.org/](https://bugs.debian.org/)"

### BBB: `lsblk`

NAME         MAJ:MIN RM   SIZE RO TYPE MOUNTPOINTS
mmcblk1      179:0    0   3.6G  0 disk 
`-mmcblk1p1  179:1    0   3.6G  0 part 
zram0        253:0    0   241M  0 disk [SWAP]
mmcblk0      179:256  0  14.6G  0 disk 
|-mmcblk0p1  179:257  0    36M  0 part /boot/firmware
|-mmcblk0p2  179:258  0   512M  0 part [SWAP]
`-mmcblk0p3  179:259  0    14G  0 part /
mmcblk1boot0 179:512  0     2M  1 disk 
mmcblk1boot1 179:768  0     2M  1 disk

### BBB: `ip addr`

1: lo:  mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host noprefixroute 
       valid_lft forever preferred_lft forever
2: eth0:  mtu 1500 qdisc mq state DOWN group default qlen 1000
    link/ether 78:04:73:41:61:a0 brd ff:ff:ff:ff:ff:ff
    altname end0
    altname enx7804734161a0
3: usb0:  mtu 1500 qdisc fq_codel state UP group default qlen 1000
    link/ether 78:04:73:41:61:a3 brd ff:ff:ff:ff:ff:ff
    inet 192.168.7.2/30 brd 192.168.7.3 scope global usb0
       valid_lft forever preferred_lft forever
    inet6 fe80::7a04:73ff:fe41:61a3/64 scope link proto kernel_ll 
       valid_lft forever preferred_lft forever

## First user-space program

### HOST, in this lab directory: `file build/hello`

hello: ELF 32-bit LSB pie executable, ARM, EABI5 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux-armhf.so.3, BuildID[sha1]=79c58fc66307ce6957f656fcf0dc9619db5fbb6, for GNU/Linux 3.2.0, not stripped

### BBB: `/home/debian/labs/lab01/hello`
Hello, Embedded Linux on BeagleBone Black!


### HOST: `ls -lh ~/bbb-workspace/kernel/bb-kernel/deploy`

total 35M
-rw-r--r-- 1 Daria Daria 177K Sep 17 13:14 6.12.109-bone72-dtbs.tar.zst
-rw-r--r-- 1 Daria Daria  26M Sep 17 13:14 6.12.109-bone72-modules.tar.zst
-rwxr-xr-x 1 Daria Daria 8.4M Sep 17 13:13 6.12.109-bone72.zImage
-rw-r--r-- 1 Daria Daria 206K Sep 17 13:13 config-6.12.109-bone72

### HOST: `cat ~/bbb-workspace/kernel/bb-kernel/KERNEL/include/config/kernel.release`

6.12.109-bone72

Do the full HOST and BBB kernel-release strings match exactly?

No. The host workspace compiled version 6.12.109-bone72, while the target BBB board is currently running 6.12.96-bone64.

Why must Lab 02 use a matching kernel tree?

Loadable kernel modules (LKM) must be compiled against the exact kernel version, configuration, and internal data structures matching the running kernel. Discrepancies cause vermagic and symbol CRC checksum mismatches, causing the kernel module loader to reject the module on the target.

Submit this completed report with src/hello.c and Makefile. Do not commit
images, executables, toolchains, kernel sources, or build artifacts.