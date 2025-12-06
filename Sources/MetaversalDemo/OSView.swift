#if os(visionOS) || !canImport(AppKit) && !canImport(UIKit)
  open class OSView
  {
    public init()
    {}

    public func viewDidLoad()
    {}
  }

  public typealias ViewControllerAPI = OSView

  public final class ViewController: ViewControllerAPI
  {
    private var renderer: Renderer?

    override public func viewDidLoad()
    {}
  }

#elseif canImport(Metal)
  import Metal
  import MetalKit

  #if canImport(AppKit)
    public typealias ViewControllerAPI = NSViewController
  #elseif canImport(UIKit)
    public typealias ViewControllerAPI = UIViewController
  #endif

  public final class ViewController: ViewControllerAPI
  {
    private var renderer: Renderer?

    override public func viewDidLoad()
    {
      super.viewDidLoad()

      print("view did load")

      guard let metalKitView = view as? MTKView else { return }

      metalKitView.enableSetNeedsDisplay = true
      metalKitView.device = MTLCreateSystemDefaultDevice()
      metalKitView.clearColor = MTLClearColorMake(0.0, 0.5, 1.0, 1.0)

      renderer = metalKitView.device.flatMap(Renderer.init)
      metalKitView.delegate = renderer
    }
  }
#endif
