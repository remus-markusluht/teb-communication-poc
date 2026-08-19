# SonosNewJMP TEB Communication POC

SonosNewJMP is a proof-of-concept Visual Studio C++ workspace for Windows kernel and user-mode research. The solution demonstrates a TEB-based user-mode communication path for a KMDF driver, alongside mapper support code and a loader scaffold inside one low-level Windows research project.

This repository is not production software. It is intended for controlled lab environments, reproducible experimentation, and review of the project structure around privileged Windows components.

## Table of Contents

1. [POC Scope](#poc-scope)
2. [Project Layout](#project-layout)
3. [Components](#components)
4. [Requirements](#requirements)
5. [Build Notes](#build-notes)
6. [Generated Files](#generated-files)
7. [Roadmap](#roadmap)
8. [Responsible Use](#responsible-use)

## POC Scope

The POC focuses on source organization and integration points for a Windows kernel/user-mode research stack. Its main research point is the TEB-based communication layer used between the user-mode client and the driver. It is useful for reviewing how the driver, client, mapper, and loader pieces fit together before converting the workspace into a cleaner, portable build.

Current scope:

- `RELEASE_KERNEL` builds the Windows kernel-mode driver.
- `RELEASE_USERMODE` builds the user-mode client, including the TEB-based driver communication setup and rendering/client support code.
- `RELEASE_MAPPER` contains PE and driver-mapping support code.
- `RELEASE_LOADER` is a loader executable scaffold.

Out of scope for this POC:

- Production deployment.
- Turnkey setup on arbitrary machines.
- Public distribution of signed driver artifacts.
- Operational instructions for use against third-party software or systems.

The workspace includes helper batch scripts for local key generation, signing, and protection steps. Those scripts are machine-specific and should be treated as examples that require review before use.

## Project Layout

```text
.
|-- SonosNewJMP.sln
|-- RELEASE_KERNEL/      Kernel-mode driver project
|-- RELEASE_USERMODE/    User-mode client, overlay, and support libraries
|-- gD/                  Mapper project and PE loading utilities
|-- RELEASE_LOADER/      Loader application scaffold
|-- anc.bat              Local post-build signing/protection script
|-- snc.bat              Local pre-build key generation script
```

## Components

### Kernel Driver

`RELEASE_KERNEL` is a KMDF driver project targeting Windows 10. It contains the driver entry point and the supporting modules used by the POC driver interface.

### User-Mode Client

`RELEASE_USERMODE` is a Windows user-mode application. It includes the client-side TEB communication setup used by the POC driver interface, DirectX 11 and ImGui rendering scaffolding, utility code, and bundled static dependencies required by the current project configuration.

### Mapper

`gD` builds the `RELEASE_MAPPER` project. It contains PE parsing and loading support code and produces mapper-related build output under `Compiled/` during local builds.

### Loader

`RELEASE_LOADER` is currently a minimal console application scaffold. It is included in the solution so the loader surface can be expanded without changing the overall project structure.

## Requirements

- Windows 10 or Windows 11 x64 development machine.
- Visual Studio 2022 with the MSVC v143 toolset.
- Windows 10/11 SDK.
- Windows Driver Kit configured for KMDF driver builds.
- DirectX SDK June 2010 for the current `RELEASE_USERMODE` include and library paths.
- Local code-signing configuration if building signed driver artifacts.
- Optional local protection/virtualization tooling if using the post-build protection script.

## Build Notes

This is currently a POC build layout, not a polished release pipeline.

1. Open `SonosNewJMP.sln` in Visual Studio 2022.
2. Select the `Release|x64` configuration for the workspace.
3. Build `RELEASE_MAPPER` first if your local workflow depends on mapper output.
4. Build `RELEASE_KERNEL` and `RELEASE_USERMODE` from the solution.
5. Review `anc.bat` and `snc.bat` before enabling automated pre-build or post-build steps on a new machine.

The current batch scripts contain absolute local paths for signing and protection tooling. Treat those scripts as environment templates, not portable build automation.

## Generated Files

Local builds produce Visual Studio intermediates, binaries, symbols, logs, generated key headers, and protection output. These files are intentionally excluded by `.gitignore` so the repository can stay focused on source, project configuration, and documentation.

Ignored examples include:

- `.vs/`
- `x64/`, `Debug/`, `Release/`, `obj/`, and `Compiled/`
- `*.obj`, `*.pdb`, `*.ipdb`, `*.iobj`, `*.tlog`, `*.log`, and `*.recipe`
- `*.exe`, `*.dll`, and `*.sys`
- Generated `key.h` files
- Private signing material such as `*.pfx` and `*.p12`
- Local protection SDK/tooling under `CodeCS/`

## Roadmap

- Convert machine-specific scripts into configurable POC build scripts.
- Move generated key material into an intermediate build directory.
- Add a reproducible clean-machine setup guide.
- Split third-party dependencies from first-party source code.
- Add static analysis and warning-clean build targets.
- Document validated Windows, SDK, and WDK versions.
- Promote stable POC pieces into clearer library boundaries.

## Responsible Use

This POC works in privileged Windows contexts and can affect system stability. Use it only on systems you own or are explicitly authorized to test. Do not use the project against third-party software, services, or devices without permission.

No license file is currently included. Add a `LICENSE` before publishing or accepting external contributions.
