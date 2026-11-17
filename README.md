# Avirah

Avirah is a self-hosted application deployment and orchestration platform for deploying, managing, monitoring, and scaling containerized applications across Linux and Windows worker nodes.

## Repository status

The repository is currently implementing the phase-wise architecture plan. P01 establishes the portable C++20/CMake source tree and build/test conventions. Runtime orchestration, the web console, worker synchronization, persistence and Docker integration are intentionally delivered in later phases.

## Build prerequisites

- CMake 3.28 or newer
- Ninja
- C++20 compiler: GCC/Clang on Linux or MSVC on Windows
- vcpkg for the pinned dependency set once the P00 dependency and licensing decisions are recorded

The native P01 targets do not require external libraries. From a Linux environment use:

```text
cmake --preset linux-gcc-debug
cmake --build --preset linux-gcc-debug
ctest --preset linux-gcc-debug
```

From a Visual Studio developer environment on Windows use the corresponding `windows-msvc-debug` presets.

The optional Wt feasibility prototype is disabled by default and must not be treated as a completed UI until its distribution-license decision and native runtime evidence are recorded.

## Executables

- `avirah-server` — future control-plane process; currently prints build identity.
- `avirah-agent` — future worker process; currently prints build identity.
- `avirah` — future API/diagnostic CLI; currently prints build identity.
- `avirah-test-driver` — native acceptance harness entry point.
- `avirah-browser-tests` — browser-test harness entry point.
