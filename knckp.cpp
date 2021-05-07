#include "../pch.h"


template<>
ScaleFactor Endgame<KNCKP>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongKnight = pos.square<KNIGHT>(strongSide);
  Square strongCannon = pos.square<CANNON>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);
  Square weakPawn = pos.square<PAWN>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  Bitboard b;
  Bitboard pinners, cannonCandidates;
  Bitboard pinned = pos.pinned_pieces(strongSide, pinners, cannonCandidates);

  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  // fen 3a1Cb2/5k1N1/4b4/9/9/6B2/2p6/4BA3/9/3AK4 w - - 17 17
  if (weakAdvisors >= 1 && weakBishops == 2)
    if (RR_WK(weakKing) == RANK_1)
    {
      b = pos.attackers_to(strongCannon, pos.pieces());
      
      if (popcount(b & pos.pieces(weakSide)) == popcount(b & pos.pieces(strongSide)))
        return ScaleFactor(8);
    }

  // fen 3k5/3N5/9/9/2b6/2B6/5p3/4B4/3K5/3C5 w - - 0 1
  if (strongAdvisors == 0)
    if (RR_WK(weakPawn) == RANK_6)
      if (and_true(pinned, square_bb(strongKnight)))
        return ScaleFactor(8);

  return sf;
}
