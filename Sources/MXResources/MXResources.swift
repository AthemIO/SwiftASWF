/* ----------------------------------------------------------------
 * S W I F T A S W F
 * ----------------------------------------------------------------
 * Copyright (C) 2025 Afloat Technologies. All Rights Reserved.
 * Licensed under https://www.apache.org/licenses/LICENSE-2.0
 * ---------------------------------------------------------------- */

#if canImport(Metal)
  import Metal
#endif /* canImport(Metal) */

/**
 * # MaterialX Resource Manager
 *
 * The ``MXResourceManager`` is a singleton class that manages all
 * the **resources** and **standard data libraries** for **MaterialX**,
 * providing **declarations** and **graph definitions** for each of the
 * **MaterialX** nodes, and **source code** for all the supported **shader
 * generators**.
 *
 * This singleton is designed for clients to use the ``shared`` instance
 * of this class within their own apps and plugins, usage is as follows:
 * ````
 * let mxResourceManager = MXResourceManager.shared
 * mxResourceManager.loadStandardLibraries()
 * ````
 *
 * - **Notice**: This singleton class is not yet implemented, it currently
 * serves as a stub for the ``MaterialX`` target, which through **SwiftPM**,
 * automatically includes all of these resources since it's a transitive
 * dependency of the ``SwiftUSD` target, when clients add the ``SwiftUSD``
 * package to their own apps & plugins, or other projects, they will also
 * automatically have all of these resources installed to the app's bundle
 * or library module's respective ``Resources`` folder for direct consumption.
 *
 * The **standard data libraries** that are bundled are the sames ones from the
 * [**MaterialX Standard Library**](https://github.com/AcademySoftwareFoundation/MaterialX/tree/main/libraries).
 *
 *
 * Additionally, we have included the
 * [**MaterialX Resources**](https://github.com/AcademySoftwareFoundation/MaterialX/tree/main/resources)
 * as well. */
public final class MXResourceManager: Sendable
{
  public static let shared = MXResourceManager()

  private init()
  {}
}
