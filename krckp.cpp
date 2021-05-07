
#include "../pch.h"


template<>
ScaleFactor Endgame<KRCKP>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongCannon = pos.square<CANNON>(strongSide);
  Square strongRook = pos.square<ROOK>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);
  Square weakPawn = pos.square<PAWN>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  Bitboard pinners, cannonCandidates;
  Bitboard pinned = pos.pinned_pieces(strongSide, pinners, cannonCandidates);

  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  if (weakAdvisors + weakBishops == 4)
  {
    if (strongAdvisors + strongBishops <= 1)
      sf = ScaleFactor(8);
    if (strongAdvisors + strongBishops <= 3)
      sf = ScaleFactor(24);
    else
      sf = ScaleFactor(32);
  }
  else if (weakAdvisors + weakBishops == 3)
  {
    if (strongAdvisors + strongBishops == 0)
      sf = ScaleFactor(8);
    else if (strongAdvisors + strongBishops <= 1)
      sf = ScaleFactor(24);
    else if (strongAdvisors + strongBishops <= 3)
      sf = ScaleFactor(32);
  }
  else if (weakAdvisors + weakBishops <= 1)
  {
    if (strongAdvisors + strongBishops == 0)
      sf = ScaleFactor(16);
  }

  // fen 5kb2/4a4/9/9/9/2B6/9/9/4KC1R1/5r3 w - - 35 35
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (strongAdvisors == 0)
      return ScaleFactor(8);

  // fen 4k4/6C2/4b4/9/2b6/9/9/3R4B/1r2K4/9 w - - 7 7
  if (weakBishops == 2 && strongAdvisors == 0)
    if (RR_WK(weakKing) != RANK_2)
      return ScaleFactor(8);

  return sf;
}
