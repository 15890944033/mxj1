
#include "../pch.h"

template<>
ScaleFactor Endgame<KRK>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongRook = pos.square<ROOK>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  if (weakAdvisors == 2 && weakBishops == 2)
    return ScaleFactor(8);

  if (RR_ST(weakKing) <= RANK_8)
  {
    Bitboard weakAdvisor = pos.pieces(weakSide, ADVISOR);
    Bitboard weakBishop = pos.pieces(weakSide, BISHOP);

    if (PC_ON_ST(SQ_E7) == MK_PC_WK(BISHOP))
    {
      // fen 4k4/4a4/3ab3b/R8/9/2B6/9/3AB4/5K3/9 b - - 76 76
      if (RS_ST(weakKing) == SQ_E9)
        return ScaleFactor(8);
      if (RS_ST(weakKing) == SQ_D9 && PC_ON_ST(SQ_C9) == MK_PC_WK(BISHOP))
        return ScaleFactor(8);
      if (RS_ST(weakKing) == SQ_F9 && PC_ON_ST(SQ_G9) == MK_PC_WK(BISHOP))
        return ScaleFactor(8);

      // fen 5k3/4a4/4ba3/5R3/6b2/9/9/3AK4/9/2B2AB2 w - - 9 9
      if (RR_WK(weakKing) == RANK_0)
      {
        if (!not_z(rook_attacks_bb(strongRook, pos.bit_mask_x(strongRook), pos.bit_mask_y(strongRook)) & BottomRankBB[weakSide]))
          return ScaleFactor(8);
      }
    }

    if (RR_WK(weakKing) == RANK_0)
    {
      // fen 3a1a3/9/4k4/9/9/9/9/B8/4A4/r1B1KA3 b - - 120 120
      if (PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR))
        if (PC_ON_ST(SQ_C9) == MK_PC_WK(BISHOP) && PC_ON_ST(SQ_A7) == MK_PC_WK(BISHOP))
          return ScaleFactor(8);
      if (PC_ON_ST(SQ_C9) == MK_PC_WK(ADVISOR))
        if (PC_ON_ST(SQ_G9) == MK_PC_WK(BISHOP) && PC_ON_ST(SQ_I7) == MK_PC_WK(BISHOP))
          return ScaleFactor(8);

      // fen 4k4/4a4/5a2b/9/4R1b2/9/9/3AK4/9/2B2AB2 b - - 0 0
      if ((PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR) || PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR)))
        if (abs(RF_XX(strongRook) - FILE_E) <= 1)
        {
          bool unlinked = false;
          if (weakBishops == 2)
            unlinked = not_z(bishop_attacks_bb(lsb(weakBishop), pos.pieces()) & msb(weakBishop));
          if (!unlinked)
            return ScaleFactor(8);
        }
    }

    if (RR_WK(strongRook) == RANK_0)
      if (PC_ON_ST(SQ_E8) == MK_PC_WK(ADVISOR) && PC_ON_ST(SQ_E7) == MK_PC_WK(BISHOP))
      {
        // fen 2baR4/4ak3/4b4/9/9/9/9/9/4K4/9 b - - 105 105
        if (PC_ON_ST(SQ_F8) == MK_PC_WK(KING)
          && PC_ON_ST(SQ_D9) == MK_PC_WK(ADVISOR)
          && RF_XX(strongRook) >= FILE_E)
        {
          if (not_z(PP_BB_WK(BISHOP) & FlankMidBoardBB[0]))
            return ScaleFactor(8);
        }

        if (PC_ON_ST(SQ_D8) == MK_PC_WK(KING)
          && PC_ON_ST(SQ_F9) == MK_PC_WK(ADVISOR)
          && RF_XX(strongRook) <= FILE_E)
        {
          if (not_z(PP_BB_WK(BISHOP) & FlankMidBoardBB[1]))
            return ScaleFactor(8);
        }

        return ScaleFactor(3);
      }

    if (PC_ON_ST(SQ_E8) == MK_PC_WK(ADVISOR) && PC_ON_ST(SQ_E7) == MK_PC_WK(BISHOP))
      if (RR_WK(weakKing) == RANK_0)
      {
        // fen 3a1k3/4a4/4b4/3R5/2b6/9/9/9/4K4/9 b - - 0 0
        if (RF_XX(weakKing) >= FILE_E && RF_XX(strongRook) <= FILE_E)
          return ScaleFactor(8);
        if (RF_XX(weakKing) <= FILE_E && RF_XX(strongRook) >= FILE_E)
          return ScaleFactor(8);
      }

    // fen 2b1kab2/3Ra4/9/9/9/9/9/5A2B/3KA4/6B2 b - - 0 1
    if (weakBishops == 2 && PC_ON_ST(SQ_E8) == MK_PC_WK(ADVISOR)
      && RR_WK(weakKing) == RANK_0)
    {
      if (abs(RF_XX(msb(weakBishop)) - RF_XX(lsb(weakBishop))) <= 4)
        return ScaleFactor(8);
    }

    // fen 4Rab2/5k3/5a2b/9/9/9/9/4B4/4AK3/3A5 w - - 120 120
    if (RR_WK(weakKing) >= RANK_1)
    {
      if (RF_XX(strongRook) == FILE_E)
      {
        if (RF_XX(weakKing) == FILE_F && PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR))
          if (popcount(PP_BB_WK(BISHOP) & FlankMidBoardBB[1]))
            return ScaleFactor(8);
        if (RF_XX(weakKing) == FILE_D && PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR))
          if (popcount(PP_BB_WK(BISHOP) & FlankMidBoardBB[0]))
            return ScaleFactor(8);
      }

      // fen 3a5/4a4/4k4/9/6b2/9/9/1r3A2B/4A4/3K2B2 r
      if (PC_ON_ST(SQ_E8) == MK_PC_WK(ADVISOR))
      {
        if (RF_XX(weakKing) == FILE_D)
          if (popcount(RightBB & (PP_BB_WK(BISHOP) | PP_BB_WK(ADVISOR))) == 4)
            return ScaleFactor(8);
        if (RF_XX(weakKing) == FILE_F)
          if (popcount(FlankMidBoardBB[0] | FileFBB & (PP_BB_WK(BISHOP) | PP_BB_WK(ADVISOR))) == 4)
            return ScaleFactor(8);
      }

      // fen 5k3/9/3a1a3/9/9/2B3B2/7r1/3A5/4A4/5K3 b - - 0 1
      if (RF_XX(weakKing) == FILE_D && !(LeftBB & PP_BB_WK(ADVISOR)))
        return ScaleFactor(8);
      if (RF_XX(weakKing) == FILE_F && !(RightBB & PP_BB_WK(ADVISOR)))
        return ScaleFactor(8);

      // fen 9/3k5/3a1a3/9/9/2B6/9/4B4/1r2A4/3K1A3 b - - 0 1
      if (PC_ON_ST(SQ_E8) == MK_PC_WK(ADVISOR))
      {
        if ((RF_XX(weakKing) == FILE_F && PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR))
          || (RF_XX(weakKing) == FILE_D && PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR)))
        {
          if (RR_WK(strongRook) == RANK_0)
            return ScaleFactor(8);
          if (RR_WK(strongRook) != RANK_0 && RR_WK(weakKing) == RANK_0)
            return ScaleFactor(8);
        }
      }

      // fen 4k4/4a4/5a3/9/2b3b2/9/7R1/3A1K3/9/5A3 b - - 0 1
      if (PC_ON_ST(SQ_E9) == MK_PC_WK(KING) && PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR))
      {
        Bitboard b = FileABB | FileBBB | FileCBB
          | FileDBB | FileEBB | FileFBB | FileHBB | FileIBB;
        if (popcount(b & PP_BB_WK(BISHOP)) == 2)
          return ScaleFactor(8);
      }

      // fen 2b1k4/4a4/b2a5/9/6R2/9/9/B8/3KA4/2B2A3 b - - 0 1
      if (PC_ON_ST(SQ_E9) == MK_PC_WK(KING) && RF_XX(strongKing) == FILE_E)
      {
        if (!(LeftBB & PP_BB_WK(BISHOP))
          || !(RightBB & PP_BB_WK(BISHOP)))
          return ScaleFactor(8);
      }

      // fen 3a5/4k4/b8/9/6b2/9/9/8B/4A4/4KAB1r w - - 0 1
      if (RR_WK(strongRook) >= RANK_1 && RR_WK(weakKing) == RANK_0)
      {
        if (RF_XX(strongRook) <= FILE_B)
          if (PC_ON_ST(SQ_C9) == MK_PC_WK(BISHOP) && PC_ON_ST(SQ_A7) == MK_PC_WK(BISHOP))
            return ScaleFactor(8);

        if (RF_XX(strongRook) >= FILE_H)
          if (PC_ON_ST(SQ_G9) == MK_PC_WK(BISHOP) && PC_ON_ST(SQ_I7) == MK_PC_WK(BISHOP))
            return ScaleFactor(8);
      }

      // fen 2b3R2/3ka4/3a5/9/2b6/9/9/9/3KA4/6B2 b - - 0 1
      if (RF_XX(strongRook) >= FILE_D && RF_XX(weakKing) == FILE_D && PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR))
        if (!(PP_BB_WK(BISHOP) & Side3FileFlank[1]))
          return ScaleFactor(8);

      if (RF_XX(strongRook) <= FILE_F && RF_XX(weakKing) == FILE_F && PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR))
        if (!(PP_BB_WK(BISHOP) & Side3FileFlank[0]))
          return ScaleFactor(8);

      // fen 2b6/3ka3R/b2a5/9/9/9/9/5A3/3KA4/9 w - - 0 1
      if (RF_XX(strongRook) > FILE_E && RF_XX(weakKing) == FILE_D && PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR))
        if (!(PP_BB_WK(BISHOP) & RightBB))
          return ScaleFactor(16);

      if (RF_XX(strongRook) < FILE_E && RF_XX(weakKing) == FILE_F && PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR))
        if (!(PP_BB_WK(BISHOP) & LeftBB))
          return ScaleFactor(16);

      // fen 5a3/3ka4/4b4/R8/2b6/6B2/9/3A5/3K5/5A3 b - - 0 1
      if (RR_WK(weakKing) >= RANK_1 && RF_XX(weakKing) != FILE_E)
        if (!(FileBB[RF_XX(weakKing)] & PP_BB_WK(ADVISOR)))
          return ScaleFactor(16);

      // fen 2bk5/9/b2a1a3/1R7/9/9/9/5A3/3K5/3A5 w - - 0 1
      if (!(PP_BB_WK(BISHOP) & (LowLines | BottomLine)))
      {
        if (RF_XX(weakKing) == FILE_D && !(PP_BB_WK(BISHOP) & RightBB))
          return ScaleFactor(16);
        if (RF_XX(weakKing) == FILE_F && !(PP_BB_WK(BISHOP) & LeftBB))
          return ScaleFactor(16);
      }

      if (PC_ON_ST(SQ_E9) == MK_PC_WK(KING))
        return ScaleFactor(32);

      if (RR_WK(weakKing) >= RANK_1 && !(FileBB[RF_XX(weakKing)] & PP_BB_WK(ADVISOR)))
        return ScaleFactor(32);
    }
  }

  return sf;
}
