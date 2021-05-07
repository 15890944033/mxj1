
#include "../pch.h"


template<>
ScaleFactor Endgame<KNNKC>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongKnight1 = lsb(pos.pieces(strongSide, KNIGHT));
  Square strongKnight2 = msb(pos.pieces(strongSide, KNIGHT));
  Square weakKing = pos.square<KING>(weakSide);
  Square weakCannon = pos.square<CANNON>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  ScaleFactor sf = SCALE_FACTOR_NORMAL;
  Color us = strongSide == pos.side_to_move() ? WHITE : BLACK;

  if (weakAdvisors == 2 && weakBishops == 2)
  {
    if (strongAdvisors + strongBishops == 0)
      sf = ScaleFactor(8);
    else if (strongAdvisors + strongBishops <= 1)
      sf = ScaleFactor(6);
    else if (strongAdvisors + strongBishops <= 3)
      sf = ScaleFactor(8);
    else if (strongAdvisors + strongBishops <= 4)
      sf = ScaleFactor(12);
  }
  else if (weakAdvisors == 0 && weakBishops == 2)
  {
    if (strongAdvisors + strongBishops == 0)
      sf = ScaleFactor(8);
    else if (strongAdvisors + strongBishops <= 1)
      sf = ScaleFactor(8);
    else if (strongAdvisors + strongBishops <= 3)
      sf = ScaleFactor(12);
  }
  else if (weakAdvisors + weakBishops == 3)
  {
    if (strongAdvisors + strongBishops == 0)
      sf = ScaleFactor(8);
    if (strongAdvisors + strongBishops <= 3)
      sf = ScaleFactor(12);
  }

  // fen 4k4/4a4/5a1N1/5N3/5c3/2B6/9/9/3K5/3A1A3 w - - 0 1
  if (weakAdvisors == 2)
    if (RR_WK(weakKing) == RANK_0)
      return ScaleFactor(8);

  // fen 4k4/9/5a3/9/2b6/9/3n5/5n2B/5C3/5KB2 w - - 0 0
  if (weakBishops == 2 && RR_WK(weakKing) >= RANK_1)
  {
    Bitboard b = pos.pieces(weakSide, BISHOP);
    Square weakBishop1 = msb(b);
    Square weakBishop2 = lsb(b);

    //if (and_true(bishop_attacks_bb(weakBishop1, pos.pieces()),
    //  bishop_attacks_bb(weakBishop2, pos.pieces())))
      return ScaleFactor(8);
  }

  // fen 4k4/4a4/4ba3/5N3/4cN3/9/9/3AB3B/4A4/5K3 w - - 0 0
  if (weakAdvisors == 2 && weakBishops >= 1)
    if (PC_ON_WK(SQ_D7) == MK_PC_WK(ADVISOR) || PC_ON_WK(SQ_F7) == MK_PC_WK(ADVISOR))
      if (RR_WK(weakCannon) > RANK_4)
        return ScaleFactor(8);

  if (weakBishops == 2 && RR_WK(weakKing) >= RANK_1)
    return ScaleFactor(8);

  return sf;
}
