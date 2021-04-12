#include "endgame.h"


//�������2��ʿ��û�����ʿ���۷�
//�����ڷ���λ�ã��۷�
//˫����2�����Ϲ��ӱ���������ӷǵ��ߵ�����Ҳ�û�б����۷�
//˫��ʿ����� : ��������ӱ�С��2
//˫�����ӷ�
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

	//ǿ��Ӧ����¶��
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

//˫��ʤ��˫ʿ  ʤ��˫��
//˫����˫ʿ�� ʤ�� 43.3%	  ���� 86% 	����˫��ʿ 29.6%
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
//���� vs ������  ʤ�ʣ� 75.05%	 ���ʣ� 14.73%
//���� vs ����ʿ  ʤ�ʣ�85.43%	���ʣ� 5.26%
//���� vs ����ʿ��	ʤ�ʣ�  62.38%	���ʣ� 26.79%	
//���� vs ����ʿʿ	ʤ�ʣ�  64.37%	���ʣ� 26.48%  ��Ӯһ��ҲҪ60�غ�����
//���� vs ��������	ʤ�ʣ�30.33%	���ʣ�58.75%
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
		//˫���޵ױ������й����м����б����͵Ļ����
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
	//ǿ��ʿ��У������ǵױ�>=2 ��������ȫ��ǿ���۷�
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

