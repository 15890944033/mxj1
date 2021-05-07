
#include "../pch.h"

template<>
ScaleFactor Endgame<KPPKP>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongPawn1 = lsb(pos.pieces(strongSide, PAWN));
  Square strongPawn2 = msb(pos.pieces(strongSide, PAWN));
  Square weakKing = pos.square<KING>(weakSide);
  Square weakPawn = pos.square<PAWN>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  Bitboard b = PP_BB_ST(PAWN), bb = NoSquares;
  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  bb = RankBB[RR_WK(RANK_0)];
  bb |= RankBB[RR_WK(RANK_1)];
  bb |= RankBB[RR_WK(RANK_2)];

  if (weakAdvisors + weakBishops == 4)
    return ScaleFactor(8);

  // fen 5k3/4a1P2/3a2P2/9/6b2/9/9/3KBA3/2p1A4/9 w - - 0 1
  if (weakAdvisors == 2)
    if (popcount(bb & PP_BB_ST(PAWN)) == 2)
    {
      if (RF_XX(weakKing) == FILE_F && !(PP_BB_WK(ADVISOR) & RightBB))
        return ScaleFactor(8);
      if (RF_XX(weakKing) == FILE_D && !(PP_BB_WK(ADVISOR) & LeftBB))
        return ScaleFactor(8);
    }

  bb = RankBB[RR_WK(RANK_0)];
  bb |= RankBB[RR_WK(RANK_1)];

  // fen 4k4/2PP5/b8/9/9/2B3B2/9/3A1K3/2p6/9 w - - 0 1
  if (weakBishops >= 1 && RF_XX(weakKing) == FILE_E && RF_XX(weakPawn) != RF_XX(strongKing))
    if (popcount(bb & PP_BB_ST(PAWN)) == 2)
    {
      if (PC_ON_ST(SQ_A7) == MK_PC_WK(BISHOP) && !(PP_BB_ST(PAWN) & (FileGBB | FileHBB | FileIBB)))
        return ScaleFactor(8);
      if (PC_ON_ST(SQ_I7) == MK_PC_WK(BISHOP) && !(PP_BB_ST(PAWN) & (LeftBB | FileEBB)))
        return ScaleFactor(8);
    }

  bb = RankBB[RR_WK(RANK_0)];

  // fen 3ak4/3PaP3/9/9/9/6B2/9/3A1A3/5K3/7p1 b - - 0 1
  if (weakAdvisors == 2)
    if (RR_WK(weakPawn) == RR_ST(RANK_0))
      if (abs(RF_XX(weakPawn) - FILE_E) >= 3)
        if (PC_ON_ST(SQ_E9) == MK_PC_WK(KING))
          if (!(PP_BB_ST(PAWN) & bb))
            if (not_z(PP_BB_ST(PAWN) & LeftBB)
              && not_z(PP_BB_ST(PAWN) & RightBB))
              return ScaleFactor(8);

  if (weakAdvisors == 2)
    return ScaleFactor(8);

  // fen 3P5/9/4k4/8p/9/8P/9/4BA3/3K5/2B2A3 b - - 122 122
  if (popcount(bb & PP_BB_ST(PAWN)) >= 1)
    return ScaleFactor(8);

  // fen 4k4/9/4b4/7P1/p8/9/P8/4B3B/4A4/3A1K3 w - - 0 1
  if (weakBishops >= 1)
  {
    if (PC_ON_ST(SQ_A3) == MK_PC_ST(PAWN) && PC_ON_ST(SQ_A5) == MK_PC_WK(PAWN))
      if (PC_ON_ST(SQ_B5) != MK_PC_ST(PAWN))
        return ScaleFactor(8);
    if (PC_ON_ST(SQ_I3) == MK_PC_ST(PAWN) && PC_ON_ST(SQ_I5) == MK_PC_WK(PAWN))
      if (PC_ON_ST(SQ_H5) != MK_PC_ST(PAWN))
        return ScaleFactor(8);
  }

  // fen 4k4/9/b2a1a3/p8/9/P8/9/3K5/5p3/5A3 w - - 0 1
  if (weakAdvisors >= 1 && RR_WK(weakKing) >= RANK_1)
    if ((RF_XX(weakKing) == FILE_F && PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR))
      || (RF_XX(weakKing) == FILE_D && PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR)))
      ;
    else
    {
      if (RR_WK(strongPawn1) >= RANK_1)
        return ScaleFactor(8);
      if (RR_WK(strongPawn2) >= RANK_1)
        return ScaleFactor(8);
    }

  // fen 3k5/2P1a1P2/9/9/9/9/9/5A3/4K4/2p6 w - - 0 1
  if (weakAdvisors >= 1)
    if (RR_WK(strongPawn1) >= RANK_1 && RR_WK(strongPawn2) >= RANK_1)
    {
      if (RF_XX(weakKing) == FILE_D && PC_ON_ST(SQ_D7) != MK_PC_WK(ADVISOR))
      {
        if (RF_XX(strongPawn1) <= FILE_D && RF_XX(strongPawn2) >= FILE_F)
          return ScaleFactor(8);
        if (RF_XX(strongPawn2) <= FILE_D && RF_XX(strongPawn1) >= FILE_F)
          return ScaleFactor(8);
      }

      if (RF_XX(weakKing) == FILE_F && PC_ON_ST(SQ_F7) != MK_PC_WK(ADVISOR))
      {
        if (RF_XX(strongPawn1) >= FILE_F && RF_XX(strongPawn2) <= FILE_D)
          return ScaleFactor(8);
        if (RF_XX(strongPawn2) >= FILE_F && RF_XX(strongPawn1) <= FILE_D)
          return ScaleFactor(8);
      }
    }

  bb = RankBB[RR_WK(RANK_0)];
  bb |= RankBB[RR_WK(RANK_1)];

  // fen 9/3P5/3P1k3/9/6b2/9/9/4K4/5p3/2BA2B2 w - - 0 1
  if (weakBishops >= 1 && RR_WK(weakKing) == RANK_2)
    if (!(PP_BB_ST(PAWN) & bb) && not_z(PP_BB_ST(PAWN) & RankBB[RR_WK(RANK_0)]))
    {
      if (!(RightBB & PP_BB_ST(PAWN)) && RF_XX(weakKing) >= FILE_E)
        return ScaleFactor(8);
      if (!(LeftBB & PP_BB_ST(PAWN)) && RF_XX(weakKing) <= FILE_E)
        return ScaleFactor(8);
    }

  bb = NoSquares;
  for (Rank r = RANK_0; r > RR_WK(Rank(rank_of(weakKing) + 1)); r--)
    bb |= RankBB[RR_WK(r)];

  // fen 2b6/P4k3/2P6/9/9/9/9/9/4p4/3K5 b - - 120 120
  if (weakBishops != 0 && strongAdvisors == 0)
    if (RR_WK(weakPawn) < RANK_4 && RR_WK(weakPawn) < RR_WK(strongKing))
      if (RF_XX(weakPawn) == FILE_E)
        if (popcount(PP_BB_ST(PAWN) & bb) >= 1)
          return ScaleFactor(8);

  bb = RankBB[RR_WK(RANK_0)];
  bb |= RankBB[RR_WK(RANK_1)];
  bb |= RankBB[RR_WK(RANK_2)];
  bb |= RankBB[RR_WK(RANK_3)];

  // fen 2b6/P4k3/2P6/9/9/9/9/9/4p4/3K5 b - - 120 120
  if (weakBishops >= 1)
    if (not_z(PP_BB_ST(PAWN) & bb))
    {
      if (PC_ON_ST(SQ_D5) == MK_PC_WK(PAWN) && PC_ON_ST(SQ_C3) == MK_PC_ST(PAWN))
        return ScaleFactor(8);
      if (PC_ON_ST(SQ_G5) == MK_PC_WK(PAWN) && PC_ON_ST(SQ_G3) == MK_PC_ST(PAWN))
        return ScaleFactor(8);
    }

  bb = NoSquares;
  for (Rank r = RANK_0; r > RR_WK(Rank(rank_of(weakKing))); r--)
    bb |= RankBB[RR_WK(r)];

  // fen 9/4P4/3k4b/9/8p/9/8P/4K3B/9/9 b - - 0 1
  if (weakBishops >= 1)
    if (not_z(PP_BB_ST(PAWN) & bb))
      return ScaleFactor(8);

  // fen 4ka3/5PP2/b7b/9/9/9/9/4BA3/3KA4/4p1B2 w - - 0 1
  if (weakAdvisors >= 1 && weakBishops == 2)
    if (RR_WK(strongPawn1) >= RANK_1 && RR_WK(strongPawn2) >= RANK_1)
    {
      if (RF_XX(strongPawn1) > FILE_E && RF_XX(strongPawn2) > FILE_E
        && PC_ON_ST(SQ_I7) == MK_PC_WK(BISHOP))
      {
        if (PC_ON_ST(SQ_E9) == MK_PC_WK(KING) && PC_ON_ST(SQ_E8) != MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
        if (file_of(weakKing) == FILE_D && PC_ON_ST(SQ_D7) != MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
      }

      if (RF_XX(strongPawn1) < FILE_E && RF_XX(strongPawn2) < FILE_E
        && PC_ON_ST(SQ_A7) == MK_PC_WK(BISHOP))
      {
        if (PC_ON_ST(SQ_E9) == MK_PC_WK(KING) && PC_ON_ST(SQ_E8) != MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
        if (file_of(weakKing) == FILE_F && PC_ON_ST(SQ_F7) != MK_PC_WK(ADVISOR))
          return ScaleFactor(8);
      }
    }

  bb = RankBB[RR_WK(RANK_0)];
  bb |= RankBB[RR_WK(RANK_1)];

  // fen 4k4/3P5/9/9/2b6/7p1/6P2/5K2B/9/3A5 b - - 120 120
  if (weakBishops != 0)
    if (RR_WK(weakPawn) < RANK_4)
      if (popcount(PP_BB_ST(PAWN) & bb) >= 1)
        return ScaleFactor(8);

  // fen 4k4/9/3aba3/4P4/9/6B2/9/B2p1p3/4K4/9 w - - 120 120
  if (weakBishops == 2 && RR_WK(weakKing) <= RANK_1)
    if (RR_WK(weakPawn) == RANK_5 || RR_WK(weakPawn) == RANK_6)
      if (abs(RF_XX(weakPawn) - FILE_E) <= 1)
        return ScaleFactor(8);

  // fen 4k4/3Pa4/b8/6P2/9/4p4/9/5A3/9/3AK4 w - - 0 0
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (RR_WK(weakKing) == RANK_0)
      if (RR_WK(weakPawn) == RANK_5 || RR_WK(weakPawn) == RANK_6)
        if (RF_XX(weakPawn) == RF_XX(strongKing))
          return ScaleFactor(8);

  // fen 2bak4/4a2P1/4b4/9/9/6B2/9/9/1p2A1p2/4K1B2 b - - 0 0
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (RR_WK(weakKing) == RANK_0)
      if (!EQ_FLK_WK(strongPawn1, strongPawn2))
        if (RR_WK(strongPawn1) >= RANK_1 || RR_WK(strongPawn2) >= RANK_1)
        {
          if (abs(RF_XX(strongPawn1) - FILE_E) >= 2 && abs(RF_XX(strongPawn2) - FILE_E) >= 2)
            return ScaleFactor(8);
          if (RF_XX(weakKing) == FILE_D && PC_ON_ST(SQ_D7) != MK_PC_WK(ADVISOR))
            return ScaleFactor(8);
          if (RF_XX(weakKing) == FILE_F && PC_ON_ST(SQ_F7) != MK_PC_WK(ADVISOR))
            return ScaleFactor(8);
        }

  bb = RankBB[RR_WK(RANK_0)];

  // fen 4k4/3P1P3/b4a2b/9/9/9/9/4BK3/3p5/3A5 w - - 0 1
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (!(PP_BB_ST(PAWN) & bb))
      if (!EQ_FLK_WK(strongPawn1, strongPawn2) && RF_XX(weakKing) == FILE_E && RR_WK(weakPawn) != RANK_9)
      {
        if (PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR) && RF_XX(weakKing) != FILE_D)
          if (RF_XX(weakPawn) == FILE_D)
            return ScaleFactor(8);
        if (PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR) && RF_XX(weakKing) != FILE_F)
          if (RF_XX(weakPawn) == FILE_F)
            return ScaleFactor(8);
      }

  // fen 9/3k1P3/2P6/9/6b2/6B2/3p5/9/4A4/3K1AB2 b - - 0 1
  if (RR_WK(weakPawn) == RANK_6 && abs(RF_XX(weakPawn) - FILE_E) <= 2)
    if (weakBishops >= 1 && RR_WK(strongPawn1) >= RANK_2 && RR_WK(strongPawn2) >= RANK_2)
      if (RR_WK(weakKing) != RANK_0 && !EQ_FLK_WK(strongPawn1, strongPawn2))
        if (RR_WK(strongPawn1) >= RANK_1 || RR_WK(strongPawn2) >= RANK_1)
          return ScaleFactor(8);

  bb = RankBB[RR_WK(RANK_0)];
  bb |= RankBB[RR_WK(RANK_1)];

  // fen 5k3/4a1P2/4b4/3P5/9/6B2/9/4K4/5p3/9 b - - 0 1
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (RR_WK(weakKing) == RANK_0)
    {
      if (RF_XX(weakKing) == FILE_F && not_z((PP_BB_ST(PAWN) & bb) & RightBB))
        return ScaleFactor(8);
      if (RF_XX(weakKing) == FILE_D && not_z((PP_BB_ST(PAWN) & bb) & LeftBB))
        return ScaleFactor(8);
    }

  // fen 9/3Pak3/9/5P3/2b6/9/9/4B4/3K5/4p4 w - - 0 1
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (RR_WK(weakPawn) <= RANK_5)
      if (RR_WK(weakKing) != RANK_0)
      {
        if (RF_XX(weakKing) == FILE_F)
          if (not_z(PP_BB_ST(PAWN) & (LeftBB & bb)))
            return ScaleFactor(8);
        if (RF_XX(weakKing) == FILE_D)
          if (not_z(PP_BB_ST(PAWN) & (RightBB & bb)))
            return ScaleFactor(8);
      }

  bb = RankBB[RR_WK(RANK_0)];

  // fen 4k4/2PPa4/4b4/9/9/2B6/9/4BK3/4A4/p4A3 b - - 0 1
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if ((RR_WK(weakPawn) <= RANK_5) ||
      (RR_WK(weakPawn) == RANK_9 && abs(RF_XX(weakPawn) - FILE_E) >= 3))
      if (!(PP_BB_ST(PAWN) & bb))
      {
        if (RF_XX(strongPawn1) < FILE_E && RF_XX(strongPawn2) < FILE_E)
          return ScaleFactor(8);
        if (RF_XX(strongPawn1) > FILE_E && RF_XX(strongPawn2) > FILE_E)
          return ScaleFactor(8);
      }

  for (Rank r = RANK_0; r > RR_WK(rank_of(weakKing)); r--)
    bb |= RankBB[RR_WK(r)];

  // fen 9/4P4/2P2k3/9/6b2/9/9/4BA3/4p4/5K3 b - - 0 1
  if ((weakAdvisors >= 1 && RR_ST(strongKing) == RANK_0 && PC_ON_WK(SQ_E8) == MK_PC_WK(PAWN))
    || (RR_WK(weakPawn) == RANK_6))
    if (weakBishops >= 1)
      switch (popcount(PP_BB_ST(PAWN) & bb))
      {
      case 2:
      return ScaleFactor(8);
      case 1:
      if (RR_WK(weakKing) == RANK_2)
      {
        bb = RankBB[RR_WK(RANK_0)];
        bb |= RankBB[RR_WK(RANK_1)];
        bb = PP_BB_ST(PAWN) & bb;

        if (not_z(bb))
          if (EQ_FLK_WK(pop_lsb(bb), weakKing))
            return ScaleFactor(16);
      }
      default:
      break;
      }

  bb = RankBB[RR_WK(RANK_0)];
  bb |= RankBB[RR_WK(RANK_1)];
  bb |= RankBB[RR_WK(RANK_2)];

  // fen 3a5/5k3/4P4/9/p8/9/P8/3A1A3/9/3K5 w - - 0 1
  if (weakAdvisors >= 1)
  {
    if (RF_XX(weakKing) == FILE_F && PC_ON_WK(SQ_D9) == MK_PC_WK(ADVISOR))
      return ScaleFactor(16);
    if (RF_XX(weakKing) == FILE_D && PC_ON_WK(SQ_F9) == MK_PC_WK(ADVISOR))
      return ScaleFactor(16);
    if (RF_XX(weakKing) == FILE_D && !((LeftBB | FileEBB | FileFBB) & (PP_BB_ST(PAWN) & bb)))
      return ScaleFactor(16);
    if (RF_XX(weakKing) == FILE_F && !((FileHBB | FileIBB) & (PP_BB_ST(PAWN) & bb)))
      return ScaleFactor(16);
  }

  // fen 2bk1ab2/2P6/9/6P2/9/9/9/4Bp3/4K4/3A5 w - - 0 125
  if (weakAdvisors >= 1 && weakBishops == 2)
    if (RR_WK(weakPawn) < RR_WK(strongKing))
    {
      if (RR_WK(weakKing) != RANK_0 && EQ_FLK_WK(strongPawn1, strongPawn2))
      {
        // fen 2bk1ab2/2P6/9/6P2/9/9/9/4Bp3/4K4/3A5 w - - 0 125
        if (RR_WK(strongPawn1) >= RANK_1 && RR_WK(strongPawn2) >= RANK_2)
        {
          if (RF_XX(strongPawn1) > FILE_E && PC_ON_WK(SQ_D7) == MK_PC_WK(ADVISOR))
            return ScaleFactor(8);
          if (RF_XX(strongPawn1) < FILE_E && PC_ON_WK(SQ_F7) == MK_PC_WK(ADVISOR))
            return ScaleFactor(8);
        }

        if (RR_WK(strongPawn2) >= RANK_1 && RR_WK(strongPawn1) >= RANK_2)
        {
          if (RF_XX(strongPawn2) > FILE_E && PC_ON_WK(SQ_D7) == MK_PC_WK(ADVISOR))
            return ScaleFactor(8);
          if (RF_XX(strongPawn2) < FILE_E && PC_ON_WK(SQ_F7) == MK_PC_WK(ADVISOR))
            return ScaleFactor(8);
        }
      }

      if (RF_XX(weakKing) != FILE_E)
      {
        if (RF_XX(weakKing) == FILE_D && PC_ON_WK(SQ_D7) != MK_PC_WK(ADVISOR))
          return ScaleFactor(16);
        if (RF_XX(weakKing) == FILE_F && PC_ON_WK(SQ_F7) != MK_PC_WK(ADVISOR))
          return ScaleFactor(16);
      }
    }

  if (weakBishops == 2)
    return ScaleFactor(16);

  bb = RankBB[RR_WK(RANK_0)];
  bb |= RankBB[RR_WK(RANK_1)];

  // fen 4ka3/9/8b/3P2P2/9/9/3p5/5A3/4A4/4K4 r
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (RR_WK(weakPawn) == RANK_6 && abs(RF_XX(weakPawn) - FILE_E) <= 1)
      if (!(PP_BB_ST(PAWN) & bb))
        return ScaleFactor(16);

  // fen 9/3Pak3/4b4/6P2/2b6/9/9/B2AK4/3pA4/6B2 b - - 0 1
  if (weakAdvisors >= 1 && weakBishops == 2)
    if (RR_WK(weakPawn) <= RANK_5)
    {
      if (RR_WK(strongPawn1) >= RANK_1)
      {
        if (RF_XX(strongPawn1) > FILE_E && RF_XX(weakKing) < FILE_E)
          if (PC_ON_ST(SQ_D7) != MK_PC_WK(ADVISOR))
            return ScaleFactor(16);
        if (RF_XX(strongPawn1) < FILE_E && RF_XX(weakKing) > FILE_E)
          if (PC_ON_ST(SQ_F7) != MK_PC_WK(ADVISOR))
            return ScaleFactor(16);
      }

      if (RR_WK(strongPawn2) >= RANK_1)
      {
        if (RF_XX(strongPawn2) > FILE_E && RF_XX(weakKing) < FILE_E)
          if (PC_ON_ST(SQ_D7) != MK_PC_WK(ADVISOR))
            return ScaleFactor(16);
        if (RF_XX(strongPawn2) < FILE_E && RF_XX(weakKing) > FILE_E)
          if (PC_ON_ST(SQ_F7) != MK_PC_WK(ADVISOR))
            return ScaleFactor(16);
      }
    }

  // fen 4P4/9/4k4/9/9/9/9/B1p3p2/4A4/3K5 b - - 0 1
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (RR_WK(weakPawn) <= RANK_5)
      if (RR_WK(strongPawn1) >= RANK_2 && RR_WK(strongPawn2) >= RANK_2)
        if (abs(RF_XX(strongPawn1) - FILE_E) >= 2 && abs(RF_XX(strongPawn2) - FILE_E) >= 2)
          if (RF_XX(weakKing) != FILE_E && !(PP_BB_WK(ADVISOR) & FileBB[RF_XX(weakKing)]))
            return ScaleFactor(16);

  // fen 3k5/5P3/3a1P3/9/6b2/2B6/9/B3K4/2p1A4/9 w - - 0 95
  if (weakAdvisors >= 1 && weakBishops >= 1)
  {
    if (RR_WK(strongPawn1) >= RANK_2 && RR_WK(strongPawn2) >= RANK_2)
      if (EQ_FLK_WK(strongPawn1, strongPawn2))
        return ScaleFactor(16);
    return ScaleFactor(32);
  }

  return sf;
}
