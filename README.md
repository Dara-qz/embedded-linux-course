# Embedded Linux on BeagleBone Black

Beginner-oriented course repository for Embedded Linux on the BeagleBone Black
(BBB). Each lab provides ordered commands, explanations, expected results, and
troubleshooting.

## Where students should start

Do not try to understand every directory or the top-level Makefile immediately.

1. Follow the [student workflow](docs/student-workflow.md) to create your fork,
   set up instructor review, and start a `lab01` branch. Then open
   [Lab 01](classroom-templates/lab01-board-bringup/README.md).
2. Follow it from top to bottom. Commands are labelled **HOST** (Linux PC) or
   **BBB** (BeagleBone Black).
3. Complete [Lab 02](classroom-templates/lab02-first-kernel-module/README.md) only after Lab 01.
4. `examples/` contains finished references. `classroom-templates/` contains
   lab instructions and starter files. Complete these files in your own fork;
   keep one fork for the whole course.

## Repository layout

```text
.
├── README.md
├── .gitignore
├── Makefile                  Optional reference-example shortcuts
├── docs/
│   ├── course-workspace.md
│   └── student-workflow.md
├── examples/
│   ├── userspace-programs/01-hello-user/
│   └── kernel-module-demos/01-hello-module/
└── classroom-templates/
    ├── README.md
    ├── lab01-board-bringup/
    └── lab02-first-kernel-module/
```

Each lab template contains `README.md`, `Makefile`, `report.md`, `.gitignore`,
and `src/hello.c`. Each reference example contains `README.md`, `Makefile`, and
`src/hello.c`.

The Linux kernel source is outside this repository. Lab 01 creates the shared
`~/bbb-workspace/` described in [the workspace guide](docs/course-workspace.md).
All kernel-module labs use `~/bbb-workspace/kernel/bb-kernel/KERNEL`.

## HOST preparation

On an Ubuntu/Debian host, install the tools:

```bash
sudo apt update
sudo apt install -y git build-essential bc bison flex libssl-dev \
  libncurses-dev libelf-dev dwarves lzop u-boot-tools rsync xz-utils \
  zstd device-tree-compiler gcc-arm-linux-gnueabihf \
  g++-arm-linux-gnueabihf openssh-client minicom
```

Create and clone your personal fork using the
[student workflow](docs/student-workflow.md). From the root of that clone,
open Lab 01:

```bash
less classroom-templates/lab01-board-bringup/README.md
```

Follow Lab 01 to clone and build the kernel in the shared workspace. The build is
large, takes time, and downloads a toolchain and Linux sources.

Lab 01 teaches manual compile, inspect, copy, and run commands first. Its
Makefile provides optional `make` and `make clean` shortcuts after those steps
are understood. The completed user-space reference can still be built from the
repository root with:

```bash
make user
make user-deploy BBB_HOST=192.168.7.2 BBB_USER=debian
```

After completing Lab 01, the module reference can be built with:

```bash
make module
make module-deploy BBB_HOST=192.168.7.2 BBB_USER=debian
```

The Makefiles never flash a raw SD-card image automatically. Lab 01 documents
the explicit, safety-critical image-writing command.

## Course workflow

1. Create a separate lab branch in your fork and read the lab's `README.md`.
2. Write code only in that lab directory unless instructed otherwise.
3. In Lab 01, run the documented compiler, `scp`, and `ssh` commands manually.
4. In later labs, use their Makefiles where the instructions introduce them.
5. Test the result on the BBB as described in the lab.
6. Complete `report.md`, commit source, Makefile, and report, and open a PR from
   your lab branch to `master` in your own fork. Keep generated outputs out of Git.
7. Address the instructor's feedback and merge only after their approval.

**A lab is accepted only after `@ant112342` approves its PR. A push or merge
alone does not count as acceptance.** See the
[student workflow](docs/student-workflow.md) for the required fork protection
settings and how to receive new labs through an update PR. If a classroom
platform or LMS is used, submit the same PR URL there.

The reference examples provide optional deployment helpers whose defaults can
be overridden on the command line. Run this from an example directory:

```bash
make deploy BBB_HOST=192.168.7.2 BBB_USER=debian BBB_DIR=/home/debian/labs
```

## Important compatibility rule

An external module must be built against the same kernel release and compatible
configuration/toolchain as the kernel running on the board. Compare:

```bash
# On the BBB
uname -r

# On the host, after building a module
modinfo path/to/module.ko | grep vermagic
```

If the releases differ, do not force-load the module. Build the matching kernel
tree first.

## Labs

- [Lab 01: board bring-up and kernel source preparation](classroom-templates/lab01-board-bringup/README.md)
- [Lab 02: first external kernel module](classroom-templates/lab02-first-kernel-module/README.md)
- [Kernel workspace guide](docs/course-workspace.md)

## Safety

- Verify SD-card device names with `lsblk` before using `dd`.
- Never use the host system disk as the `dd` output.
- Do not load a module whose `vermagic` does not match the target.
- Keep generated binaries, kernel sources, toolchains, and credentials out of
  Git; the repository `.gitignore` covers the standard build outputs.
