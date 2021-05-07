
#include "../pch.h"

template<>
ScaleFactor Endgame<KPK>::operator()(const Position& pos) const {

  Square strongKing = pos.square<KING>(strongSide);
  Square strongPawn = pos.square<PAWN>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  ScaleFactor sf = ScaleFactor(8);

  if (weakAdvisors + weakBishops == 0)
    if (RR_ST(strongPawn) >= RR_ST(weakKing))
      return SCALE_FACTOR_NORMAL;

  // fen 5k3/9/3aPa3/9/9/9/9/9/9/4K4 w - - 0 1
  if (weakBishops == 0 && weakAdvisors == 2)
    if (PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR) && PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR))
      if (RS_ST(strongPawn) == SQ_E7)
        return SCALE_FACTOR_NORMAL;

  return sf;
}
