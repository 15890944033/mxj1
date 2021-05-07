
#include "../pch.h"


template<>
ScaleFactor Endgame<KRPKP>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongPawn = pos.square<PAWN>(strongSide);
  Square strongRook = pos.square<ROOK>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);
  Square weakPawn = pos.square<PAWN>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  if (weakAdvisors == 2 && weakBishops == 2)
    sf = ScaleFactor(8);

  // fen 3a1kb2/4a4/4b4/9/5Rp2/2B6/6P2/5A2B/4K4/3A5 b - - 18 18
  if (weakAdvisors == 2 && weakBishops == 2)
    if (PC_ON_ST(SQ_E7) == MK_PC_WK(BISHOP) && RR_WK(weakKing) == RANK_0)
    {
      if (PC_ON_ST(SQ_G5) == MK_PC_WK(PAWN) && PC_ON_ST(SQ_G3) == MK_PC_ST(PAWN))
        return ScaleFactor(8);
      if (PC_ON_ST(SQ_C5) == MK_PC_WK(PAWN) && PC_ON_ST(SQ_C3) == MK_PC_ST(PAWN))
        return ScaleFactor(8);
    }

  return sf;
}
