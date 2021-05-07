
#include "../pch.h"


template<>
ScaleFactor Endgame<KRRKR>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongRook1 = pos.squares<ROOK>(strongSide)[0];
  Square strongRook2 = pos.squares<ROOK>(strongSide)[1];
  Square weakKing = pos.square<KING>(weakSide);
  Square weakRook = pos.square<ROOK>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  if (weakAdvisors + weakBishops == 4)
    return ScaleFactor(8);

  return sf;
}
