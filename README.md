# SwiftASWF

[![Ubuntu](https://img.shields.io/github/actions/workflow/status/AthemIO/SwiftASWF/swift-ubuntu.yml?style=flat-square&label=ubuntu&labelColor=E95420&logoColor=FFFFFF&logo=ubuntu)](https://github.com/AthemIO/SwiftASWF/actions/workflows/swift-ubuntu.yml)
[![macOS](https://img.shields.io/github/actions/workflow/status/AthemIO/SwiftASWF/swift-macos.yml?style=flat-square&label=macOS&labelColor=000000&logo=apple)](https://github.com/AthemIO/SwiftASWF/actions/workflows/swift-macos.yml)
[![Windows](https://img.shields.io/github/actions/workflow/status/AthemIO/SwiftASWF/swift-debug-windows.yml?style=flat-square&label=windows&labelColor=357EC7&logo=gitforwindows)](https://github.com/AthemIO/SwiftASWF/actions/workflows/swift-debug-windows.yml)

Swift package providing [Academy Software Foundation (ASWF)](https://landscape.aswf.io) libraries for VFX and graphics applications. This package serves as the primary dependency for [SwiftUSD](https://github.com/AthemIO/SwiftUSD).

## Installation

Add SwiftASWF as a dependency in your `Package.swift`:

```swift
dependencies: [
  .package(url: "https://github.com/AthemIO/SwiftASWF.git", from: "1.8.5"),
]
```

## Swift Targets

### Core

| Target | Version |
|--------|---------|
| OpenEXR | 3.2.1 |
| Imath | 3.1.9 |
| Eigen | 3.4.0 |
| OneTBB | 2021.10.0 |

### Imaging

| Target | Version |
|--------|---------|
| OpenImageIO | master |
| OpenColorIO | 2.3.0 |
| TurboJPEG | 3.0.1 |
| TIFF | 4.6.0 |
| LibPNG | 1.6.40 |
| WebP | 1.3.2 |
| Raw | 0.21.1 |

### 3D & Graphics

| Target | Version |
|--------|---------|
| MaterialX | 1.39.3 |
| OpenSubdiv | 3.6.1 |
| OpenVDB | 10.1.0 |
| Alembic | 1.8.5 |
| Ptex | 2.4.2 |
| Draco | 1.5.6 |

### Compression

| Target | Version |
|--------|---------|
| Blosc | 1.21.5 |
| ZStandard | 1.5.5 |
| LZMA2 | 5.4.4 |
| MiniZip | 4.0.1 |

### Utilities

| Target | Version |
|--------|---------|
| HDF5 | 1.10.0 |
| Yaml | 0.8.0 |
| ImGui | 1.89.9 |

## Platform Support

- **macOS** 14+, **iOS** 17+, **visionOS** 1.0+
- **Linux** (Ubuntu, CentOS)
- **Windows**

## License

Licensed under the Apache License 2.0. See individual library directories for their respective licenses.
