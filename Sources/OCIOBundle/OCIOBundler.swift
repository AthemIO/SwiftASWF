import Foundation
import OpenColorIO
#if os(Linux)
  import Glibc
#elseif os(macOS) || os(visionOS) || os(iOS) || os(tvOS) || os(watchOS)
  import Darwin.C
#endif

public final class OCIOBundler: @unchecked Sendable
{
  public static let shared = OCIOBundler()

  private init()
  {
    ocioInit()
  }

  public var config: OpenColorIO_v2_3.ConstConfigRcPtr?

  public func ocioInit(config ocio: OCIOConfigProfileType = .aces)
  {
    guard let ocioConfig = ocio.config
    else { return print("Could not find OCIO config.") }

    #if os(macOS)
      /* setup ocio color config. */
      setenv("OCIO", ocioConfig, 1)
    #endif /* macOS */

    config = OpenColorIO_v2_3.GetCurrentConfig()
  }

  public func ocioInfo()
  {
    guard let ocioConfig = config
    else { return }

    print(ocioConfig)
  }
}

public enum OCIOConfigProfileType
{
  case aces
  case agx

  public var config: String?
  {
    switch self
    {
      case .aces: Bundle.module.path(forResource: "colormanagement/ACES/studio-config-v2.1.0_aces-v1.3_ocio-v2.3.ocio", ofType: nil)
      case .agx: Bundle.module.path(forResource: "colormanagement/AgX/config.ocio", ofType: nil)
    }
  }
}
