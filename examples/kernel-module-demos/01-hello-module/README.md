# Hello external kernel module example

The source is `src/hello.c`. Complete Lab 01 first to prepare
`~/bbb-workspace/kernel/bb-kernel/KERNEL`. From this example directory, build
against that shared kernel tree and inspect compatibility:

```bash
make
make check
```

Copy, load, inspect, and unload on the board:

```bash
make deploy BBB_HOST=192.168.7.2
make load BBB_HOST=192.168.7.2
make unload BBB_HOST=192.168.7.2
```

`KDIR`, `ARCH`, and `CROSS_COMPILE` are configurable. The Makefile automatically
uses a compatible toolchain downloaded by `bb-kernel` when one is present.
