
#include "../pch.h"


template<>
ScaleFactor Endgame<KRNKR>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongKnight = pos.square<KNIGHT>(strongSide);
  Square strongRook = pos.square<ROOK>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);
  Square weakRook = pos.square<ROOK>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  CheckInfo *ci = pos.check();

  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  if (weakAdvisors + weakBishops == 4)
  {
    if (strongAdvisors + strongBishops >= 2)
      sf = ScaleFactor(8);
    else
      sf = ScaleFactor(16);
  }
  else if (weakAdvisors + weakBishops == 3)
  {
    if (strongAdvisors + strongBishops <= 0)
      sf = ScaleFactor(8);
    else if (strongAdvisors + strongBishops <= 4)
      sf = ScaleFactor(16);
  }
  else if (weakAdvisors == 0 && weakBishops == 2)
  {
    sf = ScaleFactor(16);
  }

  // fen 3k5/4a4/4b3b/9/9/6B2/9/3nR4/1r1K5/9 w - - 0 0
  if (RR_WK(strongKnight) == RANK_2 && RR_WK(weakRook) == RR_WK(strongKnight))
    return ScaleFactor(8);

  // fen 3a1k3/4a4/4br3/5N3/9/5R3/9/4B4/9/5K3 w - - 78 78
  if (weakAdvisors + weakBishops >= 2)
    if (popcount(between_bb(weakRook, strongRook) & pos.pieces()) == 1)
      if (and_true(between_bb(weakRook, strongRook), square_bb(strongKnight)))
        return ScaleFactor(8);

  if (weakAdvisors + weakBishops >= 2)
    if (strongAdvisors + strongBishops >= 2)
      return ScaleFactor(8);

  // fen 4ka3/9/9/7r1/9/9/1R7/3A5/3nA4/5K3 w
  if (weakAdvisors == 2 && PC_ON_WK(SQ_E1) == MK_PC_WK(ADVISOR))
    if (RR_WK(strongKnight) <= RANK_2 && !EQ_FLK_WK(strongKnight, weakKing))
    {
      if (RS_WK(SQ_D2) == MK_PC_WK(ADVISOR))
        if (RF_XX(strongKnight) < FILE_E && RF_XX(weakRook) == FILE_B)
          return ScaleFactor(8);
      if (RS_WK(SQ_F2) == MK_PC_WK(ADVISOR))
        if (RF_XX(strongKnight) > FILE_E && RF_XX(weakRook) == FILE_H)
          return ScaleFactor(8);
    }

  // fen 3k5/2RNa4/3a5/1r7/9/9/9/3AK4/4A4/9 w - - 39 39
  if (weakAdvisors == 2 && RR_WK(strongRook) == RANK_1)
  {
    if (PC_ON_WK(SQ_D0) == MK_PC_WK(KING) && PC_ON_WK(SQ_D1) == MK_PC_WK(KNIGHT)
      && PC_ON_WK(SQ_D2) == MK_PC_WK(ADVISOR) && RF_XX(weakRook))
      return ScaleFactor(8);
    if (PC_ON_WK(SQ_F0) == MK_PC_WK(KING) && PC_ON_WK(SQ_F1) == MK_PC_WK(KNIGHT)
      && PC_ON_WK(SQ_F2) == MK_PC_WK(ADVISOR) && RF_XX(weakRook))
      return ScaleFactor(8);
  }

  // fen 3k1a2R/4a2rN/9/9/9/9/9/4BA2B/4A4/4K4 r
  if (weakAdvisors == 2 && abs(RF_XX(strongKnight)
    - FILE_E) == 4 && RF_XX(strongRook) == RF_XX(strongKnight))
    if (RR_WK(strongKnight) == RANK_1 && RR_WK(strongRook) == RANK_0)
      return ScaleFactor(8);

  // fen 4ka3/4a4/b5r2/3R1N3/9/9/9/3KBA3/9/5AB2 b - - 0 1
  if (weakAdvisors == 2 && weakBishops >= 1)
    return ScaleFactor(8);

  if (and_true(ci->pinned, square_bb(strongKnight)))
    return SCALE_FACTOR_NORMAL;

  return sf;
}
