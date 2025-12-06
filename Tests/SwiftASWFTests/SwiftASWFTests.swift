import XCTest
@testable import Draco
@testable import Imath
@testable import ImGui
@testable import MaterialX
@testable import OCIOBundle
@testable import OpenColorIO
@testable import OpenEXR
@testable import OpenImageIO
@testable import OpenSubdiv
@testable import OpenTime
@testable import OpenTimelineIO
@testable import OpenVDB
@testable import Ptex
#if canImport(Python) && (os(macOS) || os(visionOS) || os(iOS) || os(tvOS) || os(watchOS))
  @testable import PyBundle
  @testable import Python
#endif // canImport(Python) && os(macOS)

class SwiftASWFTests: XCTestCase
{
  func testSwiftASWF() throws
  {
    print("it works!")
  }
}
