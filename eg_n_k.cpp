#include "endgame.h"

//�о�Ҫ���ǵ����أ�
//˫���ı���Ŀ
//˫��ʿ����Ŀ
//���Ʒ�ʿ����Ƿ�Ӧ��С
//һ����ʿ��һ�����������Ӧ��ε���
//���Ʒ�ʿ��Ӧ������
//�Ƿ񽻻���
//�Ƿ񽻻�ʿ��
//�Ƿ����ʿ�� ����ʿ / ���˫ʿ��˫�󣬻�ʿ + ���3��ʿ��
//����λ�ã�δ���ӣ���ͷ���� ���ӱ��� �߱�����·�ͱ��� ��·�ͱ��� ����������ͷ���� �ױ���
//2�����ϱ�����ʱӦע��������������³壬���⼷��ͬһ��
//���λ�ã�����λ�����λ
//ʿ���λ�ã��Է�����ʱ
//ǣ�����⣬ ��ǣ��
//���Ƿ�ռ�У��Ƿ�¶�����Ƿ����¶���� �Ƿ����ڶ�
//����ʤ��		��������������λ��û������Ҫ�󣬲���Ҫ�ر��ȡʤ�ֶ�
//���Ժ���		������ֻ��һ��������������2����


//��ʿ��ֵ���
//������������ڲ���¶�����۷�
//����2�����Ϲ��ӱ�����������˫��������ӷǵ��ߵ�����Ҳ�û�б����۷�
//���б�����������һ��ʿ������������2�����ӱ�������ռ400���������ƣ�����������ӱ�����·���֣� �ӷ�
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
					//������·�� �¶�·��������·�ı������ڲ�ͬ��
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
					//������·�� �¶�·��������·�ı������ڲ�ͬ��
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
//�������ϱ�����
//��ʤ���� 
//��ʤʿ
//�������� ʤ�ʣ�14.56%  ���ϱ�ʤ
//������ʿ�� ���ϱ�ʤ
//������˫ʿ ���ϱ�ʤ
//������˫�� ˫��ʿ��˫ʿ��ʿ��ȫ ���ϱ�Ҳ�Ǻ�
template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::kn_k_0p_0p(const Position& pos, Score& score) const {
	//��ʤ����
	//��ʤ��ʿ �����ܱ�ǣ�ƣ�
	//��Ե�����ʤ��
	//������
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
            //������·¶�����Է��������ͬһ�� ʤ
            if (pos.is_king_mid_clear<strong>()) {
                if (same_flank(pos.square(weak, KING), pos.square(weak, BISHOP)))
                    goto almostWin;
            }
            break;
        case BA_BA:
            if (pos.pawn_bottomcount<strong>() > 0)			//��ױ�ʤ��ʿ�� , ���Ѷȣ���Ӧ��win����
                goto almostWin;
            break;
        case BA_DA:
            if (pos.pawn_bottomcount<strong>() > 0)			//��ױ�ʤ˫ʿ
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
//���ʤ����		�����ϱ�Ҳʤ
//���ʤ��		�����ϱ�ʤ
//�����ʤʿ		�����ϱ��������ϱ��������¶�·�� ̫�����κ�
//�����ʤʿ��	�����ϱ��������ϱ��������¶�·�� ̫�����κ�
//���ʤ˫ʿ		�����ϱ�����������ϱ��������¶�·�� ̫�����κ�
//���ʤ˫��		���ϱ�Ҳʤ	Ψһ���壺�����ϱ� �����ϱ����ұ�������·δ����
//�����˫��ʿ	
//�����˫ʿ��	�߱�׽�����ʤ
//�����ʿ��ȫ	�����ϱ��������ϱ���ʤ	

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
		//��һ������Ǻ��� �еױ������ڲ���¶����̫�����Σ���û�еױ�����һ�������¶�·�ͱ�������Է��������
		if (pos.pawn_bottomcount<weak>() > 0 && pos.pawn_low3count<strong>() == 0 
			&& pos.pawn_bottomcount<strong>() == 0 && good_defense_against_kp<weak>(pos))
			break;
		goto almostWin;
	case BA_DA:
		//��һ������Ǻ��� �еױ������ڲ���¶������û�еױ���û�и߱��� ����Է��������
		if (pos.pawn_bottomcount<weak>() > 0 && pos.is_king_flank_clear<weak>()
			&& pos.pawn_highcount<strong>() == 0
			&& !same_flank(pos.square(strong, PAWN), pos.square(weak, KING)))
			break;

		goto almostWin;
	case BA_DB:
		//�����߱����Թ��ӣ����õ���  ���˫���еױ�, �����������ߣ�û�й��ӣ���û�еױ� ��
		if (pos.pawn_bottomcount<weak>() > 0 && homepawn_threeseven<strong>(pos)
			&& pos.pawn_bottomcount<strong>() == 0)
			break;
		goto almostWin;

		
	case BA_DBA:
		//Ҫ���ǵ����⣬�����߱��ܷ���ӣ� �߱�ȡʤ·���� �ͱ�����·�������еױ��������еױ�
		//ȡʤ·���������ߵ�����������һ��¶������������
		if (homepawn_threeseven<strong>(pos))
			break;
		if (pos.pawn_bottomcount<strong>() > 0)
			goto almostWin;

		//��ռ�ߵ���������¶��������һ���ߵ����Է�����������¥�� ����ҪӮ��
		if (pos.is_king_flank_clear<strong>() && !pos.is_king_top<weak>()){
			s = pos.pawn_monsterknock(strong);
			if (s != SQ_NONE && !same_flank(s, pos.square(strong, KING))) {
				update_score(score, strong, PawnValueEg);
				goto almostWin;
			}
		}
		//��̫������
		if(!good_defense_against_kp<weak>(pos))
			goto almostWin;
		break;
	case BA_BDA:
		//Ҫ�������еױ� �� �����еױ�
		//�߱�ȡʤ·�����ȳԵ���
		//��ѱ���ס���ұ����϶��ߣ��ӷ�
		bcTmp = pos.pieces(weak, BISHOP) & AreaBorderFile;
		if (not_z(bcTmp)) {
			s = lsb(bcTmp);
			if (is_same_rank(s, pos.square(strong, KNIGHT)) && file_distance(s, pos.square(strong, KNIGHT)) == 1
				&& pos.pawn_crhighcount<strong>() == 1) {
				update_score(score, strong, BISHOP_END_70P);
				goto almostWin;
			}
		}
		//�ͱ�����·���� ��û�и߱���û�еױ���  �����ڲ���¶������������������࣬or �����еױ�
		if(pos.pawn_bottomcount<strong>() == 0 && pos.pawn_highcount<strong>() == 0 && pos.is_king_flank_clear<weak>()
			&& (pos.pawn_bottomcount<weak>() > 0 || !same_flank(pos.square(strong, PAWN), pos.square(weak, KING))))
			break;

		goto almostWin;
	default:
		if (homepawn_threeseven<strong>(pos))		//������δ���ӱ��޷����ӣ� ��
			break;
		if (pos.pawn_bottomcount<strong>() > 0)				//���еױ����ױ���ֵ����ʿ���󣬸��ױ��ӷ֣� ʤ�����Դ�
			goto almostWin;

		//�����¶����ߵ������ڲ���¶�����������࣬���ڹ���λ�ã����ǵ��͵Ĺ������ӷ֣��䲻һ��Ӯ��
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

//��Ա������� �����û�й��ӣ���û�ϱ�����ʤ�� 
//��ͱ�����
template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::kn_k_0p_1p(const Position& pos, Score& score) const {
	Value v = king_clear<strong>(pos) + knight_attack<strong>(pos);

	I_AM_WEAK

	if (pos.zero_ba(weak) && pos.pawn_homecount<weak>() == 1 && pos.pawn_bottomcount<weak>() == 0)
		return value_draw_zoom<1>(pos, score);

	return value_draw_zoom<4>(pos, score);
}
//���ʤ������	�����ϱ�Ҳʤ
//���ʤ����		�����ϱ�ʤ
//����Ա�ʿ		��߱�ʤ�� �����ϱ��������¶�·�� ̫�����κ�
//����Ա�ʿ��	��߱�ʤ�������ϱ��������¶�·�� ̫�����κ�
//���ʤ��˫��	Ψһ���壺�����ϱ� �����ϱ����ұ�������·δ����
//���ʤ��˫ʿ	�����ϱ�����������ϱ��������¶�·�� ̫�����κ�
//����Ա�˫��ʿ	��߱�ʤ
//����Ա�˫ʿ��	�����ϱ�ʤ
//�����ʿ��ȫ	��
template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::kn_k_1p_1p(const Position& pos, Score& score) const {
	BitboardC bcTmp;
	I_AM_WEAK
	auto ba = pos.ba_number<weak>();
	//��߱�ʤ��ʿ 
	//��ͱ�������ʿ �� ̫������
	//��߱�������˫ʿ
	switch (ba)
	{
	case BA_ZERO:
	case BA_BS:
		goto almostWin;
	case BA_AD:
		//����·�ߣ�������λ����
		if (pos.pawn_midbishop<strong>()) {
			update_score(score, strong, BishopValueEg);
			goto almostWin;
		}
		//��ͱ�������ʿ �� ̫������
		if (pos.pawn_low2count<strong>() == 1 && pos.pawn_bottomcount<strong>() == 0 
			&& pos.pawn_validcount<weak>() > 0 && pos.is_king_flank_clear<weak>()
			&& is_same_file(pos.square(weak, ADVISOR), pos.square(weak, KING))
			&& !same_flank(pos.square(strong, PAWN), pos.square(weak, KING))) 
			break;
		//�����еױ����ı���
		goto almostWin;
	case BA_BA:
		//��ͱ�������ʿ �� ̫������
		if (pos.pawn_low2count<strong>() == 1 && pos.pawn_validcount<weak>() > 0 && pos.pawn_bottomcount<strong>() == 0
			&& pos.is_king_flank_clear<weak>() && is_same_file(pos.square(weak, ADVISOR), pos.square(weak, KING))
			&& !same_flank(pos.square(strong, PAWN), pos.square(weak, KING)))
			break;
		//�����еױ����ı���
		goto almostWin;
	case BA_DB:
		//����������δ���ӱ�������ȥ����� 
		if (homepawn_threeseven<strong>(pos) && pos.pawn_bottomcount<weak>() > 0 && pos.pawn_bottomcount<strong>() == 0)
			break;
		goto almostWin;
	case BA_DA:
		if (pos.pawn_bottomcount<strong>() > 0) {
			//����������¶���������ʿ���ұ����ڵ�λ�����飩�� �����ͱ��������������  ����
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
				//����û�еױ��������
				//����ʿ��
				//����������λ�������¶������ ���ܶԷ��߱��ͱ�����ʤ
				//��������·������Է���ͬ�࣬ ���ܶԷ��߱��ͱ�����ʤ
				//���߱� ���ܶԷ��߱��ͱ�����ʤ
				//����ʿ��
				//���������ڲ���¶������ʤ
				//����û�и߱���û�������߱������и߱�or����������ͬ�� ʤ
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
				//�����еױ�����û�߱���Ҳû�����������
				if(pos.pawn_highcount<strong>() == 0 && pos.pawn_low3count<strong>() == 0)
					break;
			}

			//�������ڲ���¶����( (�������¶��ߣ��������������) or ������λ��) ������
			if (pos.pawn_highcount<strong>() == 0 && pos.is_king_flank_clear<weak>()) {
				if(pos.pawn_midbishop<strong>())
					break;
				if (pos.pawn_low3count<strong>() == 0 && !same_flank(pos.square(strong, PAWN), pos.square(weak, KING)))
					break;

			}

				

			//�����������һ����ʤ��
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
			//�������ڲ���¶���� ǿ�������ڸ�λ�����������ͬ�� ����
			if(good_defense_against_kp<weak>(pos))
				break;
		}
		goto almostWin;

	case BA_BDA:
		//Ҫ�������еױ� �� �����еױ�
		//�߱�ȡʤ·�����ȳԵ���
		//�ͱ�����·���� �������¶��ߣ�����࣬ �����ڲ���¶��������������࣬���еױ�
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

//�������˫�߱�	�����ϱ��ͣ� ���ϱ��� ������˫�߱��� ��
//������ʤ��ʿ���࣬˫�ࣩ
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
		return value_draw_zoom<2>(pos, score);		//3���������ϣ� ���Ʊ�2����Ӧ��Ҫ������������С����Ϊ4 
	else
		return value_draw_zoom<4>(pos, score);

almostWin:
	return update_score(pos, score, weak, v);

}


//�������  
//����ռ�����
//һ������� ��ռ��
template<EndgameType E/*, typename T = eg_type<E>*/>
template<Color strong> inline Value Endgame<E>::kn_k_1p_2p(const Position& pos, Score& score) const {
	I_AM_WEAK

	auto baStrong = pos.ba_number<strong>();
	auto baWeak = pos.ba_number<weak>();

	int nb = pos.pawn_nobottomcount<weak>();

	if (nb == 2) {
		//�����˫��
		//����ʤ���� ���߱������ţ� ����˫�󣬵�ʿ�������
		//�;�  �����ϱ��� ���� ��ʿ��ȫ or ˫ʿ��  or (˫������·���֣� ����˫ʿ) 
		if (pos.pawn_bottomcount<strong>() == 0) {
			if (baWeak >= BA_BDA || (baWeak >= BA_DA && pos.is_pawns_partner_midhigh<weak>()))
				return value_draw_zoom<2>(pos, score);

			if(baWeak == BA_DBA && pos.pawn_crhighmidcount<weak>() > 0)
				return value_draw_zoom<1>(pos, score);
		}
	}
	else if (nb == 3) {
		//��������� �������   �����ϱ��� >=˫ʿ��or ��ʿ�� ���� ��ʿ��ȫ or ˫ʿ��  or (˫������·���֣� ����˫ʿ) 
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
