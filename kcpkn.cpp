
#include "../pch.h"


template<>
ScaleFactor Endgame<KCPKN>::operator()(const Position& pos) const
{
    Square strongKing = pos.square<KING>(strongSide);
    Square strongPawn = pos.square<PAWN>(strongSide);
    Square strongCannon = pos.square<CANNON>(strongSide);
    Square weakKing = pos.square<KING>(weakSide);
    Square weakKnight = pos.square<KNIGHT>(weakSide);

    int strongAdvisors = pos.count<ADVISOR>(strongSide);
    int strongBishops = pos.count<BISHOP>(strongSide);
    int weakAdvisors = pos.count<ADVISOR>(weakSide);
    int weakBishops = pos.count<BISHOP>(weakSide);

    CheckInfo *ci = pos.check();
    ScaleFactor sf = SCALE_FACTOR_NORMAL;

    if (RR_WK(strongPawn) < RR_WK(weakKing))
        sf = ScaleFactor(32); // 60

      // fen 4kab2/3Pn4/9/9/6b2/9/9/9/4K4/4CA3 w - - 0 0
    if (PC_ON_ST(SQ_E9) == MK_PC_WK(KING) && PC_ON_ST(SQ_E8) == MK_PC_WK(KNIGHT))
        return ScaleFactor(64);

    if (strongAdvisors == 0)
    {
        if (RR_WK(strongPawn) < RR_WK(weakKing))
            return ScaleFactor(8);

        if (weakAdvisors + weakBishops >= 1)
            return ScaleFactor(8);

          // fen 5kb2/9/9/9/5N3/9/9/9/6pc1/4K4 b - - 120 120
        if (RR_WK(strongPawn) > RANK_2)
            return ScaleFactor(8);
    }

    if (weakAdvisors >= 1 && weakBishops == 2)
        return ScaleFactor(8);

      // fen 4c4/3ka4/9/9/9/2N6/9/4K3B/3p5/9 w - - 169 169
    if (weakBishops >= 1 && strongAdvisors <= 1)
        if (RR_WK(strongPawn) < RR_WK(weakKing))
            return ScaleFactor(8);

        // fen 5kb2/3P5/3a5/9/2n6/9/9/9/3KA4/5C3 b - - 126 126
    if (weakBishops >= 1)
        if (RR_WK(strongPawn) >= RANK_1)
        {
            if (PC_ON_ST(SQ_D7) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) < FILE_E)
                if (not_z(knight_attacks_bb(weakKnight, pos.pieces()) & SquareBB[RS_ST(SQ_D7)]))
                    return ScaleFactor(8);
            if (PC_ON_ST(SQ_F7) == MK_PC_WK(ADVISOR) && RF_XX(strongPawn) > FILE_E)
                if (not_z(knight_attacks_bb(weakKnight, pos.pieces()) & SquareBB[RS_ST(SQ_F7)]))
                    return ScaleFactor(8);
        }

    if (and_true(ci->pinned, square_bb(weakKnight)) && and_true(ci->pinned, pos.pieces(weakSide, ADVISOR, BISHOP)))
        return ScaleFactor(64);

    if (weakAdvisors + weakBishops >= 3)
        return ScaleFactor(8);

    if (weakAdvisors + weakBishops >= 2)
        return ScaleFactor(8);

      // fen 5k3/4P4/b8/9/9/9/6n2/3A5/3KA4/3C5 w - - 121 121
    if (strongBishops == 0)
        if (RR_WK(strongPawn) >= RANK_5 && abs(RR_WK(strongPawn) - RR_WK(weakKing)) <= 1)
        {
            if (RF_XX(weakKing) == FILE_F)
                if (PC_ON_ST(SQ_C3) == MK_PC_WK(KNIGHT) || PC_ON_ST(SQ_G3) == MK_PC_WK(KNIGHT))
                    return ScaleFactor(8);
            if (RF_XX(weakKing) == FILE_D)
                if (PC_ON_ST(SQ_C1) == MK_PC_WK(KNIGHT) || PC_ON_ST(SQ_G1) == MK_PC_WK(KNIGHT))
                    return ScaleFactor(8);
        }

      // fen 3k5/4n4/9/9/4C1P2/9/9/9/9/4K4 w - - 0 0
    if (strongAdvisors == 0 && strongBishops == 0)
    {
        if (RF_XX(weakKing) <= FILE_E && RF_XX(strongPawn) >= FILE_E)
            return ScaleFactor(8);
        if (RF_XX(weakKing) >= FILE_E && RF_XX(strongPawn) <= FILE_E)
            return ScaleFactor(8);
    }

    // fen 5a3/5k3/3a1N3/9/6b2/6c2/9/5K3/3p5/9 w - - 0 1
    if (not_z(KingMove[strongKing] & PP_BB_WK(KNIGHT)))
        return ScaleFactor(64);

      // fen 9/5k3/4P4/5C3/3n5/9/9/4B4/9/2BK5 w - - 0 123
    if (strongAdvisors == 0 && RR_WK(strongPawn) >= RANK_2)
        if (abs(RR_WK(strongPawn) - RR_WK(weakKing)) <= 1)
            return ScaleFactor(8);

        // fen 9/4P4/5k3/9/9/2B6/2n6/3KBA3/4A4/8C b - - 126 126
    if (RR_WK(strongPawn) < RR_WK(weakKing) && RR_WK(weakKnight) <= RANK_5)
        return ScaleFactor(16);

      // fen 1c7/3ka4/9/6N2/9/9/9/3p5/4K4/3A5 w - - 121 121
    if (weakAdvisors >= 1 && RR_WK(weakKnight) <= RANK_4)
        if (strongAdvisors == 0 && strongBishops == 0)
            if (abs(RF_XX(strongPawn) - RF_XX(weakKing)) <= 1)
                return ScaleFactor(16);

          // fen 5k3/4P4/3Cb4/3n5/9/2B6/9/4BA3/9/4K4 w - - 0 1
    if (weakBishops >= 1 && RR_WK(strongPawn) >= RANK_1)
        if (RR_WK(strongCannon) >= RANK_2)
            if (abs(RR_WK(weakKnight) - RANK_3) <= 1)
                return ScaleFactor(16);

          // fen 4k4/9/9/4P4/9/2B1n4/9/9/5K3/5C3 r
    if (strongAdvisors == 0 && strongBishops <= 1)
        return ScaleFactor(16);

      // fen 2b2c3/3ka4/5a3/9/9/9/6N2/4B4/5p3/4K4 b - - 0 103
    if (weakBishops >= 1)
        if (!(RR_WK(weakKing) == RANK_0 && PC_ON_ST(SQ_E8) == MK_PC_ST(PAWN)))
            return ScaleFactor(32);

    return sf;
}
