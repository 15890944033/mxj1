#include "endgame.h"


//马方如果有2个士，没有羊角士，扣分
//马方马不在防守位置，扣分
//双马方有2个以上过河兵，如果过河非底线的左或右侧没有兵，扣分
//双马方士象调整 : 如果马方过河兵小于2
//双马方兵加分
template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color c>
inline void Endgame<E>::nn_n_total(const Position& pos, Score& score) const {
	const Color Them = c == WHITE ? BLACK : WHITE;

	int nbpStrong = pos.pawn_nobottomcount<c>();
	Value v = VALUE_ZERO;

	//if (nbpStrong > 0) {
	//	v += KnightValueEg * 0.4;
	//	pawns_bonus<c>(pos, score);
	//}

	int ad = pos.count(Them, ADVISOR);
	if (ad == 2 && !pos.is_advisor_cavel(Them))
		v += BISHOP_END_10P;

	if (pos.pawn_validcount<c>() >= 2
		&& (equal_z(pos.pieces_pawn_crnb<c>() & FlankBoardBC[LEFT]) || equal_z(pos.pieces_pawn_crnb<c>() & FlankBoardBC[RIGHT]))) {
		v += -PAWN_END_10P;
	}

	if (!is_kn_defense<Them>(pos))
		v += BISHOP_END_50P;

	//强方应该王露脸
	if (!pos.is_king_clear<c, 0>())
		v += -BISHOP_END_10P;

	update_score(score, c,  v);
	pawns_bonus<c>(pos, score);

	if (nbpStrong == 0 && pos.pawn_nobottomcount<Them>() == 0)
		ba_adjust_strong<c>(pos, score);

}


template<>
Value Endgame<KNNKN>::operator()(const Position& pos, Score& score) const {
	if (strongSide == WHITE) {
		if (pos.pawn_validcount<WHITE>() == 0) {
			if (knight_chain_byking<WHITE>(pos))
				return update_score(score, -KNIGHT_END_90P);
		}
	}
	else {
		if (pos.pawn_validcount<BLACK>() == 0) {
			if (knight_chain_byking<BLACK>(pos))
				return update_score(score, KNIGHT_END_90P);
		}
	}

	strongSide == WHITE ? nn_n_total<WHITE>(pos, score) : nn_n_total<BLACK>(pos, score);


	FUN_IMPL_DIFF_PIECES_ALL(knn_kn)
}

//双马胜马双士  胜马双象
//双马马双士象 胜率 43.3%	  有象 86% 	对马双象士 29.6%
template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::knn_kn_0p_0p(const Position& pos, Score& score) const {
	I_AM_WEAK

	auto ba = pos.ba_number<weak>();
	switch (ba)
	{
	case BA_ZERO:
	case BA_AD:
	case BA_BS:
	case BA_BA:
	case BA_DA:
		goto almostWin;
	case BA_DB:
		if (pos.pawn_bottomcount<strong>() > 0)
			goto almostWin;
		break;
	case BA_BDA:
		if (pos.pawn_bottomcount<strong>() > 0 || pos.count(strong, BISHOP) > 0)
			goto almostWin;
		break;
	case BA_DBA:
		if (pos.pawn_bottomcount<strong>() > 0)
			goto almostWin;
		break;
	default:
		if (pos.pawn_bottomcount<strong>() > 0)
			break;
		else
			return value_draw_zoom<2>(pos, score);
	}

	return value_draw_zoom<1>(pos, score);

almostWin:
	return value_final(pos, score);

}

template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::knn_kn_1p_0p(const Position& pos, Score& score) const {
	return VALUE_NONE;


}

template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::knn_kn_2p_0p(const Position& pos, Score& score) const {
	return VALUE_NONE;
}
//马马 vs 马卒象  胜率： 75.05%	 和率： 14.73%
//马马 vs 马卒士  胜率：85.43%	和率： 5.26%
//马马 vs 马卒士象	胜率：  62.38%	和率： 26.79%	
//马马 vs 马卒士士	胜率：  64.37%	和率： 26.48%  能赢一般也要60回合以上
//马马 vs 马卒象象	胜率：30.33%	和率：58.75%
template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::knn_kn_0p_1p(const Position& pos, Score& score) const {
	I_AM_WEAK

	auto ba = pos.ba_number<weak>();
	switch (ba)
	{
	case BA_ZERO:
	case BA_AD:
		goto almostWin;

	case BA_BS:
		//双马方无底兵且马方有过河中间五列兵，和的机会大
		if(pos.pawn_bottomcount<strong>() == 0 && not_z(pos.pieces(weak, PAWN) & AreaMid5File & HighPawnBC[weak]))
			break;
		goto almostWin;

	case BA_DB:
	case BA_DA:
		if (pos.pawn_bottomcount<strong>() > 0)
			goto almostWin;
		break;
	default:
		break;
	}

	return value_draw_zoom<1>(pos, score);

almostWin:
	return value_final(pos, score);
}

template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::knn_kn_1p_1p(const Position& pos, Score& score) const {
	return VALUE_NONE;
}

template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::knn_kn_2p_1p(const Position& pos, Score& score) const {
	return VALUE_NONE;
}


template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::knn_kn_0p_2p(const Position& pos, Score& score) const {
	I_AM_WEAK
		int vp = pos.pawn_validcount<weak>();
	//强方士象残，弱方非底兵>=2 防御子力全，强方扣分
	if (vp >= 2 && pos.defense_count(strong) <= 2 && (pos.defense_count(weak) >= 3 || pos.count(weak, BISHOP) == 2))
		return update_score(pos, score, strong, -BISHOP_END_10P * vp);

	int nb = pos.pawn_nobottomcount<weak>();
	if (nb == 2) {
		if (pos.pawn_bottomcount<strong>() == 0 && pos.defense_count(strong) >= 3
			&& (pos.defense_count(weak) >= 3 || pos.count(weak, BISHOP) == 2 || pos.is_pawns_partner_midhigh<weak>()))
			goto drawEnd;
	}
	//else {
	//	assert(nb > 2);
	//	if (pos.full_ba(weak))
	//		return update_score(pos, score, weak, BishopValueEg * 0.4 * nb);

	//}

	return VALUE_NONE;

drawEnd:
	return value_draw_zoom<2>(pos, score);
}

template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::knn_kn_1p_2p(const Position& pos, Score& score) const {
	I_AM_WEAK
	if (pos.is_pawns_partner_midhigh<weak>())
		return update_score(pos, score, strong, -BISHOP_END_80P);
	return VALUE_NONE;
}

template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::knn_kn_2p_2p(const Position& pos, Score& score) const {
	return VALUE_NONE;
}

