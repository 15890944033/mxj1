
#include "../pch.h"


template<>
ScaleFactor Endgame<KNCKN>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongKnight = pos.square<KNIGHT>(strongSide);
  Square strongCannon = pos.square<CANNON>(strongSide);
  Square weakKing = pos.square<KING>(weakSide);
  Square weakKnight = pos.square<KNIGHT>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  Bitboard b;
  CheckInfo *ci = pos.check();
  ScaleFactor sf = SCALE_FACTOR_NORMAL;

  if (weakAdvisors + weakBishops == 4)
    if (strongAdvisors + strongBishops == 0)
      return ScaleFactor(8);

  // fen 5kb2/9/8b/5N3/9/2B6/9/4B1Cn1/9/3K5 w - - 89 89
  //if (weakBishops == 2 && strongAdvisors == 0)
  //  if (RR_WK(weakKnight) >= RANK_4)
  //    return ScaleFactor(8);

  // fen 5k3/5N3/8b/9/9/9/6n2/5KC2/9/9 b - - 0 1
  if (weakAdvisors >= 1 && weakBishops >= 1)
    if (strongAdvisors == 0 && strongBishops == 0)
      if (and_true(ci->pinned, square_bb(strongKnight)))
        return ScaleFactor(8);

  // fen 6b2/3kN4/4b4/9/5n3/9/9/4CA3/4A4/2B1K1B2 b - - 0 1
  if (weakBishops == 2)
  {
    b = knight_attacks_bb(strongKnight, pos.pieces());
    int i = 0, c = popcount(b);

    while (not_z(b))
      if (not_z(pos.attackers_to(pop_lsb(b), pos.pieces()) & pos.pieces(weakSide)))
        i++;

    if (i == c && !aligned(strongCannon, weakKing, strongKnight))
      return ScaleFactor(8);
  }

  // fen 9/4k4/4N4/9/9/C8/9/3A1A3/4K3n/9 b - - 0 1
  if (weakBishops == 0 && strongBishops == 0)
    if (and_true(square_bb(strongKnight), ci->pinned))
      return ScaleFactor(8);

  return sf;
}
