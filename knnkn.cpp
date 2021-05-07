
#include "../pch.h"


template<>
ScaleFactor Endgame<KNNKN>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongKnight1 = lsb(pos.pieces(strongSide, KNIGHT));
  Square strongKnight2 = msb(pos.pieces(strongSide, KNIGHT));
  Square weakKing = pos.square<KING>(weakSide);
  Square weakKnight = pos.square<KNIGHT>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  if (weakAdvisors == 2 && weakBishops == 2)
    sf = ScaleFactor(16);
  else if (weakAdvisors >= 1 && weakBishops == 2)
    sf = ScaleFactor(16);
  else if (weakAdvisors == 2 && weakBishops >= 1)
    sf = ScaleFactor(16);
  else if (weakAdvisors + weakBishops >= 2)
    sf = ScaleFactor(16);

  if (weakAdvisors == 2 || weakBishops == 2)
    if (RR_WK(weakKing) >= RANK_1)
      sf -= ScaleFactor(2);

  // fen 2ba1k3/4a1N2/4b4/6N2/9/9/8n/4B4/4A4/2BAK4 w - - 0 0
  if (strongAdvisors >= 1 && strongBishops == 2)
    if (RR_WK(weakKnight) <= RANK_6)
      if ((RF_XX(weakKnight) == RF_XX(strongKnight1)) || (RF_XX(weakKnight) == RF_XX(strongKnight2)))
        if ((RR_WK(weakKnight) < RR_WK(strongKnight1)) || (RR_WK(weakKnight) < RR_WK(strongKnight2)))
          if (abs(RR_WK(weakKnight) - RR_WK(strongKnight1)) == 1 || abs(RR_WK(weakKnight) - RR_WK(strongKnight2)) == 1)
            sf += ScaleFactor(8);

  // fen 6b2/4Nk3/4b4/4nN3/9/6B2/9/3AB4/9/3K1A3 b - - 16 16
  if (weakBishops == 2)
    if (PC_ON_ST(SQ_E8) == MK_PC_ST(KNIGHT))
      if (PC_ON_ST(SQ_E7) == MK_PC_WK(BISHOP) && PC_ON_ST(SQ_E6) == MK_PC_WK(KNIGHT))
        if (RR_WK(weakKing) >= RANK_1)
          return ScaleFactor(8);

  // fen 9/3ka4/5a3/3N5/6b2/9/3n5/4BAn1B/5K3/9 w - - 66 66
  if (weakAdvisors >= 1 && strongBishops == 2)
    if (RR_WK(weakKing) >= RANK_1 && RR_WK(weakKnight) >= RANK_6)
      return ScaleFactor(8);
    else
      return ScaleFactor(16);

  // fen 9/4ak3/5a2b/3N5/4N4/7n1/9/9/5K3/2B6 b - - 0 1
  if (weakAdvisors == 2 && weakBishops >= 1)
    if (RR_WK(weakKing) >= RANK_1 && RR_WK(weakKnight) >= RANK_4)
      return ScaleFactor(16);

  // fen 9/4ak1N1/4ba3/4N4/9/9/6n2/9/9/5KB2 b - - 0 1
  if (weakAdvisors == 2 && weakBishops >= 1)
    if (RR_WK(weakKing) >= RANK_1 && RR_WK(weakKnight) >= RANK_4)
      return ScaleFactor(16);
    else
      return ScaleFactor(32);

  // fen 5a3/3k5/5a3/9/9/4n1B2/9/4B1n2/6N2/4K4 w - - 0 1
  if (weakBishops == 2)
    if (RR_WK(weakKing) == RANK_0 && RR_WK(weakKnight) >= RANK_5)
      return ScaleFactor(32);

  // fen 3a1k3/9/3a5/3N5/n8/3N5/9/5A2B/9/3A1K3 w - - 0 1
  if (weakAdvisors == 2)
    if (RR_WK(weakKing) >= RANK_1)
      return ScaleFactor(32);

  return sf;
}
