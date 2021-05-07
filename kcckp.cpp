
#include "../pch.h"


template<>
ScaleFactor Endgame<KCCKP>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongCannon1 = msb(pos.pieces(strongSide, CANNON));
  Square strongCannon2 = lsb(pos.pieces(strongSide, CANNON));
  Square weakKing = pos.square<KING>(weakSide);
  Square weakPawn = pos.square<PAWN>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  if (weakBishops == 2)
    if (strongAdvisors == 0 && strongBishops == 0)
      return ScaleFactor(8);

  if (strongAdvisors == 0)
    return ScaleFactor(16);

  if (weakAdvisors == 2 && weakBishops == 2)
    if (RR_WK(weakKing) == RANK_0)
      return ScaleFactor(32);

  return sf;
}
