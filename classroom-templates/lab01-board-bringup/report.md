# Lab 01 report

- Student name:
- GitHub username:
- Image filename:
- SHA-256 (paste the checksum and state whether it matches the lab):

Replace each placeholder with your own command output. Label HOST and BBB
results. Do not include passwords or private keys.

## Running Linux on BBB

### BBB: `uname -r`

```text
<paste output>
```

### BBB: `cat /etc/os-release`

```text
<paste output>
```

### BBB: `lsblk`

```text
<paste output>
```

### BBB: `ip addr`

```text
<paste output>
```

## First user-space program

### HOST, in this lab directory: `file build/hello`

```text
<paste output>
```

### BBB: `/home/debian/labs/lab01/hello`

```text
<paste program output>
```

## Shared kernel workspace

### HOST: `ls -lh ~/bbb-workspace/kernel/bb-kernel/deploy`

```text
<paste file list>
```

### HOST: `cat ~/bbb-workspace/kernel/bb-kernel/KERNEL/include/config/kernel.release`

```text
<paste complete kernel release>
```

Do the full HOST and BBB kernel-release strings match exactly?

<answer>

Why must Lab 02 use a matching kernel tree?

<short answer>

Submit this completed report with `src/hello.c` and `Makefile`. Do not commit
images, executables, toolchains, kernel sources, or build artifacts.
