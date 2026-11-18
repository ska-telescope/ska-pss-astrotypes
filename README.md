# astrotypes

Common Data Types and data utilities for Pulsar Data.

## Documentation

The documentation for this repository can be found on our 
[GitHub page](https://pulsarsearchsoft.github.io/astrotypes/).

# Dependencies

- Ubuntu 26.04 build tools (GCC 15 and make)
- cmake - 4.2 (minimum 3.14)
- boost - 1.90.0

## Ubuntu 26.04 builds

CI build and test jobs use the pinned Ubuntu 26.04 `buildpack-deps` image
on Docker runners selected by `RUNNER_TAG` (default: `pss-dokimi-docker`).
The image, not the runner tag, selects the userspace OS.

Use fresh build and install directories when changing the OS or Boost version.
GoogleTest build output is isolated per build directory. Build downstream
Cheetah with the same OS/Boost toolchain and the matching Panda upgrade.
