
#include "../pch.h"


template<>
ScaleFactor Endgame<KNPKN>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongPawn = pos.square<PAWN>(strongSide);
  Square strongKnight = pos.square<KNIGHT>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);
  Square weakKnight = pos.square<KNIGHT>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  Bitboard b = PP_BB_ST(PAWN), bb = NoSquares;
  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  // fen 2b1k4/4aP3/3a5/9/2bN5/9/3p5/B8/9/3AKA3 b - - 0 1
  if (weakAdvisors == 2 && weakBishops == 2)
    sf = ScaleFactor(8);
  else if (weakAdvisors + weakBishops >= 2)
    sf = ScaleFactor(16);

  // fen 4k4/4a4/4P4/5n3/9/5N3/9/8B/9/2B1K4 b - - 0 1
  if (weakAdvisors >= 1)
    if (RR_WK(weakKing) == RANK_0 && RR_WK(weakKnight) >= RANK_4)
      sf = ScaleFactor(16);

  if (RR_WK(strongPawn) == RANK_0)
    return ScaleFactor(8);

  if (weakBishops >= 1)
    if (RR_WK(weakKnight) >= RANK_4)
      return ScaleFactor(8);

  if (weakAdvisors == 2)
    return ScaleFactor(8);

  // fen 3a1k3/2P6/9/2N1n4/9/9/9/9/9/4K4 w
  if (weakAdvisors != 0)
    if (RR_WK(weakKnight) >= RANK_4)
      if (RR_WK(strongPawn) > RANK_2)
        return ScaleFactor(8);

  // fen 5k3/3P5/3ab3b/9/9/9/8N/5A3/4K4/6Bn1 w - - 46 46
  if (weakAdvisors != 0 && weakBishops == 2)
    if (abs(RR_WK(weakKnight) - RR_WK(strongKnight)) <= 3)
      return ScaleFactor(8);

  // fen 9/3P5/4k3b/9/2N6/9/9/1n2BA3/9/3K5 b - - 15 15
  if (weakBishops >= 1)
    if (RR_WK(strongPawn) < RR_WK(weakKing))
      return ScaleFactor(8);

  if (weakBishops == 2)
    return ScaleFactor(8);

  // fen 6b2/1N2a4/3a1k3/9/6b2/1nB6/9/7p1/3KA4/9 b - - 0 1
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (!(RR_WK(weakKing) == RANK_0 && PC_ON_ST(SQ_E8) == MK_PC_ST(PAWN)))
      return ScaleFactor(8);

  // fen 3a5/5k3/4P4/1N7/1n7/2B6/9/5A3/4A4/4K1B2 w - - 0 102
  if (weakAdvisors >= 1)
    if (RR_WK(weakKnight) >= RANK_5 && RR_WK(weakKing) == RANK_1)
      if (PC_ON_ST(SQ_D9) == MK_PC_WK(ADVISOR) || PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR))
        return ScaleFactor(8);

  // fen 5k3/9/b3b4/5NP2/9/2n6/9/8B/4A4/4K4 w - - 0 1
  if (weakBishops == 2)
    if (RR_WK(strongPawn) <= RANK_3 && RR_WK(weakKnight) >= RANK_5)
      return ScaleFactor(16);

  // fen 3a5/5k3/4P4/1N7/1n7/2B6/9/5A3/4A4/4K1B2 w - - 0 102
  if (weakAdvisors >= 1)
    if (RR_WK(weakKnight) >= RANK_5)
    {
      if (RR_WK(weakKing) == RANK_1)
        return ScaleFactor(16);

      // fen 3a1k3/9/4P4/4n1N2/9/2B3B2/9/3K1A3/9/5A3 b - - 0 1
      if (PC_ON_ST(SQ_E7) == MK_PC_ST(PAWN) && PC_ON_ST(SQ_E6) == MK_PC_WK(KNIGHT))
        return ScaleFactor(24);

      // fen 3a1k3/9/4P4/4n4/3N5/9/9/3A1A3/9/3K5 b - - 0 112
      if (RR_WK(weakKing) >= RANK_1 && RR_WK(strongPawn) >= RANK_2)
        return ScaleFactor(24);

      return ScaleFactor(32);
    }

  return sf;
}
