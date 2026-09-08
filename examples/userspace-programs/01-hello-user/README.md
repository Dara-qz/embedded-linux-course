# Hello user-space example

The source is `src/hello.c`. From this example directory, build, inspect, deploy,
and run:

```bash
make
file build/hello
make test BBB_HOST=192.168.7.2 BBB_USER=debian
```

`CROSS_COMPILE` defaults to `arm-linux-gnueabihf-` and can be overridden.
