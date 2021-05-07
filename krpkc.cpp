
#include "../pch.h"


template<>
ScaleFactor Endgame<KRPKC>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongPawn = pos.square<PAWN>(strongSide);
  Square strongRook = pos.square<ROOK>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);
  Square weakCannon = pos.square<CANNON>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  if (weakAdvisors == 2 && weakBishops == 2)
  {
    sf = ScaleFactor(16);

    // fen 2b1k4/4a4/9/9/9/9/3p5/B2A5/4A4/2B1KC1r1 w - - 0 0
    if (PC_ON_ST(SQ_E9) == MK_PC_WK(KING) && RR_WK(strongPawn) <= RANK_3)
    {
      if (PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR) && PC_ON_ST(SQ_F9) == MK_PC_WK(CANNON))
        return ScaleFactor(8);
      if (PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR) && PC_ON_ST(SQ_D9) == MK_PC_WK(CANNON))
        return ScaleFactor(8);
    }

    if (PC_ON_ST(SQ_E7) == MK_PC_WK(BISHOP))
      if (RR_WK(weakKing) == RANK_0)
        if (RR_WK(weakCannon) == RANK_0)
          return ScaleFactor(8);

    // fen 3ak1b2/3Pa4/4c3b/9/5R3/6B2/9/B2AK4/9/5A3 b - - 0 1
    if (PC_ON_ST(SQ_D9) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) < FILE_E)
      return ScaleFactor(8);
    if (PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) > FILE_E)
      return ScaleFactor(8);

    // fen 5k3/9/9/9/2b1C1p2/2B6/1r7/3AB4/3KA4/9 r
    if (RR_WK(weakKing) >= RANK_1)
      if (PC_ON_ST(SQ_C4) == MK_PC_ST(PAWN) || PC_ON_ST(SQ_G4) == MK_PC_ST(PAWN) || PC_ON_ST(SQ_A4) == MK_PC_ST(PAWN) || PC_ON_ST(SQ_I4) == MK_PC_ST(PAWN))
        return ScaleFactor(8);

    // fen 2b1ka3/4a4/b8/1R2P4/9/2B6/9/2cAB4/9/3A1K3 b - - 156
    if (PC_ON_ST(SQ_E9) == MK_PC_WK(KING) && RR_WK(strongPawn) < RANK_2)
      return ScaleFactor(8);
  }

  if (weakAdvisors >= 1 && weakBishops == 2)
  {
    sf = ScaleFactor(16);

    if (RR_WK(weakKing) == RANK_0)
    {
      // fen 3k1P3/4a4/3cb4/9/3R2b2/6B2/9/8B/9/3AKA3 b - - 0 0
      if (PC_ON_ST(SQ_E8) == MK_PC_WK(ADVISOR))
      {
        if (PC_ON_ST(SQ_F9) == MK_PC_ST(PAWN) && PC_ON_ST(SQ_D7) == MK_PC_WK(CANNON))
          return ScaleFactor(8);
        if (PC_ON_ST(SQ_D9) == MK_PC_ST(PAWN) && PC_ON_ST(SQ_F7) == MK_PC_WK(CANNON))
          return ScaleFactor(8);
      }

      // fen 1P2kc3/9/3ab4/9/2b6/9/1R7/4B4/4A4/2B1K4 b
      if (RR_WK(weakCannon) == RANK_0 && RR_WK(strongPawn) == RANK_0)
      {
        if (RF_XX(strongPawn) <= FILE_B && RF_XX(weakCannon) >= FILE_F)
          return ScaleFactor(8);
        if (RF_XX(strongPawn) >= FILE_H && RF_XX(weakCannon) <= FILE_D)
          return ScaleFactor(8);
        return ScaleFactor(16);
      }
    }
  }

  // fen 1R1ak4/4a4/4b4/p1p5p/9/2Pn5/P3c3P/3K5/4A4/5A3 w - - 0 1
  if (weakAdvisors == 2 && weakBishops >= 1)
  {
    sf = ScaleFactor(16);

    if (PC_ON_ST(SQ_E9) == MK_PC_WK(KING) && RR_WK(strongPawn) >= RANK_1)
    {
      if (PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) > FILE_E)
        if (!(PP_BB_WK(BISHOP) & RightBB))
          return ScaleFactor(16);
      if (PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) > FILE_E)
        if (!(PP_BB_WK(BISHOP) & LeftBB))
          return ScaleFactor(16);
    }
  }

  // fen 2b1k1b2/4a4/3a1c3/3P5/4R4/9/9/3A1A3/3K5/2B3B2 b - - 0 1
  if (weakAdvisors == 2 && weakBishops == 2)
    if (RR_WK(weakKing) == RANK_0 && RR_WK(weakCannon) >= RANK_2)
      if (RR_WK(strongPawn) <= RANK_3 && RF_XX(weakCannon) != FILE_E)
        return ScaleFactor(16);

  // fen 4ka3/4a4/2P1bc3/8R/2b6/9/9/3K5/4A4/2B6 w - - 0 1
  if (weakAdvisors == 2 && weakBishops == 2)
    if (PC_ON_ST(SQ_E9) == MK_PC_WK(KING) && RR_WK(weakCannon) >= RANK_2)
      if (!EQ_FLK_WK(strongPawn, weakCannon) && abs(RF_XX(strongPawn) - FILE_E) >= 2)
        return ScaleFactor(16);

  // fen 1R5P1/3ka4/5a2b/9/c8/9/9/5A3/9/4K4 w - - 0 1
  if (weakAdvisors == 2 && weakBishops >= 1)
    if (RR_WK(weakKing) >= RANK_1 && RR_WK(strongPawn) == RANK_0)
    {
      if (PC_ON_ST(SQ_I7) == MK_PC_WK(BISHOP) && PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR))
        if (RF_XX(weakCannon) <= FILE_D && RF_XX(strongPawn) >= FILE_H)
          return ScaleFactor(16);
      if (PC_ON_ST(SQ_A7) == MK_PC_WK(BISHOP) && PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR))
        if (RF_XX(weakCannon) >= FILE_F && RF_XX(strongPawn) <= FILE_B)
          return ScaleFactor(16);
    }

  // fen 4ka3/4a4/2P1bc3/8R/2b6/9/9/3K5/4A4/2B6 w - - 0 1
  if (weakAdvisors == 2 && weakBishops == 2)
    if (PC_ON_ST(SQ_E9) == MK_PC_WK(KING))
      return ScaleFactor(32);

  return sf;
}
