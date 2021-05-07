
#include "../pch.h"


template<>
ScaleFactor Endgame<KRCKR>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongCannon = pos.square<CANNON>(strongSide);
  Square strongRook = pos.square<ROOK>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);
  Square weakRook = pos.square<ROOK>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  // fen 4k1b2/4a4/9/5P1R1/2r6/9/9/4B4/4A4/4KAB2 b - - 0 1
  if (weakAdvisors + weakBishops == 4)
    return ScaleFactor(8);

  if (weakAdvisors == 0 && weakBishops == 0)
    if (strongAdvisors + strongBishops >= 1)
      return ScaleFactor(8);
    else if (RF_XX(weakRook) == FILE_E && RR_WK(weakKing) != RANK_2)
      return ScaleFactor(8);

  // fen 5kb2/4a4/9/9/9/2B6/9/9/4KC1R1/5r3 w - - 35 35 
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (strongAdvisors == 0)
      return ScaleFactor(8);

  // fen 4kaRC1/4a4/9/7r1/9/6B2/9/8B/9/4K4 b
  if (weakAdvisors == 2)
    if (RR_WK(strongCannon) == RR_WK(strongRook)
      && RF_XX(weakRook) == RF_XX(strongCannon))
      return ScaleFactor(8);

  // fen 4k4/9/3ab4/9/2b6/9/1R1C4r/4B4/4A4/2B1K4 w
  if (popcount(between_bb(strongRook, weakRook) & pos.pieces()) == 1)
    if (and_true(between_bb(strongRook, weakRook), square_bb(strongCannon)))
      return ScaleFactor(8);

  // fen 4k4/6C2/4b4/9/2b6/9/9/3R4B/1r2K4/9 w - - 7 7
  if (weakBishops == 2 && strongAdvisors == 0)
    return ScaleFactor(8);

  // fen 5ab2/4a4/4k4/9/9/4R4/r3c4/4B4/4A4/3AK4 b - - 57 57
  if (weakAdvisors == 2 && weakBishops == 2)
    if (RR_ST(strongCannon) >= RANK_4)
      if (RR_WK(strongRook) == RR_WK(strongCannon) && RF_XX(weakRook) == RF_XX(strongCannon))
        return ScaleFactor(8);

  if (weakAdvisors == 2 && strongAdvisors == 0)
    return ScaleFactor(8);

  // fen 9/4ak3/1r1a4b/C8/9/9/9/5AR2/5K3/9 b - - 0 1
  if (strongAdvisors <= 1 && strongBishops == 0)
    if (weakAdvisors + weakBishops >= 3 && RR_WK(weakKing) >= RANK_1)
      if (RR_WK(strongCannon) >= RANK_7)
        return ScaleFactor(8);

  // fen 4k4/5R3/9/9/9/9/9/3KB4/3C5/3r2B2 b - - 0 1
  if (weakBishops == 2 && strongAdvisors == 0)
    return ScaleFactor(8);

  // fen 5ab2/4a4/4k4/9/9/4R4/r3c4/4B4/4A4/3AK4 b - - 57 57
  if (weakAdvisors == 2 && weakBishops >= 1)
    //if (RR_WK(strongRook) == RR_WK(strongCannon)
    //  && RF_XX(strongCannon) == RF_XX(weakRook))
    return ScaleFactor(8);

  if (weakAdvisors == 2 && strongAdvisors == 0)
    return ScaleFactor(8);

  // fen 9/4ak3/1r1a4b/C8/9/9/9/5AR2/5K3/9 b - - 0 1
  if (strongAdvisors <= 1 && strongBishops == 0)
    if (weakAdvisors + weakBishops >= 3)
      return ScaleFactor(8);

  // fen 3ak4/9/R3Ca3/4r4/9/2B6/9/4BA3/4A4/5K3 w - - 37 37
  if (weakAdvisors == 2)
    if (RR_WK(strongRook) == RR_WK(strongCannon)
      && RR_WK(weakRook) < RANK_2)
      return ScaleFactor(8);

  // fen 4k4/9/5a3/4r4/2b2C3/9/5R3/9/5K3/3A5 b - - 0 1
  if (weakAdvisors >= 1 && strongAdvisors <= 1 && strongBishops == 0)
    if (RR_WK(strongCannon) == RR_WK(weakRook)
      && RF_XX(strongRook) == RF_XX(strongCannon))
      return ScaleFactor(8);

  // fen 3ck4/4a4/9/9/6R2/4r4/9/3A5/4A4/5K3 w - - 26 26
  if (strongAdvisors <= 1 && strongBishops == 0)
    if (weakAdvisors == 2)
      return ScaleFactor(8);

  // fen 9/5k3/4br3/9/4R4/9/9/B8/9/2C1K4 b - - 0 1
  if (strongAdvisors == 0 && strongBishops <= 1)
    return ScaleFactor(8);

  // fen 6b2/3k5/b8/9/4R4/6r2/3C5/3K5/9/3A5 b - - 0 1
  if (strongAdvisors + strongBishops <= 1)
    if (weakBishops == 2)
      return ScaleFactor(8);

  // fen 9/4k4/3ab4/9/2b6/5R3/9/9/4A1r2/3C1KB2 r
  if (weakAdvisors >= 1 && weakBishops == 2)
    if (strongAdvisors <= 1 && strongBishops == 0)
      return ScaleFactor(8);
    else if (strongBishops == 0)
      return ScaleFactor(12);
    else if (strongAdvisors <= 1 && strongBishops <= 1)
      return ScaleFactor(12);

  return sf;
}
