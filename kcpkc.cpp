#include "../pch.h"


template<>
ScaleFactor Endgame<KCPKC>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongPawn = pos.square<PAWN>(strongSide);
  Square strongCannon = pos.square<CANNON>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);
  Square weakCannon = pos.square<CANNON>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  if (RR_WK(strongPawn) < RR_WK(weakKing))
    sf = ScaleFactor(32);

  if (weakAdvisors == 2 && weakBishops == 2)
    return ScaleFactor(8);

  if (strongAdvisors == 0 && strongBishops == 0)
    return ScaleFactor(8);

  // fen 2b6/4P4/3k5/9/3c5/9/9/3A4B/9/2C1K4 w - - 35 35
  if (RR_WK(strongPawn) == RANK_0)
    return ScaleFactor(8);

  if (RR_WK(strongPawn) < RR_WK(weakKing))
  {
    if (weakAdvisors == 2)
      return ScaleFactor(8);
    if (weakBishops != 0)
      return ScaleFactor(8);
  }

  // fen 2b6/3k1P3/3a5/3c5/9/6B2/9/3K5/4A4/7C1 w - - 122 122
  if (weakAdvisors != 0 && weakBishops != 0)
    if (RR_WK(strongPawn) >= RANK_1)
      return ScaleFactor(8);

  // fen 9/5k3/4P4/9/9/2B6/5c3/9/4K2C1/6B2 b - - 0 0
  if (weakAdvisors != 0 && RF_XX(weakCannon) != RF_XX(weakKing))
    if (RR_WK(strongPawn) >= RANK_2 && abs(RR_WK(weakKing) - RR_WK(strongPawn)) <= 1)
      if (RF_XX(weakCannon) != RF_XX(weakKing))
        return ScaleFactor(8);
      else
        return ScaleFactor(8);

  if (weakBishops != 0)
    if (RR_WK(strongCannon) >= RANK_3 && RR_WK(weakCannon) >= RANK_4)
      if (RR_WK(weakCannon) > RR_WK(strongCannon))
        return ScaleFactor(8);

  // fen 9/4k4/1c7/4P4/2b3b2/9/3C5/3A5/4A4/5K3 b - - 0 1
  if (weakBishops == 2 && RR_WK(strongPawn) <= RANK_3)
    if (RR_WK(weakKing) >= RANK_1)
      sf = ScaleFactor(16);

  // fen 4c4/9/b3k1P2/9/9/9/9/3A5/3C1K3/9 w - - 218 218
  if (weakBishops != 0 && strongAdvisors <= 1 && strongBishops == 0)
    if (RR_WK(strongPawn) >= RANK_2 && abs(RR_WK(strongPawn) - RR_WK(weakKing)) <= 1)
      if (PC_ON_ST(SQ_E9) == MK_PC_WK(CANNON) && RF_XX(weakKing) == FILE_E)
        return ScaleFactor(8);

  // fen 9/6c2/b2aka3/9/6b2/9/3p5/3AC4/4A4/3K5 b - - 0 1
  if (weakAdvisors == 2 && RR_WK(weakKing) >= RANK_1)
    if ((PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR)) || (PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR)))
      sf = ScaleFactor(16);

  // fen 4k4/2c6/b8/2C6/2b6/2P6/9/3KB3B/4A4/5A3 w - - 0 105
  if (weakBishops == 2 && RR_WK(weakKing) >= RANK_1)
    sf = ScaleFactor(16);

  // fen 4k4/9/2ca2P2/9/6b2/9/6C2/5A2B/4A4/4K1B2 b - - 0 1
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (RR_WK(weakKing) >= RANK_1 && abs(RF_XX(strongPawn) - FILE_E) >= 2)
      if (not_z(cannon_attacks_bb(weakCannon, pos.bit_mask_x(weakCannon), pos.bit_mask_y(weakCannon)) & PP_BB_ST(PAWN)))
        return ScaleFactor(8);

  // fen 5a3/3P1k3/c8/9/9/9/9/5A3/4K4/1C4B2 w - - 0 1
  if (weakAdvisors >= 1)
    if (RR_WK(weakCannon) == RANK_2 && RR_WK(strongPawn) >= RANK_1)
    {
      if (RF_XX(strongPawn) < FILE_E && RF_XX(weakKing) == FILE_F)
        if (PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
      if (RF_XX(strongPawn) > FILE_E && RF_XX(weakKing) == FILE_D)
        if (PC_ON_ST(SQ_D9) == MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
    }

  // fen 2bk5/4a4/4ba3/9/p8/2B1c3C/9/4B4/9/5K3 w - - 0 1
  if (weakBishops == 2 && RR_WK(weakKing) >= RANK_1)
    if (RR_WK(strongPawn) <= RANK_5)
      sf = ScaleFactor(24);
    else
      sf = ScaleFactor(12);

  // fen 3c1kb2/9/3a5/5P3/9/9/2C6/5A3/4A4/4K1B2 b - - 0 1
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (RR_WK(weakKing) >= RANK_1 && RR_WK(weakCannon) >= RANK_1)
      sf = ScaleFactor(12);

  // fen 6c2/4a4/3k1a3/9/6b2/9/4C4/4p3B/4A4/4K4 b - - 124 124
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (PC_ON_ST(SQ_E8) == MK_PC_WK(ADVISOR) && PC_ON_ST(SQ_E7) == MK_PC_ST(PAWN))
      if (RF_XX(strongCannon) != FILE_E)
        return ScaleFactor(16);

  // fen 4k4/4a1c2/4b4/9/4C1b2/9/4p4/8B/9/4KA3 w - - 136 136
  if (weakAdvisors >= 1 && weakBishops >= 1)
  {
    if (strongAdvisors == 0)
      return ScaleFactor(16);
    if (strongAdvisors <= 1)
      if (not_z(cannon_attacks_bb(weakCannon, pos.bit_mask_x(weakCannon), pos.bit_mask_y(weakCannon)) & (PP_BB_WK(CANNON) & SquareBB[strongKing])))
        return ScaleFactor(16);
  }

  // fen 4k4/4a4/b2c2P2/9/9/2B3B2/9/3A1A3/4K4/2C6 w
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (RR_WK(weakKing) == RANK_0 && RR_WK(strongPawn) >= RANK_2)
      if (PC_ON_ST(SQ_E8) == MK_PC_WK(ADVISOR) && abs(RF_XX(strongPawn) - FILE_E) >= 2)
        return ScaleFactor(16);

  if (weakAdvisors + weakBishops >= 2)
    return ScaleFactor(16);

  // fen 3k1ab2/9/4ba3/8p/9/9/9/3cB4/7C1/5K3 r
  if (weakBishops >= 1)
    if (PC_ON_ST(SQ_E8) == MK_PC_ST(PAWN) && RR_WK(weakKing) == RANK_0)
      return ScaleFactor(16);

  // fen 4k4/4a4/3aP4/4c4/9/2B6/9/4KA3/3C5/6B2 b - - 0 111
  if (weakAdvisors <= 1 && weakBishops >= 1)
    if (RR_WK(weakKing) == RANK_1 && RR_WK(weakCannon) == RANK_2)
      if (RR_WK(strongPawn) >= RANK_1)
      {
        if (PC_ON_ST(SQ_D8) == MK_PC_WK(KING) && PC_ON_ST(SQ_D9) == MK_PC_WK(ADVISOR))
          if (RF_XX(strongPawn) >= FILE_E)
            return ScaleFactor(16);
        if (PC_ON_ST(SQ_F8) == MK_PC_WK(KING) && PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR))
          if (RF_XX(strongPawn) <= FILE_E)
            return ScaleFactor(16);
      }

  // fen 9/4ak3/9/5P3/9/6B2/9/3K5/5c3/3C5 b - - 0 1
  if (weakAdvisors >= 1 && strongAdvisors == 0 && strongBishops <= 1)
    if (RR_WK(weakKing) >= RANK_1 && RR_WK(strongPawn) <= RANK_3)
      return ScaleFactor(16);

  // fen 5k3/4a4/3a4c/9/9/2B3B2/5p3/9/4A4/1C1K5 b - - 0 1
  if (strongAdvisors >= 1 && strongBishops == 2)
    if (RR_WK(weakKing) == RANK_0)
      if (RR_WK(strongPawn) < RANK_1)
        return ScaleFactor(16);
      else
        return ScaleFactor(32);

  // fen 9/4P4/3k5/3c5/9/2B6/9/3AK4/9/6C2 w - - 0 0
  if (strongAdvisors <= 1 && RR_WK(strongPawn) < RR_WK(weakKing))
    return ScaleFactor(32);

  // fen 3k5/c8/5a3/3P5/9/6B2/9/4K4/6C2/2B6 b - - 0 1
  if (weakAdvisors >= 1 && strongAdvisors == 0)
    if (RR_WK(weakCannon) == RANK_1 && RR_WK(weakKing) == RANK_0)
      return ScaleFactor(32);

  return sf;
}
