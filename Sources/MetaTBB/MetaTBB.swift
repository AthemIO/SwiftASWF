/* ----------------------------------------------------------------
 * S W I F T A S W F
 * ----------------------------------------------------------------
 * Copyright (C) 2025 Afloat Technologies. All Rights Reserved.
 * Licensed under https://www.apache.org/licenses/LICENSE-2.0
 * ---------------------------------------------------------------- */

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
