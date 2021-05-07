
#include "../pch.h"


template<>
ScaleFactor Endgame<KNPKP>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongPawn = pos.square<PAWN>(strongSide);
  Square strongKnight = pos.square<KNIGHT>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);
  Square weakPawn = pos.square<PAWN>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  Bitboard b = PP_BB_ST(PAWN), bb = NoSquares;
  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  // fen 2b1k4/4aP3/3a5/9/2bN5/9/3p5/B8/9/3AKA3 b - - 0 1
  if (weakAdvisors == 2 && weakBishops == 2)
    if (RR_WK(weakKing) == RANK_0)
      if (RR_WK(weakPawn) == RANK_6)
        sf = ScaleFactor(8);
      else
        sf = ScaleFactor(16);

  // fen 3k5/4a4/5aP2/9/4N1b2/9/9/3AB4/3p5/3A1K3 w - - 0 1
  if (RF_XX(weakPawn) != RANK_9)
    sf = ScaleFactor(8);

  if (RR_WK(weakPawn) == RANK_9 && strongBishops >= 1)
    if (abs(RF_XX(weakPawn) - FILE_E) <= 1)
      sf = ScaleFactor(8);

  // fen 2b1k1b2/4a4/3a5/3P1N3/6p2/9/9/B3B4/3KA4/5A3 b - - 0 1
  if (weakAdvisors == 2 && weakBishops == 2)
    if (RR_WK(weakKing) == RANK_0)
      if (RR_WK(strongPawn) >= RANK_3)
        sf = ScaleFactor(8);

  if (RR_WK(strongPawn) == RANK_0)
    return ScaleFactor(8);
  if (RR_WK(strongKing) <= RR_WK(weakPawn))
    sf = ScaleFactor(16);
  if (abs(RF_XX(weakPawn) - FILE_E) >= 3)
    sf = ScaleFactor(8);

  // fen 3k5/3N3P1/4ba3/9/9/6B2/9/9/3K5/4p4 b - - 0 1
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (RR_WK(strongKnight) >= RANK_2 && RR_WK(strongPawn) >= RANK_1)
      if (!EQ_FLK_WK(strongKnight, strongPawn))
        if (RR_WK(strongKnight) - 1 == RR_WK(weakKing) && RF_XX(strongKnight) == RF_XX(weakKing))
          return ScaleFactor(8);

  // fen 4k4/4a4/4NaP2/9/9/9/9/3A5/4A1p2/5K3 w - - 47 47
  if (weakAdvisors == 2 && RR_WK(weakPawn) <= RANK_5 && RR_WK(weakPawn) != RANK_9)
    if (RR_WK(strongPawn) >= RANK_2)
    {
      if (RF_XX(strongPawn) > FILE_E && PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR) && RF_XX(weakKing) <= FILE_E)
        return ScaleFactor(8);
      if (RF_XX(strongPawn) < FILE_E && PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR) && RF_XX(weakKing) >= FILE_E)
        return ScaleFactor(8);
    }

  // fen 4k4/3Pa4/5a3/9/2b1N4/9/4p4/4B4/4A4/2B2K3 b - - 0 1
  if (weakAdvisors == 2 && weakBishops >= 1)
    if (RR_WK(weakKing) == RANK_0 && RR_WK(weakPawn) == RANK_6)
      if (abs(RF_XX(weakPawn) - FILE_E) <= 1)
        return ScaleFactor(8);

  // fen 5k3/3P1N3/3a5/9/2b3b2/9/9/4B4/3pAK3/3A2B2 w - - 0 1
  if (weakAdvisors >= 1 && weakBishops == 2)
    if (RR_WK(strongPawn) >= RANK_1)
    {
      if (RF_XX(strongPawn) > FILE_E && PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR)
        && PC_ON_ST(SQ_F9) == MK_PC_WK(KING) && PC_ON_ST(SQ_F8) == MK_PC_WK(KNIGHT))
        return ScaleFactor(8);
      if (RF_XX(strongPawn) < FILE_E && PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR)
        && PC_ON_ST(SQ_F9) == MK_PC_WK(KING) && PC_ON_ST(SQ_F8) == MK_PC_WK(KNIGHT))
        return ScaleFactor(8);
    }

  // fen 3k2b2/9/3a4b/2N6/9/2B3P2/9/3AB4/3p5/4KA3 b - - 0 1
  if (weakBishops == 2)
    if (RR_WK(weakKing) >= RANK_1)
      if (RR_WK(weakPawn) <= RANK_5)
        return ScaleFactor(8);

  // fen 3a5/3k1P3/9/6N2/9/9/3p5/9/9/4K4 w - - 0 0
  if (weakAdvisors >= 0)
    if (RR_WK(strongPawn) > RANK_2)
    {
      if (RF_XX(strongPawn) > FILE_E && PC_ON_ST(SQ_D9) == MK_PC_WK(ADVISOR)
        && RF_XX(weakKing) == FILE_D)
        return ScaleFactor(8);
      if (RF_XX(strongPawn) < FILE_E && PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR)
        && RF_XX(weakKing) == FILE_F)
        return ScaleFactor(8);
    }

  // fen 5k3/4a4/2Pa5/6N2/6b2/9/9/3AK4/4A4/7p1 w - - 0 1
  if (weakAdvisors == 2 && weakBishops >= 1)
    if (RR_WK(weakPawn) == RANK_9 && abs(RF_XX(weakPawn) - FILE_E) >= 2)
      if (RR_WK(strongPawn) >= RANK_2)
      {
        if (RF_XX(weakKing) == FILE_F && RF_XX(strongPawn) <= FILE_D
          && !(PP_BB_WK(ADVISOR) & RightBB))
          return ScaleFactor(8);
        if (RF_XX(weakKing) == FILE_D && RF_XX(strongPawn) >= FILE_F
          && !(PP_BB_WK(ADVISOR) & LeftBB))
          return ScaleFactor(8);
      }

  // fen 4k4/4aP3/3a5/9/9/9/9/2n1p4/3KA4/5A3 w - - 127 127
  if (weakAdvisors == 2)
    if (PC_ON_ST(SQ_E7) == MK_PC_ST(PAWN) && PC_ON_ST(SQ_E8) == MK_PC_WK(ADVISOR))
    {
      if (RF_XX(strongKing) == FILE_D && PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR))
        ;
      else if (RF_XX(strongKing) == FILE_F && PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR))
        ;
      else
        return ScaleFactor(8);
    }

  // fen 9/3k1P3/3N1a3/9/9/9/9/B4A2B/1p7/3K1A3 w - - 1 1
  if (RR_WK(strongPawn) >= RANK_1)
  {
    if (PC_ON_ST(SQ_D8) == MK_PC_WK(KING) && PC_ON_ST(SQ_D7) == MK_PC_ST(KNIGHT))
      if (RF_XX(strongPawn) > FILE_E)
        return ScaleFactor(8);
    if (PC_ON_ST(SQ_F8) == MK_PC_WK(KING) && PC_ON_ST(SQ_F7) == MK_PC_ST(KNIGHT))
      if (RF_XX(strongPawn) < FILE_E)
        return ScaleFactor(8);
  }

  // fen 2ba1k3/4a4/2P5b/3N5/9/2B3B2/9/5A3/4K4/3A2p2 w - - 0 1
  if (weakAdvisors == 2 && weakBishops == 2)
    if (RR_WK(weakKing) >= RANK_1 && RR_WK(strongPawn) >= RANK_2)
    {
      if (RF_XX(strongPawn) < FILE_E && RF_XX(weakKing) > FILE_E && !(PP_BB_WK(ADVISOR) & RightBB))
        return ScaleFactor(8);
      if (RF_XX(strongPawn) > FILE_E && RF_XX(weakKing) < FILE_E && !(PP_BB_WK(ADVISOR) & LeftBB))
        return ScaleFactor(8);
    }

  if (weakAdvisors >= 1 && weakBishops == 2)
    if (RR_WK(weakPawn) <= RANK_5 && RR_WK(strongPawn) >= RANK_1)
      if (PC_ON_ST(SQ_E7) == MK_PC_WK(BISHOP))
      {
        // fen 5a3/5P3/3kb4/2N6/2b6/2B6/9/3AK4/5p3/6B2 b - - 0 1
        if (RF_XX(strongPawn) >= FILE_F && (PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR) || PC_ON_ST(SQ_E8) == MK_PC_ST(ADVISOR)))
          if (!(knight_attacks_bb(strongKnight, pos.pieces()) & SquareBB[RS_ST(SQ_E8)]))
            return ScaleFactor(8);
        if (RF_XX(strongPawn) <= FILE_D && (PC_ON_ST(SQ_D9) == MK_PC_WK(ADVISOR) || PC_ON_ST(SQ_E8) == MK_PC_ST(ADVISOR)))
          if (!(knight_attacks_bb(strongKnight, pos.pieces()) & SquareBB[RS_ST(SQ_E8)]))
            return ScaleFactor(8);
      }

  if (weakAdvisors == 2 && weakBishops == 2)
  {
    // fen 2b2a3/3ka4/b8/9/9/1NP3B2/9/8B/5p3/3AK4 b - - 120 120
    if (RR_WK(weakPawn) <= RANK_5 && RR_WK(weakKing) >= RANK_1)
      return ScaleFactor(8);

    // fen 4k4/4a4/5a3/2P6/9/9/5n3/2pAB4/4A4/3K2B2 b - - 67 67
    if (RR_WK(weakKing) >= RANK_1)
      if (RR_WK(weakPawn) == RANK_5 || RR_WK(weakPawn) == RANK_6)
        return ScaleFactor(8);
  }

  // fen 3a1k3/4a4/9/6p2/2b3b2/2B3P2/9/2nK5/9/6B2 w - - 128 128
  if (weakBishops == 2)
  {
    if (PC_ON_ST(SQ_C3) == MK_PC_ST(PAWN) && PC_ON_ST(SQ_E3) == MK_PC_WK(PAWN))
      return ScaleFactor(8);
    if (PC_ON_ST(SQ_C6) == MK_PC_ST(PAWN) && PC_ON_ST(SQ_E6) == MK_PC_WK(PAWN))
      return ScaleFactor(8);
  }

  // fen 4k1P2/9/4ba3/9/9/9/9/2p6/4A4/3A1K1n1 w - - 0 1
  if (weakAdvisors == 2)
    if (RR_WK(weakPawn) <= RANK_4 && RR_WK(weakPawn) != RANK_9)
      if (RR_WK(strongPawn) >= RANK_2)
      {
        if (RF_XX(strongPawn) > FILE_E && PC_ON_ST(SQ_D7) != MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
        if (RF_XX(strongPawn) < FILE_E && PC_ON_ST(SQ_F7) != MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
      }

  // fen 3a1k1P1/9/3a4b/9/9/9/3n5/4pA3/3KA4/9 w - - 0 1
  if (weakAdvisors == 2)
    if (RR_WK(weakPawn) <= RANK_5 && PC_ON_ST(SQ_E7) == MK_PC_ST(PAWN))
      if (RR_WK(weakPawn) == RANK_9 && abs(RF_XX(weakPawn) - FILE_E) <= 1)
        ;
      else
      {
        if (RF_XX(weakKing) == FILE_D && PC_ON_ST(SQ_D9) != MK_PC_WK(ADVISOR) && PC_ON_ST(SQ_D7) != MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
        if (RF_XX(weakKing) == FILE_F && PC_ON_ST(SQ_F9) != MK_PC_WK(ADVISOR) && PC_ON_ST(SQ_F7) != MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
      }

  // fen 3k5/5P3/9/9/9/9/9/3A5/5p3/n3KA3 w - - 0 0
  if (weakAdvisors == 2)
    if (RR_WK(weakPawn) <= RANK_5 && RF_XX(weakPawn) != RANK_9)
    {
      if (RF_XX(strongPawn) > FILE_E && PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR) && PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR))
        return ScaleFactor(8);
      if (RF_XX(strongPawn) < FILE_E && PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR) && PC_ON_ST(SQ_D9) == MK_PC_WK(ADVISOR))
        return ScaleFactor(8);
      // fen 3k5/5P3/9/9/9/9/9/3A5/5p3/n3KA3 w - - 0 0
      if (RR_WK(strongPawn) >= RANK_2)
      {
        if (RF_XX(weakKing) < FILE_E && RF_XX(strongPawn) > FILE_E && PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
        if (RF_XX(weakKing) > FILE_E && RF_XX(strongPawn) > FILE_E && PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
      }
    }

  if ((RF_XX(weakKing) == FILE_D && PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR))
    || (RF_XX(weakKing) == FILE_F && PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR)))
    if (RR_WK(strongPawn) != RANK_0)
      sf += ScaleFactor(2);

  // fen 9/4k1P2/5a3/9/9/9/9/3K2p2/4A4/1n3AB2 b - - 0 1
  if (weakAdvisors == 2)
    if (RR_WK(strongPawn) >= RANK_2)
      if (RR_WK(weakPawn) <= RANK_5 && !EQ_FLK_WK(weakKing, strongPawn))
      {
        if (RF_XX(weakKing) == FILE_D && PC_ON_ST(SQ_D7) != MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
        if (RF_XX(weakKing) == FILE_F && PC_ON_ST(SQ_F7) != MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
      }

  // fen 9/3k1P3/3a5/9/2b1N1b2/9/3p5/5A3/9/3K1AB2 w - - 0 1
  if (weakAdvisors >= 1 && weakBishops == 2)
    if (RR_WK(strongPawn) >= RANK_1 && RR_WK(weakPawn) == RANK_6)
      if (RR_WK(weakKing) >= RANK_1)
      {
        if (RF_XX(weakKing) == FILE_D && RF_XX(weakPawn) == FILE_D && RF_XX(strongPawn) >= FILE_F)
          return ScaleFactor(8);
        if (RF_XX(weakKing) == FILE_F && RF_XX(weakPawn) == FILE_F && RF_XX(strongPawn) <= FILE_D)
          return ScaleFactor(8);
      }

  // fen 3k1a3/5P3/N2a4b/9/2p3b2/6B2/9/B4A3/3K5/5A3 b - - 0 1
  if (weakAdvisors == 2 && weakBishops == 2)
    if (RR_WK(weakKing) >= RANK_1 && RR_WK(strongPawn) >= RANK_1)
    {
      if (RF_XX(strongPawn) > FILE_E && PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR))
        return ScaleFactor(8);
      if (RF_XX(strongPawn) < FILE_E && PC_ON_ST(SQ_D9) == MK_PC_WK(ADVISOR))
        return ScaleFactor(8);
    }

  if (weakAdvisors >= 1 && weakBishops == 2)
    if (RR_WK(weakPawn) == RANK_6)
    {
      // fen 5ab2/5k3/2P1b4/9/9/9/2N6/9/p8/3AK1B2 b
      if (RR_WK(strongPawn) >= RANK_2 && !EQ_FLK_WK(weakKing, strongPawn))
      {
        if (RF_XX(weakKing) == FILE_D && PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
        if (RF_XX(weakKing) == FILE_F && PC_ON_ST(SQ_D9) == MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
      }

      // fen 4k4/4a4/5a2b/3P5/9/3n5/4p4/4B4/4A4/4K1B2 w - - 120 120
      if (RR_WK(strongPawn) < RANK_2)
        return ScaleFactor(16);
    }

  // fen 4k4/4aP3/3aN4/9/9/9/9/B2K1A3/1p7/3A2B2 w - - 0 1
  if (weakAdvisors == 2)
    if (RR_WK(weakKing) >= RANK_1 && RR_WK(weakPawn) <= RANK_6)
      if (RR_WK(strongPawn) >= RANK_1)
      {
        if (RF_XX(strongPawn) > FILE_E && PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR))
          if (PC_ON_ST(SQ_D9) != MK_PC_WK(ADVISOR) && PC_ON_ST(SQ_F7) != MK_PC_WK(ADVISOR))
            return ScaleFactor(16);
        if (RF_XX(strongPawn) < FILE_E && PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR))
          if (PC_ON_ST(SQ_F9) != MK_PC_WK(ADVISOR) && PC_ON_ST(SQ_D7) != MK_PC_WK(ADVISOR))
            return ScaleFactor(16);
      }

  // fen 2b1k4/4a4/4ba3/6N1p/9/6B1P/9/5A3/4A4/2B1K4 b - - 0 1
  if (weakAdvisors == 2 && weakBishops == 2)
    if (RR_WK(weakKing) >= RANK_1)
      if (PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR) || PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR))
        return ScaleFactor(16);

  // fen 2b2k3/4a4/5a3/9/P3N4/8p/9/9/4A4/3AK4 w - - 0 1
  if (weakAdvisors == 2 && weakBishops >= 1)
    if (RR_WK(weakPawn) == RANK_5 || RR_WK(weakPawn) == RANK_6)
      if (RR_WK(weakKing) >= RANK_1)
        return ScaleFactor(16);

  // fen 2b2k3/4a4/5a3/5P3/9/2B5N/9/4K1p2/4A4/6B2 w - - 0 1
  if (weakAdvisors == 2 && weakBishops >= 1)
  {
    sf -= ScaleFactor(2);
    if (RR_WK(strongPawn) <= RANK_3 && RR_WK(weakKing) >= RANK_1)
      return ScaleFactor(16);
  }

  // fen 4k4/3Pa2N1/4ba3/9/9/9/9/9/2p1K4/2B3B2 b - - 0 1
  if (weakAdvisors == 2 && weakBishops >= 1)
    if (RR_WK(strongPawn) >= RANK_1 && PC_ON_ST(SQ_E7) == MK_PC_WK(BISHOP))
    {
      if (RF_XX(strongPawn) < FILE_E && PC_ON_ST(SQ_H8) == MK_PC_ST(KNIGHT))
        if (PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR))
          return ScaleFactor(16);
      if (RF_XX(strongPawn) > FILE_E && PC_ON_ST(SQ_B8) == MK_PC_ST(KNIGHT))
        if (PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR))
          return ScaleFactor(16);
    }

  b = RankBB[RR_WK(RANK_0)];
  b |= RankBB[RR_WK(RANK_1)];

  // fen 5k3/4a1P2/5a3/9/2bN5/9/9/9/3KA4/6p2 b - - 0 1
  if (weakAdvisors == 2 && weakBishops >= 1)
    if (RR_WK(weakPawn) <= RANK_5)
      if (RR_WK(strongPawn) >= RANK_1)
        if (abs(RF_XX(strongPawn) - FILE_E) >= 2)
          if (not_z(PP_BB_WK(ADVISOR) & b))
            return ScaleFactor(16);

  // fen 9/3ka4/5a3/N4P3/9/6B2/9/5A3/2p1A4/4K1B2 b - - 122 122
  if (weakAdvisors == 2)
    if (RR_WK(weakPawn) != RANK_9 && RR_WK(weakKing) >= RANK_1)
    {
      sf -= ScaleFactor(2);
      if (RR_WK(weakPawn) < RANK_5)
      {
        if (PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR) && RF_XX(weakKing) == FILE_F)
          return ScaleFactor(16);
        if (PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR) && RF_XX(weakKing) == FILE_D)
          return ScaleFactor(16);
        return ScaleFactor(32);
      }
    }

  // fen 3k1a3/4a4/4N4/4P4/9/2B6/2p6/5A3/4AK3/9 b
  if (weakAdvisors == 2)
    if (RR_WK(weakPawn) == RANK_6)
      if (abs(RF_XX(weakPawn) - FILE_E) <= 2)
        return ScaleFactor(32);

  // fen 5k3/4a1P2/5a3/9/2bN5/9/9/9/3KA4/6p2 b - - 0 1
  if (weakAdvisors == 2 && weakBishops >= 1)
    if (RR_WK(weakPawn) <= RANK_5)
      if (RR_WK(strongPawn) >= RANK_1)
        return ScaleFactor(32);

  return sf;
}
