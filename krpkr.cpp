
#include "../pch.h"


template<>
ScaleFactor Endgame<KRPKR>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongPawn = pos.square<PAWN>(strongSide);
  Square strongRook = pos.square<ROOK>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);
  Square weakRook = pos.square<ROOK>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  // fen 4k1b2/4a4/9/5P1R1/2r6/9/9/4B4/4A4/4KAB2 b - - 0 1
  if (weakAdvisors + weakBishops == 4)
    return ScaleFactor(8);

  if (weakAdvisors == 2)
    if (RR_WK(weakKing) == RANK_0 || RR_WK(strongPawn) < RR_WK(weakKing))
      return ScaleFactor(8);

  // fen 2b6/4k4/4b4/1r2P4/9/2B1R4/9/9/9/2BAKA3 w - - 0 1
  if (weakBishops == 2 && RF_XX(weakKing) == FILE_E)
    if (RR_WK(strongPawn) == RR_WK(weakRook) && RF_XX(strongPawn) == RF_XX(strongRook))
      if (RR_WK(strongPawn) < RANK_2 && RF_XX(strongPawn) == FILE_E)
        return ScaleFactor(8);

  if (weakAdvisors >= 1 && weakBishops >= 1)
  {
    // fen 3ak1b2/9/9/9/5r3/2P4R1/9/4B3B/4A4/4KA3 r
    if (RR_WK(weakKing) == RANK_0 && RR_WK(strongPawn) < RANK_4)
      return ScaleFactor(8);

    // fen 4ka3/1P1r5/4b4/9/9/1R7/9/3A5/9/3K5 w - - 26 26
    if (PC_ON_ST(SQ_E9) == MK_PC_WK(KING))
      if (RR_WK(strongRook) > RR_WK(weakRook))
        if ((RF_XX(strongPawn) <= FILE_C && PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR))
          || (RF_XX(strongPawn) >= FILE_G && PC_ON_ST(SQ_D9) == MK_PC_WK(ADVISOR)))
          if (RR_WK(strongPawn) == RR_WK(weakRook) && RF_XX(strongPawn) == RF_XX(strongRook))
            return ScaleFactor(8);

    // fen 3ak4/9/4b4/5P3/9/9/1R7/9/4K4/5r3 w - - 196 196
    if (PC_ON_ST(SQ_E9) == MK_PC_WK(KING))
      if (strongAdvisors == 0 && strongBishops == 0)
        if (RR_WK(strongPawn) <= RANK_3)
          return ScaleFactor(8);
  }

  // fen 3k5/9/9/4R4/9/2B6/9/3A5/1r1K1p3/9 w - - 211 211
  if (weakAdvisors >= 1 && strongAdvisors == 0)
    if (RR_WK(weakRook) < RANK_2 && RR_WK(strongPawn) >= RANK_1)
    {
      if (PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) > FILE_E)
        if (RF_XX(strongRook) != FILE_D)
          if (not_z(rook_attacks_bb(weakRook, pos.bit_mask_x(weakRook), pos.bit_mask_y(weakRook)) & FileDBB))
            return ScaleFactor(8);
      if (PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) < FILE_E)
        if (RF_XX(strongRook) != FILE_F)
          if (not_z(rook_attacks_bb(weakRook, pos.bit_mask_x(weakRook), pos.bit_mask_y(weakRook)) & FileFBB))
            return ScaleFactor(8);
    }

  if (weakAdvisors >= 1 && weakBishops == 2)
    if (RR_WK(weakKing) == RANK_0)
    {
      // fen 2b1k4/9/4b4/9/9/6R2/5r3/4B4/4A2p1/4K1B2 w - - 41 41
      if (RR_WK(strongPawn) != RANK_1 || abs(RF_XX(strongPawn) - FILE_E) > 2)
        return ScaleFactor(8);

      // fen 4k1b2/4a4/4b4/9/5R3/9/9/4B4/6p2/2B1KA2r w - - 121 121
      if (RF_XX(strongPawn) >= FILE_F && RF_XX(strongRook) >= FILE_G)
        if (PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR) && RF_XX(weakRook) == FILE_F)
          return ScaleFactor(8);
      if (RF_XX(strongPawn) <= FILE_D && RF_XX(strongRook) <= FILE_C)
        if (PC_ON_ST(SQ_C9) == MK_PC_WK(ADVISOR) && RF_XX(weakRook) == FILE_D)
          return ScaleFactor(8);

      // fen 3k5/4a4/9/9/2b2r3/9/9/B3B4/4Ap1R1/4K4 w - - 124 124
      if (RR_WK(strongPawn) >= RANK_4 && RR_WK(strongPawn) == RR_WK(weakRook) && RF_XX(strongRook) == RF_XX(strongPawn))
        if (PC_ON_ST(SQ_E8) == MK_PC_WK(ADVISOR) && PC_ON_ST(SQ_E7) == MK_PC_WK(BISHOP))
        {
          if (RF_XX(strongPawn) > FILE_E && RF_XX(weakRook) > RF_XX(strongPawn))
            if (PC_ON_ST(SQ_C9) == MK_PC_WK(BISHOP) || PC_ON_ST(SQ_A7) == MK_PC_WK(BISHOP))
              return ScaleFactor(8);
          if (RF_XX(strongPawn) < FILE_E && RF_XX(weakRook) < RF_XX(strongPawn))
            if (PC_ON_ST(SQ_G9) == MK_PC_WK(BISHOP) || PC_ON_ST(SQ_I7) == MK_PC_WK(BISHOP))
              return ScaleFactor(8);
        }

      // fen 9/4k4/9/9/5R3/9/9/4B4/3p3r1/4KAB2 b - - 186 186
      if (RR_WK(strongPawn) == RANK_1)
      {
        if (RF_XX(strongPawn) < FILE_E && RF_XX(strongRook) > FILE_E)
          if (PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR) && RF_XX(weakRook) == FILE_F)
            return ScaleFactor(8);
        if (RF_XX(strongPawn) > FILE_E && RF_XX(strongRook) < FILE_E)
          if (PC_ON_ST(SQ_D9) == MK_PC_WK(ADVISOR) && RF_XX(weakRook) == FILE_D)
            return ScaleFactor(8);
      }
    }

  if (weakAdvisors >= 1 && weakBishops >= 1)
  {
    // fen 5a3/4k4/5a3/9/9/9/9/5A3/2p3R2/5KBr1 w - - 120
    if (RR_WK(weakKing) == RANK_0)
    {
      if (RR_WK(weakRook) == RANK_1 && RR_WK(strongPawn) == RANK_1)
        if (EQ_FLK_WK(strongRook, weakRook) && !EQ_FLK_WK(weakRook, strongPawn))
        {
          if (PC_ON_ST(SQ_C9) == MK_PC_WK(BISHOP) && RF_XX(weakRook) == FILE_C)
            return ScaleFactor(8);
          if (PC_ON_ST(SQ_G9) == MK_PC_WK(BISHOP) && RF_XX(weakRook) == FILE_G)
            return ScaleFactor(8);
        }

      if (RR_WK(strongPawn) == RANK_0)
        return ScaleFactor(8);
    }
  }

  // fen 3ak4/9/5a3/9/2b3b2/2R6/9/2p6/2r1AK3/9 w - - 130 130
  if (weakAdvisors >= 1)
    if (RF_XX(weakRook) == RF_XX(strongRook) && RF_XX(weakRook) == RF_XX(strongPawn))
      if ((RR_WK(strongPawn) > RR_WK(weakRook) && RR_WK(strongPawn) < RR_WK(strongRook))
        || (RR_WK(strongPawn) < RR_WK(weakRook) && RR_WK(strongPawn) > RR_WK(strongRook)))
        if (popcount(BetweenBB[weakRook][strongRook] & pos.pieces()) == 1)
          if (abs(RF_XX(strongPawn) - RF_XX(weakKing)) >= 2)
            return ScaleFactor(8);

  // fen 4k4/2R6/2P1b4/2r6/9/9/9/4B3B/4A4/3AK4 w - - 0 0
  if (weakBishops >= 1)
    if (RR_WK(strongPawn) >= RANK_2 && abs(RF_XX(strongPawn) - FILE_E) >= 2)
      if (RR_WK(strongPawn) == RR_WK(strongRook) + 1 && RF_XX(strongPawn) == RF_XX(strongRook))
        if (RF_XX(strongRook) == FILE_C || RF_XX(strongRook) == FILE_G)
          if (RF_XX(weakRook) == RF_XX(strongPawn))
            return ScaleFactor(8);

  if (RR_WK(strongPawn) == RANK_0)
  {
    // fen 4k1b2/9/3r5/9/5R3/9/9/5A3/3p5/5K3 b - - 115 115
    if (RR_WK(weakKing) >= RANK_1)
    {
      if (RF_XX(weakKing) <= FILE_E && RF_XX(weakRook) == FILE_D)
        if (PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) > FILE_E)
          return ScaleFactor(8);
      if (RF_XX(weakKing) >= FILE_E && RF_XX(weakRook) == FILE_F)
        if (PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) < FILE_E)
          return ScaleFactor(8);
    }

    // fen 4k1P2/9/4r4/3R5/9/9/9/9/9/3K5 w
    if (RR_WK(weakRook) <= RANK_2 && RF_XX(weakRook) == FILE_E)
      return ScaleFactor(8);

    if (weakAdvisors != 0 || weakBishops != 0)
      if (RR_WK(weakRook) > RR_WK(weakKing))
        if (RF_XX(weakKing) == FILE_E && RF_XX(weakRook) == FILE_E)
          return ScaleFactor(8);

    // fen 9/4k4/4b4/4r4/6b2/1R7/9/3A5/3K5/4p4 w - - 142 142
    if (RR_WK(weakKing) == RANK_1 && RR_WK(weakRook) < RANK_2)
      if (PC_ON_ST(MK_SQ(RF_XX(weakKing), Rank(RR_WK(weakKing) + 1))) == MK_PC_WK(ADVISOR))
        return ScaleFactor(8);
  }

  // fen 3a5/3k1P3/9/9/4R4/3r5/9/9/4A4/4K4 w
  if (((PC_ON_ST(SQ_D8) == MK_PC_WK(KING) || (PC_ON_ST(SQ_D7) == MK_PC_WK(KING) && RR_WK(weakRook) != RANK_0)) && PC_ON_ST(SQ_D9) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) > FILE_E)
    || ((PC_ON_ST(SQ_F8) == MK_PC_WK(KING) || (PC_ON_ST(SQ_F7) == MK_PC_WK(KING) && RR_WK(weakRook) != RANK_0)) && PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) < FILE_E))
    if (RF_XX(weakKing) == RF_XX(weakRook))
      return ScaleFactor(8);

  // fen 5k3/3P5/3a5/3R5/5r3/2B6/9/5A2B/4A4/4K4 b - - 134 134
  if (weakAdvisors >= 1)
    if (RR_WK(weakKing) >= RANK_1 && RF_XX(weakKing) != FILE_E)
    {
      if (PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) <= FILE_E)
        return ScaleFactor(8);
      if (PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) >= FILE_E)
        return ScaleFactor(8);
    }

  if (RR_WK(strongPawn) == RANK_1)
  {
    if (weakAdvisors >= 1)
    {
      // fen 9/3k1P3/3r1a3/9/9/4R4/9/9/4A4/4K4 w
      if (RR_WK(weakKing) >= RANK_1)
      {
        if (RF_XX(weakKing) <= FILE_E)
          if (PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) > FILE_E)
          {
            if (PC_ON_ST(SQ_D7) == MK_PC_WK(ROOK))
              return ScaleFactor(8);
            if (not_z(rook_attacks_bb(weakRook, pos.bit_mask_x(weakRook), pos.bit_mask_y(weakRook)) & SquareBB[RS_ST(SQ_D7)]))
              return ScaleFactor(8);
          }
        if (RF_XX(weakKing) >= FILE_E)
          if (PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) < FILE_E)
          {
            if (PC_ON_ST(SQ_F7) == MK_PC_WK(ROOK))
              return ScaleFactor(8);
            if (not_z(rook_attacks_bb(weakRook, pos.bit_mask_x(weakRook), pos.bit_mask_y(weakRook)) & SquareBB[RS_ST(SQ_D7)]))
              return ScaleFactor(8);
          }

        // fen 4k1b2/9/3r5/9/5R3/9/9/5A3/3p5/5K3 b - - 115 115
        if (strongAdvisors == 0)
        {
          if (RF_XX(weakKing) <= FILE_E)
            if (PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) > FILE_E)
            {
              if (RF_XX(weakRook) == FILE_D)
                return ScaleFactor(8);
            }
          if (RF_XX(weakKing) >= FILE_E)
            if (PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) < FILE_E)
            {
              if (RF_XX(weakRook) == FILE_F)
                return ScaleFactor(8);
            }
        }

        // fen 9/3kaRP2/9/9/3r5/9/9/9/4A4/4K4 w - - 6 6
        if (PC_ON_ST(SQ_E8) == MK_PC_WK(ADVISOR) && RR_WK(strongRook) == RANK_1)
          if (RR_ST(weakRook) <= RR_ST(weakKing) && RF_XX(weakRook) == RF_XX(weakKing))
            return ScaleFactor(8);
      }
    }
  }

  if (strongAdvisors == 0 && strongBishops == 0)
  {
    if (weakBishops >= 1 && RR_WK(strongPawn) <= RANK_1)
    {
      if (RR_WK(weakKing) == RANK_2 && RR_WK(weakRook) > RANK_2 && RF_XX(weakRook) == FILE_E)
      {
        // fen 6b2/5P3/4k4/9/3R5/4r4/9/9/9/5K3 w - - 8 8
        if (abs(RF_XX(strongPawn) - RF_XX(weakKing)) != 1)
          return ScaleFactor(8);
        if (abs(RF_XX(strongRook) - RF_XX(weakKing)) == 1)
          if (RF_XX(strongRook) != RF_XX(strongKing))
            return ScaleFactor(8);
      }

      // fen 9/5P3/3kr3b/9/9/9/5R3/9/9/5K3 b - - 0 1
      if (RF_XX(weakRook) == FILE_E && RR_WK(weakRook) >= RANK_2)
      {
        if (RF_XX(strongKing) == FILE_F)
          if (PC_ON_ST(SQ_G9) == MK_PC_WK(BISHOP) || PC_ON_ST(SQ_I7) == MK_PC_WK(BISHOP))
            return ScaleFactor(8);
        if (RF_XX(strongKing) == FILE_D)
          if (PC_ON_ST(SQ_C9) == MK_PC_WK(BISHOP) || PC_ON_ST(SQ_A7) == MK_PC_WK(BISHOP))
            return ScaleFactor(8);
      }

      // fen 4k1b2/6P2/9/5R3/9/9/4r4/9/9/5K3 w
      if (RF_XX(weakRook) == FILE_E && RR_WK(weakRook) >= RANK_2 && abs(RR_WK(weakRook) - RR_WK(strongKing)) >= 2)
      {
        if (RF_XX(strongRook) > FILE_E)
        {
          if (PC_ON_ST(SQ_G9) == MK_PC_WK(BISHOP))
            if (RF_XX(strongPawn) > FILE_E)
              return ScaleFactor(8);
          if (PC_ON_ST(SQ_I7) == MK_PC_WK(BISHOP))
            if (RF_XX(weakKing) == FILE_F)
              if (abs(RF_XX(strongPawn) - RF_XX(weakKing)) > 1)
                return ScaleFactor(8);
        }
        else
        {
          if (PC_ON_ST(SQ_I7) == MK_PC_WK(BISHOP))
            if (RF_XX(strongPawn) < FILE_E)
              return ScaleFactor(8);
        }

        if (RF_XX(strongRook) < FILE_E)
        {
          if (PC_ON_ST(SQ_C9) == MK_PC_WK(BISHOP))
            if (RF_XX(strongPawn) < FILE_E)
              return ScaleFactor(8);
          if (PC_ON_ST(SQ_A7) == MK_PC_WK(BISHOP))
            if (RF_XX(weakKing) == FILE_D)
              if (abs(RF_XX(strongPawn) - RF_XX(weakKing)) > 1)
                return ScaleFactor(8);
        }
        else
        {
          if (PC_ON_ST(SQ_A7) == MK_PC_WK(BISHOP))
            if (RF_XX(strongPawn) > FILE_E)
              return ScaleFactor(8);
        }
      }
    }
  }

  // fen 3R5/4k4/4b4/9/4r4/6P2/9/4B4/4A4/4KAB2 w - - 1 1
  if (weakBishops >= 1 && PC_ON_ST(SQ_E7) == MK_PC_WK(BISHOP) && strongBishops == 0)
    if (RF_XX(weakRook) == FILE_E)
      return ScaleFactor(8);

  // fen 3akab2/9/9/9/9/9/5R3/B4A3/3p4r/2B2K3 b - - 143 143
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (RR_WK(strongPawn) <= RANK_1)
      if (RR_WK(weakRook) <= RANK_3)
        if (RF_XX(weakRook) == RF_XX(weakKing) && !EQ_FLK_WK(weakKing, strongPawn))
          return ScaleFactor(8);
    
  // fen 4kab2/4a4/4b4/9/4R4/9/9/4p4/4r4/5K3 b - - 123 123
  if (RF_XX(weakRook) == FILE_E && RR_WK(weakKing) == RANK_0)
    if (PC_ON_ST(SQ_E8) == MK_PC_ST(ROOK) && PC_ON_ST(SQ_E7) == MK_PC_ST(PAWN))
      return ScaleFactor(8);

  if (weakAdvisors == 1 && weakBishops == 0)
    if (aligned(weakRook, strongPawn, strongRook))
      return ScaleFactor(8);

  if (weakAdvisors == 0 && weakBishops == 1)
    if (strongAdvisors == 0 && strongBishops == 1)
      return ScaleFactor(8);

  return sf;
}
