/* ----------------------------------------------------------------
 * S W I F T A S W F
 * ----------------------------------------------------------------
 * Copyright (C) 2025 Afloat Technologies. All Rights Reserved.
 * Licensed under https://www.apache.org/licenses/LICENSE-2.0
 * ---------------------------------------------------------------- */

import Draco
import ImGui
import Imath
import MaterialX
import OCIOBundle
import OpenColorIO
import OpenEXR
import OpenImageIO
import OpenSubdiv
import OpenTime
import OpenTimelineIO
import OpenVDB
import Ptex

#if canImport(Python) && (os(macOS) || os(visionOS) || os(iOS) || os(tvOS) || os(watchOS))
    import PyBundle
    import Python
#endif  // canImport(Python) && os(macOS)

public typealias OCIO = OpenColorIO_v2_4
public typealias OIIO = OpenImageIO_v2_5

#if canImport(AppKit) || canImport(UIKit)
    import Metal
    import MetalKit

    #if canImport(AppKit)
        public typealias OSWindow = NSWindow
        public typealias OSDelegate = NSApplicationDelegate & NSResponder
        public typealias OSApp = NSApplication
    #elseif canImport(UIKit)
        public typealias OSWindow = UIWindow
        public typealias OSDelegate = UIApplicationDelegate & UIResponder
        public typealias OSApp = UIApplication
    #endif /* canImport(UIKit) */
#else  // !canImport(AppKit) || !canImport(UIKit)
    public class OSApp {
        public static let shared = OSApp()

        private init() {
            print("OSApp is not supported on this platform.")
        }

        public var delegate = AppDelegate()

        public func run() {
            print("OSApp is not supported on this platform.")
        }
    }

    public struct OSWindow {}

    public struct OSDelegate {}
#endif

@main
class Creator {
    let app = OSApp.shared
    let delegate = AppDelegate()

    init() {
        app.delegate = delegate
    }

    static func main() {
        let C: Creator

        #if canImport(Python) && (os(macOS) || os(visionOS) || os(iOS) || os(tvOS) || os(watchOS))
            /* embed & init python. */
            PyBundler.shared.pyInit()
            PyBundler.shared.pyInfo()
        #endif  // canImport(Python)
        print("app launched.")

        C = Creator()

        #if canImport(AppKit)
            C.app.run()
        #endif /* canImport(AppKit) */
    }

    static func setupGuiStyle(with context: UnsafeMutablePointer<ImGuiContext>? = nil) {
        assert(context != nil, "ImGui context is nil")

        let io = ImGui.GetIO()
        io.pointee.IniFilename = nil
        io.pointee.LogFilename = nil
        io.pointee.Fonts.pointee.Build()

        ImGui.StyleColorsDark(nil)
    }

    /* -------------------------------------------------------- */

    static func configColor() {
        OCIOBundler.shared.ocioInit(config: .aces)

        OCIO.GetCurrentConfig()
    }

    static func configImaging() {
        /* create some exr images. */
        let dtp = OIIO.TypeDesc(.init("float"))
        let fmt = OIIO.ImageSpec(512, 89, 4, dtp)

        var fg = OIIO.ImageBuf(.init(std.string("fg.exr")), fmt, OIIO.InitializePixels.Yes)
        let bg = OIIO.ImageBuf(.init(std.string("bg.exr")), fmt, OIIO.InitializePixels.Yes)

        fg.set_origin(0, 0, 0)

        if OIIO.ImageBufAlgo.fill(
            &fg, .init(Float(0.01)), .init(Float(0.01)), .init(Float(1.0)), .init(Float(0.01)),
            .init(), 0)
        {
            let comp = OIIO.ImageBufAlgo.over(fg, bg, .init(), 0)
            if !comp.has_error() {
                if comp.write(
                    .init(std.string("composite.exr")), OIIO.TypeDesc(.init("UNKNOWN")), .init(""),
                    nil, nil) == false || comp.has_error()
                {
                    print("Error writing image: \(comp.geterror(true))")
                }
            } else {
                print("Error writing image: \(comp.geterror(true))")
            }
        } else {
            print("Error filling fg image.")
        }
    }

    /* -------------------------------------------------------- */
}

#if canImport(AppKit)
    public class AppDelegate: OSDelegate {
        let app = OSApp.shared
        let viewController = ViewController()
        let ctx = ImGui.CreateContext(nil)

        public var window: OSWindow?

        public func applicationDidFinishLaunching(_: Notification) {
            print("SwiftASWFDemo has launched.")

            Creator.configColor()
            Creator.configImaging()
            Creator.setupGuiStyle(with: ctx)

            let window = NSWindow(
                contentRect: NSRect(x: 0, y: 0, width: 1280, height: 720),
                styleMask: [.titled, .closable, .miniaturizable, .resizable, .fullSizeContentView],
                backing: .buffered,
                defer: false
            )
            window.title = "SwiftASWF"
            window.contentViewController = viewController
            window.makeKeyAndOrderFront(nil)

            self.window = window
        }

        public func applicationWillTerminate(_: Notification) {
            ImGui.DestroyContext(ctx)
        }

        public func applicationShouldTerminateAfterLastWindowClosed(_: OSApp) -> Bool {
            false
        }
    }

#elseif canImport(UIKit)
    public class AppDelegate: OSDelegate {
        let app = OSApp.shared
        let viewController = ViewController()
        let ctx = ImGui.CreateContext(nil)

        public var window: OSWindow?

        public func application(
            _: OSApp, didFinishLaunchingWithOptions _: [UIApplication.LaunchOptionsKey: Any]?
        ) -> Bool {
            Creator.configColor()
            Creator.configImaging()
            Creator.setupGuiStyle(with: ctx)

            let window = UIWindow()
            window.makeKeyAndVisible()

            self.window = window

            return true
        }

        public func applicationWillTerminate(_: OSApp) {
            ImGui.DestroyContext(ctx)
        }
    }
#else /* !canImport(AppKit) && !canImport(UIKit) */
    public class AppDelegate {
        let app = OSApp.shared
        let ctx = ImGui.CreateContext(nil)

        public var window: OSWindow?

        public func application(_: OSApp, didFinishLaunchingWithOptions _: [String: Any]?) -> Bool {
            Creator.configColor()
            Creator.configImaging()
            Creator.setupGuiStyle(with: ctx)

            window = .init()

            print("app launched succesfully.")

            return true
        }

        public func applicationWillTerminate(_: OSApp) {
            ImGui.DestroyContext(ctx)
        }
    }
#endif /* !canImport(AppKit) && !canImport(UIKit) */
