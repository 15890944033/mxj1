
#include "../pch.h"


template<>
ScaleFactor Endgame<KCPKP>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongPawn = pos.square<PAWN>(strongSide);
  Square strongCannon = pos.square<CANNON>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);
  Square weakPawn = pos.square<PAWN>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  if (strongAdvisors == 0 && strongBishops == 0)
    if (RR_WK(weakPawn) > RANK_7)
      if (RR_WK(weakPawn) < RANK_4)
        return ScaleFactor(8);

  // fen 1C2ka3/4a4/4b4/9/p1b6/6B2/P8/9/9/2BAKA3 w - - 3 3
  if (weakAdvisors == 2 && weakBishops == 2)
    return ScaleFactor(8);

  // fen 5P3/3k5/4b4/9/6b2/6B2/2p6/4BA3/3C5/4KA3 b
  if (weakAdvisors == 2 || weakBishops == 2)
    if (RR_WK(strongPawn) == RANK_0)
      return ScaleFactor(8);
    else if (RR_WK(strongPawn) > RR_WK(weakKing))
      return ScaleFactor(8);

  // fen 3k1a3/9/5a2b/4c1p2/2b6/6P2/9/B3B4/4A4/4K4 b - - 0 0
  if (weakAdvisors >= 1 && weakBishops == 2)
    if (RR_WK(weakKing) == RANK_0)
    {
      if (PC_ON_ST(SQ_C5) == MK_PC_WK(PAWN) && PC_ON_ST(SQ_C3) == MK_PC_ST(PAWN))
        return ScaleFactor(8);
      if (PC_ON_ST(SQ_G5) == MK_PC_WK(PAWN) && PC_ON_ST(SQ_G3) == MK_PC_ST(PAWN))
        return ScaleFactor(8);
    }

  if (strongAdvisors == 0)
  {
    // fen 3a1a3/9/4k3P/9/9/9/5p3/9/5K3/8C w - - 0 1
    if (weakBishops == 0 && strongBishops == 0)
      if (weakAdvisors == 2)
        return ScaleFactor(8);

    // fen 3k5/4P4/3a5/9/9/2B6/2p6/9/3K5/1C7 w - - 0 1
    if (RR_WK(strongPawn) >= RANK_1)
      if (abs(RR_WK(weakKing) - RR_WK(strongPawn)) <= 1)
        if (RR_WK(weakPawn) == RANK_6 && RF_XX(weakPawn) != RF_XX(strongKing))
          return ScaleFactor(8);

    // fen 2C6/3P5/b4k3/9/9/9/9/9/4K4/4p4 w - - 104 104
    if (RR_WK(weakKing) > RR_WK(strongPawn))
      if (weakBishops != 0)
        return ScaleFactor(8);

    if (RR_WK(strongPawn) >= RANK_2)
      if (abs(RR_WK(weakKing) - RR_WK(strongPawn)) <= 1)
        if (weakBishops != 0 && strongBishops == 0)
          return ScaleFactor(8);

    // fen 9/6P2/4k4/9/9/9/5p3/9/C8/2B2KB2 b - - 0 1
    if (RR_WK(weakKing) > RR_WK(strongPawn) && RR_ST(weakPawn) == RANK_6)
      return ScaleFactor(8);
  }
  else if (strongAdvisors == 1)
  {
    // fen 5kC2/4P4/9/9/2b6/9/9/9/5p3/3AK4 w - - 0 0
    if (weakBishops != 0)
      if (RR_ST(strongKing) == RANK_0 && RR_WK(strongPawn) >= RANK_1)
        if (PC_ON_WK(SQ_D8) == MK_PC_WK(PAWN) || PC_ON_WK(SQ_F8) == MK_PC_WK(PAWN))
          if (PC_ON_WK(SQ_D9) == MK_PC_ST(ADVISOR) || PC_ON_WK(SQ_F9) == MK_PC_ST(ADVISOR))
            return ScaleFactor(8);
  }

  // fen 3k5/4aP3/4ba3/9/2b6/2B3C2/9/3A1A3/4p4/5K3 b - - 0 1
  if (weakAdvisors == 2 && weakBishops == 2)
    if (RR_WK(weakKing) == RANK_0 && RR_WK(strongPawn) >= RANK_1)
      if (PC_ON_ST(SQ_E8) == MK_PC_WK(ADVISOR))
      {
        if (RF_XX(strongPawn) > FILE_E && PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
        if (RF_XX(strongPawn) < FILE_E && PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
      }

  // fen 4k4/9/3a4b/9/2b6/6P2/2p6/4BA3/9/3K1C3 w - - 0 0
  if (weakAdvisors >= 1 && weakBishops == 2)
    if (RR_WK(weakPawn) == RANK_5 || RR_WK(weakPawn) == RANK_6)
      return ScaleFactor(8);

  // fen 5k3/4P4/4b4/9/6b2/2B6/9/3K1C3/4p4/9 b - - 0 1
  if (weakBishops == 2 && strongAdvisors == 0)
    if (RR_WK(strongPawn) >= RANK_1)
      if (abs(RR_WK(strongPawn) - RR_WK(weakKing)) <= 1)
        return ScaleFactor(8);

  // fen 3ak4/5P3/4b4/9/6b2/6B2/p8/3A5/4AK3/4C4 r
  if (weakAdvisors >= 1 && weakBishops == 2)
    if (RR_WK(weakPawn) == RANK_6 && RR_WK(strongPawn) >= RANK_1)
      if (PC_ON_ST(SQ_E9) == MK_PC_WK(KING) && PC_ON_ST(SQ_E8) == MK_PC_WK(ADVISOR))
      {
        if (not_z(pos.attackers_to(RS_ST(SQ_E7), pos.pieces(weakSide))))
          if (PC_ON_ST(SQ_E7) == MK_PC_WK(BISHOP))
            return ScaleFactor(8);
        if (not_z(bishop_attacks_bb(lsb(pos.pieces(weakSide, BISHOP)), pos.pieces())
          & bishop_attacks_bb(msb(pos.pieces(weakSide, BISHOP)), pos.pieces())))
          return ScaleFactor(8);
      }

  // fen 2b2k3/9/9/5P3/2b6/2B6/3p5/8B/5K3/4C4 b - - 0 1
  if (weakBishops == 2 && strongAdvisors == 0)
    if (RR_WK(weakPawn) == RANK_6 && RF_XX(weakPawn) != RF_XX(weakKing))
      return ScaleFactor(8);

  // fen 1C4b2/5k3/3a5/9/9/8P/1p7/4B4/4K4/2B6 r
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (strongAdvisors == 0)
      if (RR_WK(weakPawn) >= RANK_6)
        sf = ScaleFactor(8);

  // fen 5a3/3k1P3/3a5/9/9/9/6p2/3ABA3/3C5/4K1B2 b - - 0 1
  if (weakAdvisors >= 1)
    if (RR_WK(weakPawn) == RANK_6 && RF_XX(weakPawn) != RF_XX(weakKing))
      //if (RR_WK(strongPawn) == RANK_0 && PC_ON_ST(SQ_E9) != MK_PC_WK(KING))
      return ScaleFactor(8);

// fen 7P1/3k5/9/9/9/9/5p3/9/4AK3/4C4 r
  if (weakAdvisors <= 1 && RR_WK(weakPawn) == RANK_6)
    if (RR_WK(strongPawn) == RANK_0 && RR_WK(weakKing) != RANK_0)
      if (abs(RF_XX(weakPawn) - FILE_E) <= 1)
        return ScaleFactor(8);

  // fen 5a3/3k1P3/3a5/9/9/9/6p2/3ABA3/3C5/4K1B2 b - - 0 1
  if (weakAdvisors == 2 && RR_WK(weakPawn) == RANK_6)
    if (RF_XX(weakPawn) != RF_XX(weakKing))
      if (RR_WK(strongPawn) >= RANK_1)
      {
        if (RF_XX(weakKing) == FILE_D && RF_XX(strongPawn) >= FILE_F)
          if (RR_WK(strongPawn) == RANK_1)
            return ScaleFactor(8);
          else
            return ScaleFactor(8);
        if (RF_XX(weakKing) == FILE_F && RF_XX(strongPawn) <= FILE_D)
          if (RR_WK(strongPawn) == RANK_1)
            return ScaleFactor(8);
          else
            return ScaleFactor(8);
      }

  // fen 2b1k1b2/4a4/9/4P4/9/4C4/4p4/3A1A3/3K5/2B6 b - - 0 1
  if (weakAdvisors >= 1 && weakBishops == 2)
    if (RR_WK(weakKing) == RANK_0 && RR_WK(weakPawn) == RANK_6)
      if (RR_WK(strongPawn) <= RANK_2)
        return ScaleFactor(8);

  // fen 4kab2/4a4/9/9/2b4P1/2c6/4p4/9/4A4/3K1AB2 b - - 0 1
  if (weakAdvisors == 2 && weakBishops >= 1)
    if (RR_WK(weakKing) == RANK_0)
      if (RR_WK(weakPawn) == RANK_5 || RR_WK(weakPawn) == RANK_6)
        return ScaleFactor(8);

  // fen 5k3/3Pa4/3a5/9/2b6/9/6p2/3K5/4A4/3A2C2 w - - 0 1
  if (weakAdvisors == 2 && weakBishops >= 1)
    if (strongBishops == 0 && !EQ_FLK_WK(weakKing, strongPawn))
      if (RR_WK(weakKing) == RANK_0 && RR_WK(weakPawn) == RANK_6)
        if (RR_WK(strongPawn) >= RANK_1)
          return ScaleFactor(8);

  // fen 3ac4/9/4k3b/2P6/9/2B6/9/4B4/5p3/4K4 w - - 0 123
  if (weakBishops == 2 && RR_WK(weakPawn) == RANK_6)
    if (RR_WK(strongPawn) >= RANK_2 && RF_XX(weakKing))
      if (abs(RR_WK(strongPawn) - RR_WK(weakKing)) == 1)
        return ScaleFactor(8);

  // fen 3k5/4aP3/4ba3/9/2b6/2B3C2/9/3A1A3/4p4/5K3 b - - 0 1
  if (weakAdvisors == 2 && weakBishops == 2)
    if (RR_WK(weakKing) == RANK_0)
      return ScaleFactor(8);

  // fen 4P4/3k5/3ab4/9/6b2/9/9/3A1A3/3CK4/3p5 w - - 0 1
  if (weakAdvisors >= 1 && weakBishops == 2)
    if (RR_WK(weakKing) != RANK_0 && RR_WK(strongPawn) == RANK_0)
      return ScaleFactor(8);

  // fen 3a1k3/9/3a5/5P3/6b2/9/1C2p4/9/4A4/4KA3 b - - 0 1
  if (weakAdvisors >= 1 && weakBishops == 2)
    if (strongBishops == 0 && RR_WK(weakKing) <= RANK_1)
      if (RR_WK(weakPawn) == RANK_6)
        return ScaleFactor(8);

  // fen 2bk2b2/9/9/4P4/9/4C4/4p4/4B4/9/2B1K4 r
  if (weakAdvisors >= 1 && weakBishops == 2)
    if (RR_WK(weakKing) >= RANK_1 && RR_WK(weakPawn) == RANK_6)
      if (PC_ON_ST(SQ_E9) == MK_PC_WK(KING))
        return ScaleFactor(8);

  // fen 3a5/3Pa4/5k3/9/9/9/9/7C1/4p4/3K5 w - - 0 1
  if (weakAdvisors == 2 && strongAdvisors == 0)
    if (strongBishops == 0 && RR_WK(strongPawn) >= RANK_1)
      if (RR_WK(weakPawn) <= RR_WK(strongKing) && abs(RF_XX(weakPawn) - RF_XX(strongKing)) == 1)
      {
        if (RF_XX(strongPawn) < FILE_E && RF_XX(weakKing) > FILE_E)
          return ScaleFactor(8);
        if (RF_XX(strongPawn) > FILE_E && RF_XX(weakKing) < FILE_E)
          return ScaleFactor(8);
      }

  // fen 4k4/4aP3/b3ba3/9/9/9/9/4CA3/3K5/2p2AB2 w - - 0 1
  if (weakAdvisors == 2 && weakBishops == 2)
    if (RR_WK(weakKing) == RANK_0 && RR_WK(strongPawn) >= RANK_1)
    {
      if (RF_XX(strongPawn) < FILE_E && PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR))
        return ScaleFactor(8);
      if (RF_XX(strongPawn) > FILE_E && PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR))
        return ScaleFactor(8);
    }

  // fen 1C2ka3/4a4/4b4/9/p1b6/6B2/P8/9/9/2BAKA3 w - - 3 3
  if (weakAdvisors == 2 && weakBishops == 2)
    if (RR_WK(weakPawn) == RANK_6)
      return ScaleFactor(8);
    else
      return ScaleFactor(24);

  if (weakAdvisors + weakBishops >= 3 && RR_WK(weakKing) == RANK_0)
    if (RR_WK(weakPawn) == RANK_5 || RR_WK(weakPawn) == RANK_6)
      return ScaleFactor(32);

  // fen 5a3/2P1a4/3k4b/9/9/9/2p6/4BA3/5C3/2BAK4 b - - 0 1
  if (weakAdvisors + weakBishops >= 3)
    if (RR_WK(weakPawn) == RANK_6 || RR_WK(weakKing) > RR_WK(strongPawn))
      return ScaleFactor(32);

  // fen 1C4b2/5k3/3a5/9/9/8P/1p7/4B4/4K4/2B6 r
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (strongAdvisors == 0 && RR_WK(weakPawn) == RANK_6)
    {
      if (RF_XX(weakKing) == FILE_D && !(PP_BB_WK(ADVISOR) & LeftBB))
        return ScaleFactor(32);
      if (RF_XX(weakKing) == FILE_F && !(PP_BB_WK(ADVISOR) & RightBB))
        return ScaleFactor(32);
    }

  return sf;
}
