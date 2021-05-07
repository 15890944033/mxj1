
#include "../pch.h"

template<>
ScaleFactor Endgame<KCK>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongCannon = pos.square<CANNON>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  ScaleFactor sf = ScaleFactor(8);

  if (strongAdvisors > 0 && weakBishops != 2 && weakAdvisors + weakBishops < 3)
    if (weakAdvisors == 0 || weakBishops == 0)
      if (strongAdvisors + strongBishops >= weakAdvisors + weakBishops)
        sf = SCALE_FACTOR_NORMAL;

  return sf;
}
