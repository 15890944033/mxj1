
#include "../pch.h"


template<>
ScaleFactor Endgame<KCCKN>::operator()(const Position& pos) const
{
  Square strongKing = pos.square<KING>(strongSide);
  Square strongCannon1 = msb(pos.pieces(strongSide, CANNON));
  Square strongCannon2 = lsb(pos.pieces(strongSide, CANNON));
  Square weakKing = pos.square<KING>(weakSide);
  Square weakKnight = pos.square<CANNON>(weakSide);

  int strongAdvisors = pos.count<ADVISOR>(strongSide);
  int strongBishops = pos.count<BISHOP>(strongSide);
  int weakAdvisors = pos.count<ADVISOR>(weakSide);
  int weakBishops = pos.count<BISHOP>(weakSide);

  ScaleFactor sf = ScaleFactor(16);

  // fen 2b6/4a4/3a1k3/6N2/9/6B2/9/B2A1A3/3K5/cc7 b - - 135 135
  if (weakAdvisors == 2 && weakBishops == 2)
    return ScaleFactor(8);

  // fen 3c5/9/5k3/4c1N2/9/2B3B2/9/5A3/9/3K5 b - - 123 123
  if (weakBishops == 2)
    if (strongAdvisors == 0 && strongBishops == 0)
      return ScaleFactor(8);

  // fen 4k1b2/9/8b/9/2n6/9/4C4/3C5/4A4/5K3 b - - 0 1
  if (weakBishops == 2)
    if (strongAdvisors <= 1 && strongBishops <= 1)
      return ScaleFactor(8);

  // fen 3k5/9/9/9/8n/2B6/9/3CB4/4CK3/9 w - - 0 1
  if (strongAdvisors == 0)
    if (RF_XX(strongKing) != FILE_E)
      return ScaleFactor(8);

  // fen 3k5/4a4/5a3/9/6b2/9/3CC4/4B4/1n2A4/3A1KB2 w - - 0 1
  if (weakAdvisors == 2 && weakBishops >= 1)
    return ScaleFactor(8);

  // fen 3c5/9/5k3/4c1N2/9/2B3B2/9/5A3/9/3K5 b - - 123 123
  if (weakBishops == 2)
    if (strongAdvisors == 0 && strongBishops <= 1)
    {
      if (RR_WK(weakKing) <= RANK_1)
        return ScaleFactor(8);

      // fen 2bk5/9/9/9/1N7/1cB6/9/3ABK3/c3A4/9 r
      if (weakBishops == 2 && weakAdvisors >= 1)
        return ScaleFactor(8);

      // fen 9/9/3k5/2N3c2/1cb6/9/9/4B4/9/5K3 w - - 225 225
      if (weakBishops >= 1)
        return ScaleFactor(8);
    }

  // fen 6b2/3ka4/3n5/4C4/2b6/2B6/9/3AB4/3C5/3A1K3 w - - 3 3
  if (weakBishops == 2 && weakAdvisors >= 1)
    return ScaleFactor(8);

  // fen 4c4/3c5/3abk3/9/2b6/5N3/9/4BA3/4A4/4K4 w - - 0 1
  if (weakBishops + weakAdvisors >= 3)
    return ScaleFactor(8);

  if (strongAdvisors == 0)
    return ScaleFactor(8);

  // fen 1c7/3ka4/5a3/9/4c4/2B3B1N/9/9/9/4K4 w - - 0 1
  if (weakBishops == 2)
    return ScaleFactor(8);

  return sf;
}
