# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

SwiftASWF is a monolithic Swift package that bundles many ASWF (Academy Software Foundation) libraries for VFX applications. It serves as the **primary VFX dependency** for [SwiftUSD](https://github.com/wabiverse/SwiftUSD), providing cross-platform access to industry-standard graphics and media libraries.

## Relationship with SwiftUSD

SwiftASWF is consumed by SwiftUSD as a package dependency. SwiftUSD's `Arch` target (the foundation of all Pixar USD modules) imports these SwiftASWF products:

```swift
// From SwiftUSD's Package.swift - Arch target dependencies
.product(name: "MetaTBB", package: "SwiftASWF"),
.product(name: "MaterialX", package: "SwiftASWF"),
.product(name: "Alembic", package: "SwiftASWF"),
.product(name: "OpenColorIO", package: "SwiftASWF"),
.product(name: "OpenImageIO", package: "SwiftASWF"),
.product(name: "OpenEXR", package: "SwiftASWF"),
.product(name: "OpenSubdiv", package: "SwiftASWF"),
.product(name: "OpenVDB", package: "SwiftASWF"),
.product(name: "Ptex", package: "SwiftASWF"),
.product(name: "Draco", package: "SwiftASWF"),
.product(name: "Eigen", package: "SwiftASWF"),
.product(name: "Apple", package: "SwiftASWF"),  // Apple platforms only
```

When modifying SwiftASWF, consider the impact on SwiftUSD builds. Breaking changes to public headers or library exports will affect USD compilation.

## Build Commands

```bash
# Build release (recommended - debug builds are slow)
swift build -c release

# Build specific target
swift build -c release --target MetaversalDemo

# Run the demo app using Swift Bundler
swift bundler run -p macOS MetaversalDemo

# Run tests
swift test

# Initialize submodules (required before first build)
git submodule update --init --recursive
```

## Architecture

### Package Structure

The package wraps 30+ C/C++ libraries as Swift targets, configured in a single large `Package.swift`. Key architectural decisions:

- **Platform-conditional compilation**: The `Arch` enum handles platform detection (apple/linux/windows/web) and CPU architecture (arm64/x86_64/etc.) for conditional dependencies and target exclusions
- **Target configuration**: The `getConfig(for:)` function centralizes platform-specific excludes, settings, and linker flags for each target
- **C++ interoperability**: Targets use `.interoperabilityMode(.Cxx)` Swift settings for C++ interop

### Key Library Groups

| Category | Libraries | Used by SwiftUSD |
|----------|-----------|------------------|
| Threading | OneTBB, TBBMalloc, MetaTBB | MetaTBB (Work, threading) |
| Math/Core | Imath, Eigen, OpenEXR | All (Gf, Vt, imaging) |
| Imaging | OpenImageIO, OpenColorIO, TurboJPEG, TIFF, LibPNG, WebP, Raw | Hio, Glf, texture loading |
| 3D/Graphics | MaterialX, OpenSubdiv, OpenVDB, Alembic, Ptex, Draco | UsdMtlx, PxOsd, UsdVol, UsdAbc, UsdDraco |
| UI | ImGui, GLFW | Not directly used by USD |
| Compression | ZStandard, LZMA2, Blosc, MiniZip, DEFLATE | OpenVDB, asset compression |

### Platform Dependencies

- **macOS/iOS**: Uses MetaverseVulkanFramework (MoltenVK) for Vulkan support
- **Linux**: Requires system libraries (libbz2-dev, X11, OpenGL)
- **Windows**: Includes MicrosoftSTL compatibility layer

### External Package Dependencies

- libwebp, zlib, libpng from `the-swift-collective` GitHub org
- MetaverseVulkanFramework from `wabiverse` (Apple platforms only)

## Code Style

- Uses SwiftFormat with 2-space indentation, Allman brace style
- Swift 5.10 with C17/C++17 language standards
- Targets macOS 14+, iOS 17+, visionOS 1.0+

## Common C++ Settings

All targets that need Windows compatibility use these cxxSettings (matching SwiftUSD's pattern):

```swift
cxxSettings: [
  .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
  .define("_ALLOW_KEYWORD_MACROS", to: "1", .when(platforms: [.windows])),
  .define("static_assert(_conditional, ...)", to: "", .when(platforms: [.windows])),
]
```
