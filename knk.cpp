
#include "../pch.h"

template<>
ScaleFactor Endgame<KNK>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongKnight = pos.square<KNIGHT>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  ScaleFactor sf = ScaleFactor(8);

  if (weakAdvisors <= 1 && weakBishops == 0)
    sf = SCALE_FACTOR_NORMAL;

  return sf;
}
