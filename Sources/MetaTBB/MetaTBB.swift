// import OneTBB

/**
 * # Metaversal Threading Building Blocks.
 *
 * Root of **OneTBB** (threading building blocks)
 * dependency. */
public final class MetaTBB: Sendable
{
  public static let shared = MetaTBB()

  private init()
  {}
}
