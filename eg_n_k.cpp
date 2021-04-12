#include "endgame.h"

//残局要考虑的因素：
//双方的兵数目
//双方士象数目
//优势方士象分是否应减小
//一方多士象，一方多兵，分数应如何调整
//劣势方士象应如何组合
//是否交换兵
//是否交换士象
//是否兵换士象 （单士 / 象或双士，双象，或士 + 象或3个士象）
//兵的位置（未过河，对头兵， 过河兵， 高兵，二路低兵， 三路低兵， 中象兵，冲过头兵， 底兵）
//2个以上兵进攻时应注意从左右两侧往下冲，避免挤在同一侧
//马的位置，进攻位或防守位
//士羊角位置，对方有马时
//牵制问题， 王牵马，
//王是否占中，是否露脸，是否侧面露脸， 是否不能在顶
//绝对胜棋		进攻方进攻子力位置没有特殊要求，不需要特别的取胜手段
//绝对和棋		进攻方只有一个进攻子力，或2个兵


//马方士象分调整
//无马方王如果不在侧面露脸，扣分
//马方有2个以上过河兵，且弱方有双象，如果过河非底线的左或右侧没有兵，扣分
//马方有兵，且有至少一个士，兵方有至少2个过河兵，且马方占400分以上优势，兵方如果过河兵在中路拉手， 加分
template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color c>
inline void Endgame<E>::n_k_total(const Position& pos, Score& score) const {
	Value v = VALUE_ZERO;
	const Color Them = c == WHITE ? BLACK : WHITE;
	
	adjust_pawn_behind_king<WHITE>(pos, score);
	adjust_pawn_behind_king<BLACK>(pos, score);
	adjust_pawn_same_flank<WHITE>(pos, score);
	adjust_pawn_same_flank<BLACK>(pos, score);

	int nbpStrong = pos.pawn_nobottomcount<c>();
	int nbpWeak = pos.pawn_nobottomcount<Them>();
	int vpWeak = pos.pawn_validcount<Them>();
	int defStrong = pos.defense_count(c);

	if (nbpStrong > 0 && !pos.is_king_flank_clear<Them>()) {
		v += PAWN_END_10P;
	}
	if (pos.pawn_validcount<c>() >= 2 && pos.count(Them, BISHOP) == 2
		&& (equal_z(pos.pieces_pawn_crnb<c>() & FlankBoardBC[LEFT]) || equal_z(pos.pieces_pawn_crnb<c>() & FlankBoardBC[RIGHT]))) {
		v += -PAWN_END_10P;
	}

	if (nbpStrong > 0 && vpWeak >= 2 && pos.count(c, ADVISOR) > 0){
		if (pos.is_pawns_partner_midhigh<Them>() && greater_than<c>(score, VALUE_ADV_LOWLIMIT)) {
			v += -PAWN_END_60P;
		}
	}
	update_score(score, c,  v);

	if (nbpStrong > 0 && nbpWeak <= 1)
		ba_adjust_strong<c>(pos, score, VALUE_BA_ADJUST_MAX_UL);
	else if (nbpStrong == 0 && nbpWeak >= 2)
		ba_adjust_strong<Them>(pos, score);
}


template<>
Value Endgame<KNK>::operator()(const Position& pos, Score& score) const {
	if (strongSide == WHITE) {
		if (knight_traped_byking<WHITE>(pos))
			goto whiteKnFixed;
		if (knight_chain_byking<WHITE>(pos)) {
			int wvp = pos.pawn_validcount<WHITE>();
			if(wvp == 0)
				goto whiteKnFixed;
			else if (wvp == 1) {
				if (pos.pawn_crhighcount<WHITE>() == 0 && pos.count(BLACK, ADVISOR) > 0) {
					//马不在中路， 下二路，或下三路的兵与马在不同侧
					Square nsq = pos.square(WHITE, KNIGHT);
					assert(nsq != SQ_NONE);
					Flank fl = square_flank(nsq);
					if (fl != MIDDLE) {
						BitboardC bc = pos.pieces(WHITE, PAWN) & LowRankBC;
						if(equal_z(bc))
							goto whiteKnFixed;
						else {
							assert(popcount(bc) == 1);
							Square psq = lsb(bc);
							assert(psq != SQ_NONE);
							if(square_flank(psq) == ~fl)
								goto whiteKnFixed;
						}
					}
				}
			}
		}
	}
	else {
		if (knight_traped_byking<BLACK>(pos))
			goto blackKnFixed;
		if (knight_chain_byking<BLACK>(pos)) {
			int wvp = pos.pawn_validcount<BLACK>();
			if (wvp == 0)
				goto blackKnFixed;
			else if (wvp == 1) {
				if (pos.pawn_crhighcount<BLACK>() == 0 && pos.count(WHITE, ADVISOR) > 0) {
					//马不在中路， 下二路，或下三路的兵与马在不同侧
					Square nsq = pos.square(BLACK, KNIGHT);
					assert(nsq != SQ_NONE);
					Flank fl = square_flank(nsq);
					if (fl != MIDDLE) {
						BitboardC bc = pos.pieces(BLACK, PAWN) & LowRankBC;
						if (equal_z(bc))
							goto blackKnFixed;
						else {
							assert(popcount(bc) == 1);
							Square psq = lsb(bc);
							assert(psq != SQ_NONE);
							if (square_flank(psq) == ~fl)
								goto blackKnFixed;
						}
					}
				}
			}
		}
	}

	strongSide == WHITE ? n_k_total<WHITE>(pos, score) : n_k_total<BLACK>(pos, score);

    {
        FUN_IMPL_DIFF_PIECES_ALL(kn_k)
    }

whiteKnFixed:
	return update_score(pos, score, -KNIGHT_END_90P);

blackKnFixed:
	return update_score(pos, score, KNIGHT_END_90P);

}
//王方有老兵，和
//马胜光王 
//马胜士
//马例和象 胜率：14.56%  有老兵胜
//马例和士象 有老兵胜
//马例和双士 有老兵胜
//马例和双象 双象士，双士象，士象全 有老兵也是和
template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::kn_k_0p_0p(const Position& pos, Score& score) const {
	//马胜光王
	//马胜单士 （不能被牵制）
	//马对单象有胜机
	//其他和
	I_AM_WEAK
	Value v = king_midclear<strong>(pos) + knight_attack<strong>(pos);
	
	if(pos.pawn_bottomcount<weak>() > 0)
		goto drawEnd;
    else
    {
        auto ba = pos.ba_number<weak>();
        switch (ba)
        {
        case BA_ZERO:
        case BA_AD:
            goto almostWin;
        case BA_BS:
            if (pos.pawn_bottomcount<strong>() > 0)
                goto almostWin;
            //王在中路露脸，对方象和王在同一侧 胜
            if (pos.is_king_mid_clear<strong>()) {
                if (same_flank(pos.square(weak, KING), pos.square(weak, BISHOP)))
                    goto almostWin;
            }
            break;
        case BA_BA:
            if (pos.pawn_bottomcount<strong>() > 0)			//马底兵胜单士象 , 有难度，不应用win分数
                goto almostWin;
            break;
        case BA_DA:
            if (pos.pawn_bottomcount<strong>() > 0)			//马底兵胜双士
                goto almostWin;
            break;
            //case BA_DB:
            //case BA_DBA:
            //case BA_BDA:
            //case BA_DBDA:
        default:
            break;
        }
    }

drawEnd:
	return value_general_final<strong>(pos, v);

almostWin:

	return value_final(pos, score);
}
//马兵胜光王		王有老兵也胜
//马兵胜象		王有老兵胜
//马兵例胜士		王有老兵，马无老兵，兵在下二路， 太公座椅和
//马兵例胜士象	王有老兵，马无老兵，兵在下二路， 太公座椅和
//马兵胜双士		王有老兵，马可以有老兵，兵在下二路， 太公座椅和
//马兵胜双象		有老兵也胜	唯一和棋：王有老兵 马无老兵，且兵在三七路未过河
//马兵对双象士	
//马兵对双士象	高兵捉死象可胜
//马兵对士象全	马有老兵，王无老兵可胜	

template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::kn_k_1p_0p(const Position& pos, Score& score) const {
	I_AM_WEAK
	Value v = king_clear<strong>(pos) + knight_attack<strong>(pos);
	BitboardC bcTmp;
	Square s;
	auto ba = pos.ba_number<weak>();
	switch (ba)
	{
	case BA_ZERO:
	case BA_BS:
		goto almostWin;
	case BA_AD:
	case BA_BA:
		//有一种情况是和棋 有底兵，王在侧面露脸，太公座椅，马方没有底兵，且一个兵是下二路低兵，且与对方的王异侧
		if (pos.pawn_bottomcount<weak>() > 0 && pos.pawn_low3count<strong>() == 0 
			&& pos.pawn_bottomcount<strong>() == 0 && good_defense_against_kp<weak>(pos))
			break;
		goto almostWin;
	case BA_DA:
		//有一种情况是和棋 有底兵，王在侧面露脸，马方没有底兵，没有高兵， 且与对方的王异侧
		if (pos.pawn_bottomcount<weak>() > 0 && pos.is_king_flank_clear<weak>()
			&& pos.pawn_highcount<strong>() == 0
			&& !same_flank(pos.square(strong, PAWN), pos.square(weak, KING)))
			break;

		goto almostWin;
	case BA_DB:
		//马方三七兵可以过河，不用担心  如果双象方有底兵, 马方兵在三七线，没有过河，且没有底兵 和
		if (pos.pawn_bottomcount<weak>() > 0 && homepawn_threeseven<strong>(pos)
			&& pos.pawn_bottomcount<strong>() == 0)
			break;
		goto almostWin;

		
	case BA_DBA:
		//要考虑的问题，三七线兵能否过河， 高兵取胜路径， 低兵和棋路径，马方有底兵和弱方有底兵
		//取胜路径，兵把肋道，王在另外一侧露脸，用马来将
		if (homepawn_threeseven<strong>(pos))
			break;
		if (pos.pawn_bottomcount<strong>() > 0)
			goto almostWin;

		//兵占肋道，王侧面露脸控制另一侧肋道，对方的王不在三楼， 马上要赢了
		if (pos.is_king_flank_clear<strong>() && !pos.is_king_top<weak>()){
			s = pos.pawn_monsterknock(strong);
			if (s != SQ_NONE && !same_flank(s, pos.square(strong, KING))) {
				update_score(score, strong, PawnValueEg);
				goto almostWin;
			}
		}
		//非太空座椅
		if(!good_defense_against_kp<weak>(pos))
			goto almostWin;
		break;
	case BA_BDA:
		//要考虑马方有底兵 和 弱方有底兵
		//高兵取胜路径，先吃掉象
		//马把边象定住，且兵在上二线，加分
		bcTmp = pos.pieces(weak, BISHOP) & AreaBorderFile;
		if (not_z(bcTmp)) {
			s = lsb(bcTmp);
			if (is_same_rank(s, pos.square(strong, KNIGHT)) && file_distance(s, pos.square(strong, KNIGHT)) == 1
				&& pos.pawn_crhighcount<strong>() == 1) {
				update_score(score, strong, BISHOP_END_70P);
				goto almostWin;
			}
		}
		//低兵和棋路径， 马方没有高兵，没有底兵，  弱王在侧面露脸，且马方兵与弱王异侧，or 弱方有底兵
		if(pos.pawn_bottomcount<strong>() == 0 && pos.pawn_highcount<strong>() == 0 && pos.is_king_flank_clear<weak>()
			&& (pos.pawn_bottomcount<weak>() > 0 || !same_flank(pos.square(strong, PAWN), pos.square(weak, KING))))
			break;

		goto almostWin;
	default:
		if (homepawn_threeseven<strong>(pos))		//三七线未过河兵无法过河， 和
			break;
		if (pos.pawn_bottomcount<strong>() > 0)				//马方有底兵，底兵价值大于士或象，给底兵加分， 胜可能性大
			goto almostWin;

		//兵在下二线肋道，王在侧面露脸，且与兵异侧，马在攻击位置，这是典型的攻法，加分（虽不一定赢）
		if (pos.is_king_flank_clear<strong>() && pos.pawn_monsterknock(strong) != SQ_NONE
			&& !same_flank(pos.square(strong, KING), pos.square(strong, PAWN))
			&& is_kn_attack<strong>(pos))
			update_score(score, strong, BISHOP_END_40P);
		break;

	}

	return value_draw_zoom<4>(pos, score);
almostWin:

	return value_final(pos, score);

}

template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::kn_k_2p_0p(const Position& pos, Score& score) const {
	return value_final(pos, score);
}

//马对兵光王， 如果兵没有过河，且没老兵，有胜机 
//马和兵其他
template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::kn_k_0p_1p(const Position& pos, Score& score) const {
	Value v = king_clear<strong>(pos) + knight_attack<strong>(pos);

	I_AM_WEAK

	if (pos.zero_ba(weak) && pos.pawn_homecount<weak>() == 1 && pos.pawn_bottomcount<weak>() == 0)
		return value_draw_zoom<1>(pos, score);

	return value_draw_zoom<4>(pos, score);
}
//马兵胜兵光王	王有老兵也胜
//马兵胜兵象		王有老兵胜
//马兵对兵士		马高兵胜， 马无老兵，兵在下二路， 太公座椅和
//马兵对兵士象	马高兵胜，马无老兵，兵在下二路， 太公座椅和
//马兵胜兵双象	唯一和棋：王有老兵 马无老兵，且兵在三七路未过河
//马兵胜兵双士	王有老兵，马可以有老兵，兵在下二路， 太公座椅和
//马兵对兵双象士	马高兵胜
//马兵对兵双士象	马有老兵胜
//马兵对士象全	和
template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::kn_k_1p_1p(const Position& pos, Score& score) const {
	BitboardC bcTmp;
	I_AM_WEAK
	auto ba = pos.ba_number<weak>();
	//马高兵胜卒士 
	//马低兵例和卒士 ， 太公座椅
	//马高兵例和卒双士
	switch (ba)
	{
	case BA_ZERO:
	case BA_BS:
		goto almostWin;
	case BA_AD:
		//进攻路线，从中象位进攻
		if (pos.pawn_midbishop<strong>()) {
			update_score(score, strong, BishopValueEg);
			goto almostWin;
		}
		//马低兵例和卒士 ， 太公座椅
		if (pos.pawn_low2count<strong>() == 1 && pos.pawn_bottomcount<strong>() == 0 
			&& pos.pawn_validcount<weak>() > 0 && pos.is_king_flank_clear<weak>()
			&& is_same_file(pos.square(weak, ADVISOR), pos.square(weak, KING))
			&& !same_flank(pos.square(strong, PAWN), pos.square(weak, KING))) 
			break;
		//弱方有底兵不改变结果
		goto almostWin;
	case BA_BA:
		//马低兵例和卒士 ， 太公座椅
		if (pos.pawn_low2count<strong>() == 1 && pos.pawn_validcount<weak>() > 0 && pos.pawn_bottomcount<strong>() == 0
			&& pos.is_king_flank_clear<weak>() && is_same_file(pos.square(weak, ADVISOR), pos.square(weak, KING))
			&& !same_flank(pos.square(strong, PAWN), pos.square(weak, KING)))
			break;
		//弱方有底兵不改变结果
		goto almostWin;
	case BA_DB:
		//考虑三七线未过河兵，过不去的情况 
		if (homepawn_threeseven<strong>(pos) && pos.pawn_bottomcount<weak>() > 0 && pos.pawn_bottomcount<strong>() == 0)
			break;
		goto almostWin;
	case BA_DA:
		if (pos.pawn_bottomcount<strong>() > 0) {
			//弱方王侧面露脸，且羊角士，且兵处于低位（防抽）， 且马方低兵，且与弱王异侧  和势
			if(pos.is_king_flank_clear<weak>() && not_z(pos.pieces(weak, ADVISOR) & AreaAdvisorCavel) 
				&& (pos.pawn_lowcount<weak>() == 1 || pos.pawn_bottomcount<weak>() > 0) 
				&& not_z(bcTmp = (pos.pieces(strong, PAWN) & LowRankBC))
				&& !same_flank(lsb(bcTmp) , pos.square(weak, KING))
				)
				break;
			goto almostWin;
		}
		else {
			if (pos.pawn_bottomcount<weak>() == 0) {
				//弱方没有底兵的情况：
				//马方有士象：
				//马方兵在拍门位，王异侧露脸，， 不管对方高兵低兵，都胜
				//马方有下三路兵且与对方王同侧， 不管对方高兵低兵，都胜
				//马方高兵 不管对方高兵低兵，都胜
				//马方无士象
				//弱方王不在侧面露脸，马方胜
				//弱方没有高兵且没有下三线兵，马方有高兵or兵与弱方王同侧 胜
				if (pos.defense_count(strong) > 0) {
					if (cnpawn_attack<strong>(pos))
						goto almostWin;
					if (pos.pawn_low3count<strong>() == 1 && same_flank(pos.square(strong, PAWN), pos.square(weak, KING)))
						goto almostWin;
					if (pos.pawn_highcount<strong>() > 0)
						goto almostWin;
				}
				else {
					if(!pos.is_king_flank_clear<weak>())
						goto almostWin;
					else if(pos.pawn_highcount<weak>() == 0 && pos.pawn_low3count<weak>() == 0 
						&& (pos.pawn_highcount<strong>() > 0 || same_flank(pos.square(strong, PAWN), pos.square(weak,KING))))
						goto almostWin;

				}
			}
			else {
				//弱方有底兵，马方没高兵，也没有中象兵，和
				if(pos.pawn_highcount<strong>() == 0 && pos.pawn_low3count<strong>() == 0)
					break;
			}

			//弱方王在侧面露脸，( (马方兵在下二线，且与弱方王异侧) or 在中象位置) ，和棋
			if (pos.pawn_highcount<strong>() == 0 && pos.is_king_flank_clear<weak>()) {
				if(pos.pawn_midbishop<strong>())
					break;
				if (pos.pawn_low3count<strong>() == 0 && !same_flank(pos.square(strong, PAWN), pos.square(weak, KING)))
					break;

			}

				

			//其他情况，有一定的胜机
			return value_draw_zoom<1>(pos, score);

		}

	case BA_DBA:
		if (homepawn_threeseven<strong>(pos))
			break;

		if (cnpawn_attack<strong>(pos)) {
			update_score(score, strong, BishopValueEg);
			goto almostWin;
		}
		if (pos.pawn_bottomcount<strong>() == 0) {
			//弱方王在侧面露脸， 强方兵不在高位，或兵不和王同侧 ，和
			if(good_defense_against_kp<weak>(pos))
				break;
		}
		goto almostWin;

	case BA_BDA:
		//要考虑马方有底兵 和 弱方有底兵
		//高兵取胜路径，先吃掉象
		//低兵和棋路径， 马方兵在下二线，且异侧， 弱王在侧面露脸，且象与王异侧，或有底兵
		if (pos.pawn_bottomcount<strong>() > 0)
			goto almostWin;
		break;
	default:
		break;
	}

//drawEnd:
	return value_draw_zoom<4>(pos, score);

almostWin:
	return value_final(pos, score);


}

template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::kn_k_2p_1p(const Position& pos, Score& score) const {
	return value_final(pos, score);
}

//马光王对双高兵	马有老兵和， 无老兵， 兵方有双高兵， 输
//三兵例胜马士（相，双相）
template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::kn_k_0p_2p(const Position& pos, Score& score) const {
	I_AM_WEAK

	if (pos.pawn_onkingcount<weak>() == 0)
		return value_general_final<weak>(pos, knight_defense<strong>(pos));
	
	int nb = pos.pawn_nobottomcount<weak>();
	auto ba = pos.ba_number<strong>();
	Value v = nb * PAWN_END_130P;

	if (nb == 2) {
		if(ba > BA_ZERO)
			goto drawEnd;
		else {
			if (pos.pawn_validcount<weak>() == 0 || pos.pawn_bottomcount<strong>() > 0)
				goto drawEnd;

			if (pos.pawn_crhighcount<weak>() >= 2) {

				if (popcount(pos.pieces(weak, PAWN) & AreaMid3File) == 2)
					v += PAWN_END_90P;
				goto almostWin;
			}
		}
	}
	else {
		auto vp = pos.pawn_validcount<weak>();

		if (vp >= 5)
			goto almostWin;

		switch (ba)
		{
		case BA_ZERO:
			goto almostWin;
		case BA_BS:
			if (vp >= 3)
				goto almostWin;
			break;
		case BA_AD:
		case BA_DB:
			if (vp >= 3 && pos.pawn_bottomcount<strong>() == 0)
				goto almostWin;
			break;
		case BA_BA:
		case BA_DA:
			if (vp >= 4)
				goto almostWin;
			break;
		default:
			break;
		}
	}


drawEnd:
	update_score(score, weak, v);
	if(nb >= 4)
		return value_draw_zoom<2>(pos, score);		//3个兵或以上， 优势比2个兵应该要大，所以优势缩小倍数为4 
	else
		return value_draw_zoom<4>(pos, score);

almostWin:
	return update_score(pos, score, weak, v);

}


//和棋情况  
//兵方占优情况
//一般情况： 马方占优
template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::kn_k_1p_2p(const Position& pos, Score& score) const {
	I_AM_WEAK

	auto baStrong = pos.ba_number<strong>();
	auto baWeak = pos.ba_number<weak>();

	int nb = pos.pawn_nobottomcount<weak>();

	if (nb == 2) {
		//马兵对双兵
		//马方有胜机， 马方高兵（拍门） 弱方双象，单士象或以下
		//和局  马方无老兵， 弱方 （士象全 or 双士象）  or (双兵在中路拉手， 且有双士) 
		if (pos.pawn_bottomcount<strong>() == 0) {
			if (baWeak >= BA_BDA || (baWeak >= BA_DA && pos.is_pawns_partner_midhigh<weak>()))
				return value_draw_zoom<2>(pos, score);

			if(baWeak == BA_DBA && pos.pawn_crhighmidcount<weak>() > 0)
				return value_draw_zoom<1>(pos, score);
		}
	}
	else if (nb == 3) {
		//马兵对三兵 和棋情况   马方无老兵， >=双士，or 单士象， 弱方 （士象全 or 双士象）  or (双兵在中路拉手， 且有双士) 
		if (pos.pawn_bottomcount<strong>() == 0) {
			if(baStrong >= BA_DA || baStrong == BA_BA)
				if (baWeak >= BA_BDA || (baWeak >= BA_DA && pos.is_pawns_partner_midhigh<weak>()))
					return value_draw_zoom<2>(pos, score);
		}

	}

	return value_final(pos, score);


}

template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::kn_k_2p_2p(const Position& pos, Score& score) const {
	return value_final(pos, score);
}
