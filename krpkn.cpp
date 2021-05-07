
#include "../pch.h"


template<>
ScaleFactor Endgame<KRPKN>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongPawn = pos.square<PAWN>(strongSide);
  Square strongRook = pos.square<ROOK>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);
  Square weakKnight = pos.square<KNIGHT>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  if (weakAdvisors == 2 && weakBishops == 2)
    if (RR_WK(weakKing) == RANK_0)
    {
      // fen 3aka3/3P5/4n3b/9/6b2/7R1/9/B8/4K4/6B2 w - - 0 1
      if (PC_ON_ST(SQ_E9) == MK_PC_WK(KING) && PC_ON_ST(SQ_E7) == MK_PC_WK(KNIGHT))
        if (RR_WK(strongPawn) >= RANK_1)
        {
          if (!(PP_BB_WK(BISHOP) & LeftBB) && PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR))
            if (RF_XX(strongPawn) < FILE_E)
              return ScaleFactor(8);
          if (!(PP_BB_WK(BISHOP) & RightBB) && PC_ON_ST(SQ_C9) == MK_PC_WK(ADVISOR))
            if (RF_XX(strongPawn) > FILE_E)
              return ScaleFactor(8);
        }

      if (RR_WK(weakKnight) <= RANK_2)
      {
        // fen 5k3/4a4/3ab4/3N5/9/6B2/9/3AB4/4Ar3/4K2p1 w - - 0 1
        if (RR_WK(strongPawn) == RANK_0 && abs(RF_XX(strongPawn) - FILE_E) >= 3)
          return ScaleFactor(8);

        // fen 1R1aka3/5P3/b3n4/9/2b6/9/9/3AK3B/9/3A5 w - - 0 113
        if (RR_WK(strongPawn) >= RANK_2)
        {
          if (RR_WK(strongPawn) >= RANK_1 || abs(RF_XX(strongPawn) - FILE_E) >= 2)
            if (PC_ON_ST(SQ_E7) == MK_PC_WK(KNIGHT))
            {
              if (popcount(PP_BB_WK(BISHOP) & LeftBB) == 2)
                return ScaleFactor(16);
              if (popcount(PP_BB_WK(BISHOP) & RightBB) == 2)
                return ScaleFactor(16);
            }
          return ScaleFactor(32);
        }
      }
    }

  return sf;
}
