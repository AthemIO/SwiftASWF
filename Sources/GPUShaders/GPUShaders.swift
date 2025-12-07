/* ----------------------------------------------------------------
 * S W I F T A S W F
 * ----------------------------------------------------------------
 * Copyright (C) 2025 Afloat Technologies. All Rights Reserved.
 * Licensed under https://www.apache.org/licenses/LICENSE-2.0
 * ---------------------------------------------------------------- */

#if canImport(Metal)
  import Metal
#endif /* canImport(Metal) */

public class GPUShaders
{
  public init()
  {
    #if canImport(Metal)
      device = MTLCreateSystemDefaultDevice()
      metalLib = try? device.makeDefaultLibrary(bundle: Bundle.module)
    #endif /* canImport(Metal) */
  }

  #if canImport(Metal)
    /**  A metal device for access to the GPU. */
    public var device: MTLDevice!

    /**  A metal library. */
    public var metalLib: MTLLibrary!
  #endif /* canImport(Metal) */
}
