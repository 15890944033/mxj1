#include "endgame.h"


//马炮方有2个以上过河兵，如果过河非底线的左或右侧没有兵，扣分
//马炮方士象调整
template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color c>
inline void Endgame<E>::cn_k_total(const Position& pos, Score& score) const {
	Value v = VALUE_ZERO;
	const Color Them = c == WHITE ? BLACK : WHITE;

	if (pos.pawn_validcount<c>() >= 2
		&& (equal_z(pos.pieces_pawn_crnb<c>() & FlankBoardBC[LEFT]) || equal_z(pos.pieces_pawn_crnb<c>() & FlankBoardBC[RIGHT]))) {
		v += -PAWN_END_10P;
	}

	if (pos.is_pawns_partner_midhigh<Them>()) {
		v += -PAWN_END_238P;
	}

	update_score(score, c,  v);

	//ba_adjust_strong<c>(pos, score);

}

template<>
Value Endgame<KCNK>::operator()(const Position& pos, Score& score) const {

	if (strongSide == WHITE) {
		if (knight_chain_byking<WHITE>(pos) && pos.pawn_nobottomcount<WHITE>() == 0
			&& (pos.defense_count(BLACK) > 0 || pos.pawn_crhighcount<BLACK>() > 0))
			update_score(pos, score, -KNIGHT_END_90P);

		if (pos.count(WHITE, ADVISOR) == 0)
			goto drawEnd;
		else {
			//马在胁道双鬼拍门位置
			if (not_z(pos.pieces(KNIGHT) & AreaDbMonster)) {
				if(pos.defense_count(BLACK) >=  3 || pos.count(BLACK, BISHOP) == 2
					|| (pos.count(BLACK, ADVISOR) == 2 && pos.pawn_crhighcount<BLACK>() > 0))
					goto drawEnd;
			}
		}
	}
	else {
		if (knight_chain_byking<BLACK>(pos) && pos.pawn_nobottomcount<BLACK>() == 0
			&& (pos.defense_count(WHITE) > 0 || pos.pawn_crhighcount<WHITE>() > 0))
			update_score(pos, score, KNIGHT_END_90P);

		if (pos.count(BLACK, ADVISOR) == 0)
			goto drawEnd;
		else {
			//马在胁道双鬼拍门位置
			if (not_z(pos.pieces(KNIGHT) & AreaDbMonster)) {
				if (pos.defense_count(WHITE) >= 3 || pos.count(WHITE, BISHOP) == 2
					|| (pos.count(WHITE, ADVISOR) == 2 && pos.pawn_crhighcount<WHITE>() > 0))
					goto drawEnd;
			}
		}

	}

	strongSide == WHITE ? cn_k_total<WHITE>(pos, score) : cn_k_total<BLACK>(pos, score);
	return VALUE_NONE;

drawEnd:
	return value_draw_zoom<4>(pos, score);

}
