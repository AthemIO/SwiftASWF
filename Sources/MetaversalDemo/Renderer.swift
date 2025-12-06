#if os(visionOS) || !canImport(AppKit) && !canImport(UIKit)

  public final class Renderer
  {
    public init?()
    {}

    public func draw()
    {}
  }

#elseif canImport(Metal)
  import Metal
  import MetalKit

  public final class Renderer: NSObject, MTKViewDelegate
  {
    private let queue: MTLCommandQueue

    public init?(device: MTLDevice)
    {
      guard let queue = device.makeCommandQueue() else { return nil }
      self.queue = queue
    }

    public func mtkView(_: MTKView, drawableSizeWillChange size: CGSize)
    {
      print("drawableSizeWillChange", size)
    }

    public func draw(in view: MTKView)
    {
      guard
        let renderPassDescriptor = view.currentRenderPassDescriptor,
        let commandBuffer = queue.makeCommandBuffer(),
        let commandEncoder = commandBuffer.makeRenderCommandEncoder(descriptor: renderPassDescriptor),
        let drawable = view.currentDrawable
      else { return }

      commandEncoder.endEncoding()

      commandBuffer.present(drawable)
      commandBuffer.commit()
    }
  }
#endif
