
#include "../pch.h"


template<>
ScaleFactor Endgame<KNPKC>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongPawn = pos.square<PAWN>(strongSide);
  Square strongKnight = pos.square<KNIGHT>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);
  Square weakCannon = pos.square<CANNON>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  Bitboard b = PP_BB_ST(PAWN), bb = NoSquares;
  CheckInfo *ci = pos.check();
  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  // fen 2b1k4/4aP3/3a5/9/2bN5/9/3p5/B8/9/3AKA3 b - - 0 1
  if (weakAdvisors == 2 && weakBishops == 2)
    sf = ScaleFactor(8);
  else if (weakAdvisors + weakBishops >= 2)
    sf = ScaleFactor(16);

  // fen 5c3/N8/4k1P1b/9/9/9/9/5K3/9/9 b - - 0 1
  if (weakBishops >= 1)
    if (RR_WK(weakKing) != RANK_0 && RR_WK(strongPawn) >= RANK_2)
    {
      sf -= ScaleFactor(2);
      if (RF_XX(weakKing) == FILE_E)
      {
        sf -= ScaleFactor(2);
        if (RR_WK(weakCannon) >= RANK_2)
          sf -= ScaleFactor(2);
      }
    }

  if (weakAdvisors == 0)
  {
    if (RR_WK(weakKing) > RR_WK(strongPawn))
      return ScaleFactor(8);

    if (weakBishops == 2)
      return ScaleFactor(8);
    else if (RR_WK(strongPawn) > RR_WK(weakKing))
      sf += ScaleFactor(weakAdvisors);
  }

  if (RR_WK(weakKing) < RR_WK(strongPawn))
    return ScaleFactor(8);

  // fen 2c6/4ak3/9/5P3/2b6/5N3/9/9/9/4K4 w
  if (abs((strongAdvisors + strongBishops) - (weakAdvisors + weakBishops)) <= 1)
    if (equal_z(ci->pinned) && equal_z(ci->dcCandidates))
      return ScaleFactor(8);

  // fen 3P1k3/9/5c1N1/9/9/2B6/9/3A5/4A4/5KB2 w - - 0 1
  if (RR_WK(strongPawn) == RANK_0)
  {
    if (RR_WK(weakKing) != RANK_0)
      return ScaleFactor(8);
    if (PC_ON_ST(SQ_D7) == MK_PC_ST(KNIGHT) && PC_ON_ST(SQ_F9) == MK_PC_WK(KING))
      ;
    else if (PC_ON_ST(SQ_F7) == MK_PC_ST(KNIGHT) && PC_ON_ST(SQ_D9) == MK_PC_WK(KING))
      ;
    else
      return ScaleFactor(8);
  }

  // fen 9/3P5/3ak4/5cN2/9/9/9/B2A4B/5K3/3A5 b
  if (weakAdvisors >= 1)
    if (RR_WK(strongPawn) < RR_WK(weakKing))
    {
      if (PC_ON_ST(SQ_D7) == MK_PC_ST(ADVISOR) && RF_XX(weakCannon) == FILE_F)
        return ScaleFactor(16);
      if (PC_ON_ST(SQ_F7) == MK_PC_ST(ADVISOR) && RF_XX(weakCannon) == FILE_D)
        return ScaleFactor(16);
    }

  if (RR_WK(strongPawn) == RANK_0)
    return ScaleFactor(16);

  // fen 3k5/5P3/1N2b4/9/9/2B6/4c4/9/5K3/9 b - - 0 1
  if (weakBishops >= 1)
    if (RR_WK(weakCannon) <= RANK_3 && RF_XX(weakCannon) == FILE_E)
      if (RR_WK(strongPawn) >= RANK_1 && !EQ_FLK_WK(strongPawn, weakKing))
        if (RF_XX(strongPawn) != FILE_E)
          return ScaleFactor(16);

  //fen 9/6P2/4ka3/3N5/9/9/9/5c3/9/5K3 w - - 0 1
  if (weakBishops >= 1)
    if (RR_WK(strongPawn) < RR_WK(weakKing))
    {
      if (RR_WK(weakCannon) < RANK_2 && RR_WK(weakCannon) < RR_WK(strongKing))
        return ScaleFactor(16);
      return ScaleFactor(32);
    }

  // fen 5a3/3ka4/9/9/2b3b2/9/9/9/2nC1p3/3K1A3 w - - 0 1
  if (weakAdvisors >= 1)
    if (RR_WK(strongPawn) >= RANK_1)
    {
      if (RF_XX(strongPawn) < FILE_E && RF_XX(strongKnight) > FILE_E && PC_ON_ST(SQ_D9) == MK_PC_WK(ADVISOR))
        return ScaleFactor(32);
      if (RF_XX(strongPawn) > FILE_E && RF_XX(strongKnight) < FILE_E && PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR))
        return ScaleFactor(32);
    }

  // fen 5c3/N8/4k1P1b/9/9/9/9/5K3/9/9 b - - 0 1
  if (weakBishops >= 1)
    if (RR_WK(strongPawn) >= RANK_2 && RR_WK(weakKing) != RANK_0)
      if (RR_WK(weakCannon) >= RANK_2 && RF_XX(weakKing) == FILE_E)
        if (strongAdvisors == 0 && strongBishops == 0)
        {
          if (RF_XX(weakCannon) == FILE_D && RF_XX(strongKing) == FILE_D && RF_XX(strongPawn) <= FILE_C)
            return ScaleFactor(32);
          if (RF_XX(weakCannon) == FILE_F && RF_XX(strongKing) == FILE_F && RF_XX(strongPawn) >= FILE_G)
            return ScaleFactor(32);
        }

  // fen 2b6/4k4/3P1cN2/9/9/2B6/9/9/5K3/6B2 w - - 0 1
  if (weakBishops >= 1)
    if (RR_WK(strongPawn) <= RANK_2)
      return ScaleFactor(48);

  return sf;
}
