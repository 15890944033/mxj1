
#include "../pch.h"


template<>
ScaleFactor Endgame<KCCKC>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongCannon1 = msb(pos.pieces(strongSide, CANNON));
  Square strongCannon2 = lsb(pos.pieces(strongSide, CANNON));
  Square weakKing = pos.square<KING>(weakSide);
  Square weakCannon = pos.square<CANNON>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  if (weakAdvisors == 2 && weakBishops == 2)
    return ScaleFactor(8);

  if (strongAdvisors == 0 && strongBishops == 0)
    return ScaleFactor(8);

  // fen 4k4/4C4/1c7/9/9/2B6/9/9/C8/4K4 b - - 0 1
  if (strongAdvisors == 0)
    if (RR_WK(weakCannon) <= RANK_4)
      return ScaleFactor(8);

  // fen 4c4/5c3/3k5/9/6b2/9/9/9/4K4/3C5 w - - 0 1
  if (strongAdvisors == 0)
    if (RR_WK(weakCannon) <= RANK_0 && RR_WK(weakKing) != RANK_0)
      return ScaleFactor(8);

  // fen 4k1b2/9/6c2/6c2/6b2/9/9/5C3/4A4/4K4 b - - 0 1
  if (weakAdvisors >= 1 && strongAdvisors == 0)
    if (RR_WK(weakKing) <= RANK_1)
      return ScaleFactor(8);

  if (strongAdvisors == 0 && weakBishops == 2)
    return ScaleFactor(8);


  if (weakAdvisors + weakBishops == 3)
  {
    if (strongAdvisors == 1 && strongBishops == 0)
      return ScaleFactor(8);
    if (strongAdvisors == 0 && strongBishops <= 2)
      return ScaleFactor(8);
    if (strongAdvisors == 0 && strongBishops == 0)
      return ScaleFactor(8);
    return ScaleFactor(16);
  }
  else if (weakAdvisors + weakBishops == 2)
  {
    if (strongAdvisors + strongBishops > 2)
      return ScaleFactor(16);
    return ScaleFactor(8);
  }

  return sf;
}
