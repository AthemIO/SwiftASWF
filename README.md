# SwiftASWF

[![Swift 6.1](https://img.shields.io/badge/Swift-6.1-F05138?style=flat-square&logo=swift&logoColor=white)](https://swift.org)
[![Ubuntu](https://img.shields.io/github/actions/workflow/status/AthemIO/SwiftASWF/swift-ubuntu.yml?style=flat-square&label=ubuntu&labelColor=E95420&logoColor=FFFFFF&logo=ubuntu)](https://github.com/AthemIO/SwiftASWF/actions/workflows/swift-ubuntu.yml)
[![macOS](https://img.shields.io/github/actions/workflow/status/AthemIO/SwiftASWF/swift-macos.yml?style=flat-square&label=macOS&labelColor=000000&logo=apple)](https://github.com/AthemIO/SwiftASWF/actions/workflows/swift-macos.yml)
[![Windows](https://img.shields.io/github/actions/workflow/status/AthemIO/SwiftASWF/swift-debug-windows.yml?style=flat-square&label=windows&labelColor=357EC7&logo=gitforwindows)](https://github.com/AthemIO/SwiftASWF/actions/workflows/swift-debug-windows.yml)

Swift package providing [Academy Software Foundation (ASWF)](https://landscape.aswf.io) libraries for 3D applications. This package serves as the primary dependency for [SwiftUSD](https://github.com/AthemIO/SwiftUSD).

## Installation

Add SwiftASWF as a dependency in your `Package.swift`:

```swift
dependencies: [
  .package(url: "https://github.com/AthemIO/SwiftASWF.git", from: "1.8.5"),
]
```

## Building from Source

### Prerequisites

**macOS:**
- Xcode 16+ with Command Line Tools
- Swift 6.1+

**Linux (Ubuntu/Debian):**
```bash
sudo apt-get install -y \
  libbz2-dev libx11-dev libgl1-mesa-dev libglu1-mesa-dev \
  libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
```

**Windows:**
- Visual Studio 2022 with C++ workload
- Swift 6.1+ toolchain

### Build Commands

```bash
# Clone the repository
git clone https://github.com/AthemIO/SwiftASWF.git
cd SwiftASWF

# Initialize submodules (required)
git submodule update --init --recursive

# Build release (recommended - debug builds are slow)
swift build -c release

# Build specific target
swift build -c release --target OpenEXR

# Run tests
swift test

# Run demo app (requires Swift Bundler)
swift bundler run -p macOS SwiftASWFDemo
```

## Swift Targets

### Core

| Target | Version | Upstream |
|--------|---------|----------|
| OpenEXR | 3.2.1 | [AcademySoftwareFoundation/openexr](https://github.com/AcademySoftwareFoundation/openexr) |
| Imath | 3.1.12 | [AcademySoftwareFoundation/Imath](https://github.com/AcademySoftwareFoundation/Imath) |
| Eigen | 3.4.0 | [eigen/eigen](https://gitlab.com/libeigen/eigen) |
| OneTBB | 2021.12.0 | [oneapi-src/oneTBB](https://github.com/oneapi-src/oneTBB) |

### Imaging

| Target | Version | Upstream |
|--------|---------|----------|
| OpenImageIO | 2.7.0 | [AcademySoftwareFoundation/OpenImageIO](https://github.com/AcademySoftwareFoundation/OpenImageIO) |
| OpenColorIO | 2.4.2 | [AcademySoftwareFoundation/OpenColorIO](https://github.com/AcademySoftwareFoundation/OpenColorIO) |
| TurboJPEG | 3.0.1 | [libjpeg-turbo/libjpeg-turbo](https://github.com/libjpeg-turbo/libjpeg-turbo) |
| TIFF | 4.6.0 | [libsdl-org/libtiff](https://github.com/libsdl-org/libtiff) |
| LibPNG | 1.6.40 | [pnggroup/libpng](https://github.com/pnggroup/libpng) |
| WebP | 1.3.2 | [webmproject/libwebp](https://github.com/AthemIO/libwebp) |
| Raw | 0.21.1 | [LibRaw/LibRaw](https://github.com/LibRaw/LibRaw) |

### 3D & Graphics

| Target | Version | Upstream |
|--------|---------|----------|
| MaterialX | 1.39.3 | [AcademySoftwareFoundation/MaterialX](https://github.com/AcademySoftwareFoundation/MaterialX) |
| OpenSubdiv | 3.6.1 | [PixarAnimationStudios/OpenSubdiv](https://github.com/PixarAnimationStudios/OpenSubdiv) |
| OpenVDB | 12.0.0 | [AcademySoftwareFoundation/openvdb](https://github.com/AcademySoftwareFoundation/openvdb) |
| Alembic | 1.8.5 | [alembic/alembic](https://github.com/alembic/alembic) |
| Ptex | 2.4.2 | [wdas/ptex](https://github.com/wdas/ptex) |
| Draco | 1.5.6 | [google/draco](https://github.com/google/draco) |

### Compression

| Target | Version | Upstream |
|--------|---------|----------|
| Blosc | 1.21.5 | [Blosc/c-blosc](https://github.com/Blosc/c-blosc) |
| ZStandard | 1.5.5 | [facebook/zstd](https://github.com/facebook/zstd) |
| LZMA2 | 5.4.4 | [tukaani-project/xz](https://github.com/tukaani-project/xz) |
| MiniZip | 4.0.1 | [zlib-ng/minizip-ng](https://github.com/zlib-ng/minizip-ng) |

### Utilities

| Target | Version | Upstream |
|--------|---------|----------|
| HDF5 | 1.10.0 | [HDFGroup/hdf5](https://github.com/HDFGroup/hdf5) |
| Yaml | 0.8.0 | [jbeder/yaml-cpp](https://github.com/jbeder/yaml-cpp) |
| ImGui | 1.89.9 | [ocornut/imgui](https://github.com/ocornut/imgui) |

## Platform Support

| Platform | Minimum Version | Status |
|----------|-----------------|--------|
| macOS | 14+ | ✓ Full support |
| iOS | 17+ | ✓ Full support |
| visionOS | 1.0+ | ✓ Full support |
| tvOS | 17+ | ✓ Full support |
| watchOS | 10+ | ✓ Full support |
| Linux | Ubuntu 22.04+ | ✓ Full support |
| Windows | Windows 10+ | ✓ Full support |

## Troubleshooting

### Build Errors

**"TBB header not found"**
```
fatal error: 'oneapi/tbb/detail/_utils.h' file not found
```
Ensure you're using SwiftASWF v1.8.5 or later, which includes fixed TBB header paths.

**"Module not found" on Linux**
```
error: no such module 'OpenEXR'
```
Install the required system dependencies (see Prerequisites above).

**Slow debug builds**

Debug builds compile significantly slower due to unoptimized C++ code. Use release builds for development:
```bash
swift build -c release
```

### Runtime Issues

**OCIO config not found**

The OCIOBundle target requires the OCIO environment variable to be set. Use `OCIOBundler.shared` to automatically configure the bundled ACES or AgX color configs.

## Related Projects

- [SwiftUSD](https://github.com/AthemIO/SwiftUSD) - Swift bindings for Pixar's Universal Scene Description
- [ASWF Landscape](https://landscape.aswf.io) - Academy Software Foundation project ecosystem

## License

Licensed under the Apache License 2.0. See [LICENSE](LICENSE) for details.

Individual bundled libraries retain their original licenses (Apache 2.0, BSD 3-Clause, MIT, etc.). See the LICENSE file for complete attribution.
