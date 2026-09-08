# Course workspace

This repository does not contain the Linux kernel source tree. It contains
course documentation, reference examples, and self-contained lab templates for
future GitHub Classroom assignments. Students work in their own lab repositories.

During [Lab 01](../classroom-templates/lab01-board-bringup/README.md), each student
creates a shared local workspace outside the course and lab repositories:

```text
~/bbb-workspace/
├── downloads/
├── kernel/
│   └── bb-kernel/
│       ├── KERNEL/
│       ├── deploy/
│       └── dl/
└── target-info/
```

On HOST:

```bash
mkdir -p ~/bbb-workspace/downloads
mkdir -p ~/bbb-workspace/kernel
mkdir -p ~/bbb-workspace/target-info
```

- `downloads/` holds downloaded board images and checksums.
- `kernel/bb-kernel/` is the separate kernel-builder clone created in Lab 01.
- `KERNEL/` contains the configured and built Linux kernel tree.
- `deploy/` contains the resulting kernel image, modules, configuration, and DTBs.
- `dl/` holds the downloaded compiler and other kernel-build downloads.
- `target-info/` can hold local board information; copy required evidence into
  each lab's `report.md` for submission.

Lab 01 creates the kernel workspace with these HOST commands:

```bash
cd ~/bbb-workspace/kernel
git clone https://github.com/RobertCNelson/bb-kernel.git
cd bb-kernel
git checkout origin/am33x-v6.12 -b am33x-v6.12-course
./build_kernel.sh
```

All later kernel-module labs use:

```text
~/bbb-workspace/kernel/bb-kernel/KERNEL
```

Makefiles express this as `$(HOME)/bbb-workspace/kernel/bb-kernel/KERNEL`, so
there is no dependency on the course repository's location or a particular PC.
Use the compiler downloaded by that kernel build; Lab 02 explains PATH setup.

Before building and loading a module, compare the complete HOST release from
`~/bbb-workspace/kernel/bb-kernel/KERNEL/include/config/kernel.release` with
`uname -r` on BBB. They must match exactly, including the release suffix; a
shared `6.12` prefix is insufficient. Never force-load a mismatched module.
If they differ, obtain the course-pinned commit matching the assigned image
from the instructor, as described in Lab 01.

On a new PC, repeat Lab 01 to recreate this workspace and perform the same
release check. Cloning a lab repository alone does not provide a kernel tree.

Keep kernel sources, toolchains, downloaded images, and generated build
artifacts out of the course and Classroom Git repositories. Commit lab source,
Makefiles, and completed reports. The separate `bb-kernel` clone has its own
upstream Git history; it must not be copied or added into a lab repository.
