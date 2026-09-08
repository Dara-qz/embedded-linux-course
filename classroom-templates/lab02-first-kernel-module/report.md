# Lab 02 report

- Student name:
- GitHub username:

Replace each placeholder with your own command output. Run HOST build commands
from this lab repository and BBB module commands from `/home/debian/labs/lab02`.
Keep the complete `vermagic`, not only its release prefix.

## Prerequisites and module metadata

### BBB: `uname -r`

```text
<paste complete running release>
```

### HOST: `cat ~/bbb-workspace/kernel/bb-kernel/KERNEL/include/config/kernel.release`

```text
<paste complete build-tree release>
```

### HOST: `file lab02_hello.ko`

```text
<paste output>
```

### HOST: `modinfo lab02_hello.ko | grep vermagic`

```text
<paste complete vermagic>
```

Explain why the full kernel releases must match and whether yours match:

<short answer>

## Load, inspect, and unload on BBB

### `sudo insmod ./lab02_hello.ko name=Student` and `sudo dmesg | tail -20`

```text
<paste load command and dmesg output>
```

### `lsmod | grep lab02_hello`

```text
<paste output>
```

### `sudo rmmod lab02_hello` and `sudo dmesg | tail -20`

```text
<paste unload command and dmesg output>
```

## Parameter tests on BBB

After implementing the student tasks, rebuild, check metadata, and copy the
module again. Unload after every successful load before testing another case.
For each case record the command, result, and relevant `dmesg` output. Capture
`echo $?` immediately after `insmod` to record its exit status.

### Valid name: `name=YourName`

```text
<command, result, and greeting>
```

### Invalid empty name: `name=` (must return `-EINVAL`)

```text
<command, error, exit status, and relevant dmesg>
```

### Valid count: test `count=1` and `count=10`

```text
<commands, results, and greeting counts>
```

### Invalid count: test `count=0` and `count=11` (must return `-EINVAL`)

```text
<commands, errors, exit statuses, and relevant dmesg>
```

## Questions

1. Why does a kernel module not have `main()`?

   <answer>

2. What does `module_init()` do?

   <answer>

3. What does `vermagic` show?

   <answer>

4. Why can `insmod` fail with `invalid module format`?

   <answer>

5. What does the `name` parameter do, and what do its permissions `0444` mean?

   <answer>

Submit `src/hello.c`, `Makefile`, and this completed `report.md`. Do not commit
`.ko`, `.o`, `.mod`, `.mod.c`, `.cmd`, `Module.symvers`, or `modules.order`.
