#include "endgame.h"


template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color c>
inline void Endgame<E>::rc_nn_total(const Position& pos, Score& score) const {
	Value v = VALUE_ZERO;
	const Color Them = c == WHITE ? BLACK : WHITE;

	//强方王居中露脸，加分
	if (pos.is_king_mid_clear<c>())
		v += BISHOP_END_40P;

	//弱方王不在底，扣分
	if (!pos.is_king_bottom(Them))
		v += BISHOP_END_40P;

	update_score(score, c, v);

	ba_adjust_strong<c>(pos, score, VALUE_BA_ADJUST_MAX_UL);

}

template<>
Value Endgame<KRCKNN>::operator()(const Position& pos, Score& score) const {
	strongSide == WHITE ? rc_nn_total<WHITE>(pos, score) : rc_nn_total<BLACK>(pos, score);
	FUN_IMPL_DIFF_PIECES_ALL(krc_knn)
}

template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::krc_knn_0p_0p(const Position& pos, Score& score) const {
	return 	VALUE_NONE;
}

template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::krc_knn_1p_0p(const Position& pos, Score& score) const {
	return 	VALUE_NONE;
}

template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::krc_knn_2p_0p(const Position& pos, Score& score) const {
	return 	VALUE_NONE;
}


template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::krc_knn_0p_1p(const Position& pos, Score& score) const {
	return 	VALUE_NONE;
}

template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::krc_knn_1p_1p(const Position& pos, Score& score) const {
	return 	VALUE_NONE;
}

template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::krc_knn_2p_1p(const Position& pos, Score& score) const {
	return 	VALUE_NONE;
}


template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::krc_knn_0p_2p(const Position& pos, Score& score) const {
	return 	VALUE_NONE;
}

template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::krc_knn_1p_2p(const Position& pos, Score& score) const {
	return 	VALUE_NONE;
}

template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::krc_knn_2p_2p(const Position& pos, Score& score) const {
	return 	VALUE_NONE;
}

