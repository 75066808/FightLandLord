#include "model.h"

qint8 Player::connectNum = 0;
qint8 Player::connectFailNum = 0;
qint8 Player::readyNum = 0;
qint8 Player::dealCardNum = 0;
qint8 Player::dealLandNum = 0;

qint8 Player::chooseLandNum = 0;
qint8 Player::skipLandNum = 0;
qint8 Player::chooseTurnNum = 0;
qint8 Player::playCardNum = 0;
qint8 Player::skipCardNum = 0;
qint8 Player::playTurnNum = 0;
qint8 Player::playnkTurnNum = 0;
qint8 Player::winGameNum = 0;
qint8 Player::loseGameNum = 0;


Player::Player() :selected(std::make_shared<RuleCardSet>()),
onHand(std::make_shared<RuleCardSet>()),
status(std::make_shared<int>(0)),
m_Num(std::make_shared<int>(0)),
s_Num(std::make_shared<int>(0)),
m_Card(std::make_shared<CARD20>()),
m_Selected(std::make_shared<BOOL20>()),
o_Card(std::make_shared<CARD20>()),
onTable(std::make_shared<RuleCardSet>())
{
}

Player::~Player()
{
}

void Player::modelCommandSlot(std::shared_ptr<Signal> signal) {
	//qDebug() << "View Model to Model" << endl;
	if (*status == SELF_DIS_CONNECT && signal->signalType == CONNECT) {
		emit modelCommandSignal(signal);
	}
	else if (*status == SELF_CONNECT && signal->signalType == READY) {
		emit modelCommandSignal(signal);
	}
	else if (*status == SELF_CONNECT && signal->signalType == DISCONNECT) {
		emit modelCommandSignal(signal);
	}
	else if (*status == SELF_CHOOSE_TURN && signal->signalType == CHOOSE_LANDLORD) {
		emit modelCommandSignal(signal);
	}
	else if (*status == SELF_CHOOSE_TURN && signal->signalType == SKIP_LANDLORD) {
		emit modelCommandSignal(signal);
	}
	else if ((*status == SELF_TURN || *status == SELF_NOSKIP_TURN) && signal->signalType == SELECT)  //this is for selected
	{
		int index = (signal->cardTransfer)[0];
		if (m_Selected->bools[index] == 0) {
			m_Selected->bools[index] = 1;
			CARDSET zero;
			zero.add(m_Card->cards[index]);
			(*selected) = (*selected) + zero;
			//for some modify-----------this is for updating o_card and s_Num
			CARDSET origin;
			for (int i = 0; i < (*s_Num); i++) {
				origin.add(o_Card->cards[i]);
			}
			index = 0;
			CARDSET tmp = zero + origin;
			while (!tmp.setIsEmpty()) {
				o_Card->cards[index] = tmp.setPop();
				index++;
			}
			(*s_Num) = index;
			signal->valid = 1;
		}
		else {
			m_Selected->bools[index] = 0;
			CARDSET zero;
			zero.add(m_Card->cards[index]);
			(*selected) = (*selected) - zero;
			//for some modify-----------this is for updating o_card and s_Num
			CARDSET origin;
			for (int i = 0; i < (*s_Num); i++) {
				origin.add(o_Card->cards[i]);
			}
			index = 0;
			CARDSET tmp = origin - zero;
			while (!tmp.setIsEmpty()) {
				o_Card->cards[index] = tmp.setPop();
				index++;
			}
			(*s_Num) = index;
			signal->valid = 1;
		}
		emit modelNotificationSignal(signal);
	}
	else if ((*status == SELF_TURN || *status == SELF_NOSKIP_TURN) && signal->signalType == PLAY_CARD) //this is for try to hand cards
	{
		if (((*onTable) < (*selected)) == 1) {
		//if (1) {
			//for some modify
			CARDSET origin;
			for (int i = 0; i < (*s_Num); i++) {
				origin.add(o_Card->cards[i]);
			}
			signal->cardTransfer = origin.tranToSig();
			emit modelCommandSignal(signal);
		}
		else {
			//for some modify
			signal->valid = 0;
			emit modelNotificationSignal(signal);
		}
	}
	else if (*status == SELF_TURN && signal->signalType == SKIP_CARD) //this is for try to hand cards
	{
		//if (((*onTable) < (*selected)) == 1) {
		if (1) {
			emit modelCommandSignal(signal);
		}
	}
	else if (*status % 3 == 0 && signal->signalType == CONT) {
		emit modelCommandSignal(signal);
	}
	else if (*status % 3 == 0 && signal->signalType == DISCONNECT) {
		emit modelCommandSignal(signal);
	}
}

void Player::modelNotificationSlot(std::shared_ptr<Signal> signal) {
	//qDebug() << "Socket to Model" << endl;
	if (signal->signalType == CONNECT_SUCCESS) {
		if (*status == 0) {
			if (signal->playerType[SELF] == 1)* status = SELF_CONNECT;
			else if (signal->playerType[SELF] == 2)* status = SELF_READY;
			else if (signal->playerType[SELF] == 0)* status = SELF_DIS_CONNECT;
		}
		else if (*status == 1) {
			if (signal->playerType[UPPERHOUSE] == 1)* status = UPPER_CONNECT;
			else if (signal->playerType[UPPERHOUSE] == 2)* status = UPPER_READY;
			else if (signal->playerType[UPPERHOUSE] == 0)* status = UPPER_DIS_CONNECT;
		}
		else if (*status == 2) {
			if (signal->playerType[LOWERHOUSE] == 1)* status = LOWER_CONNECT;
			else if (signal->playerType[LOWERHOUSE] == 2)* status = LOWER_READY;
			else if (signal->playerType[LOWERHOUSE] == 0)* status = LOWER_DIS_CONNECT;
		}

		selected->clear();
		onHand->clear();
		onTable->clear();
		(*m_Num) = 0;
		(*s_Num) = 0;
		m_Card->clear();
		m_Selected->clear();
		o_Card->clear();

		connectNum++;
		if (connectNum == 3) {
			emit modelNotificationSignal(signal);
			connectNum = 0;
		}

	}
	else if (signal->signalType == CONT) {
		int sig = 0;
		if (*status % 3 == 0) {
			if (signal->playerType[SELF] == 1) {
				*status = SELF_CONNECT;
				sig = 1;
			}
			else if (signal->playerType[SELF] == 2) {
				*status = SELF_READY;
				sig = 1;
			}
			else if (signal->playerType[SELF] == 0)* status = SELF_DIS_CONNECT;
		}
		else if (*status % 3 == 1) {
			if (signal->playerType[UPPERHOUSE] == 1)* status = UPPER_CONNECT;
			else if (signal->playerType[UPPERHOUSE] == 2)* status = UPPER_READY;
			else if (signal->playerType[UPPERHOUSE] == 0)* status = UPPER_DIS_CONNECT;
		}
		else if (*status % 3 == 2) {
			if (signal->playerType[LOWERHOUSE] == 1)* status = LOWER_CONNECT;
			else if (signal->playerType[LOWERHOUSE] == 2)* status = LOWER_READY;
			else if (signal->playerType[LOWERHOUSE] == 0)* status = LOWER_DIS_CONNECT;
		}
		if (sig == 1) {
			selected->clear();
			onHand->clear();
			onTable->clear();
			(*m_Num) = 0;
			(*s_Num) = 0;
			m_Card->clear();
			m_Selected->clear();
			o_Card->clear();
		}

		loseGameNum++;
		if (loseGameNum == 3) {
			emit modelNotificationSignal(signal);
			loseGameNum = 0;
		}

	}
	else if (signal->signalType == DISCONNECT) {
		if (*status % 3 == 0) {
			if (signal->playerType[SELF] == 1)* status = SELF_CONNECT;
			else if (signal->playerType[SELF] == 2)* status = SELF_READY;
			else if (signal->playerType[SELF] == 0)* status = SELF_DIS_CONNECT;
		}
		else if (*status % 3 == 1) {
			if (signal->playerType[UPPERHOUSE] == 1)* status = UPPER_CONNECT;
			else if (signal->playerType[UPPERHOUSE] == 2)* status = UPPER_READY;
			else if (signal->playerType[UPPERHOUSE] == 0)* status = UPPER_DIS_CONNECT;
		}
		else if (*status % 3 == 2) {
			if (signal->playerType[LOWERHOUSE] == 1)* status = LOWER_CONNECT;
			else if (signal->playerType[LOWERHOUSE] == 2)* status = LOWER_READY;
			else if (signal->playerType[LOWERHOUSE] == 0)* status = LOWER_DIS_CONNECT;
		}

		selected->clear();
		onHand->clear();
		onTable->clear();
		(*m_Num) = 0;
		(*s_Num) = 0;
		m_Card->clear();
		m_Selected->clear();
		o_Card->clear();
		

		connectFailNum++;
		if (connectFailNum == 3) {
			emit modelNotificationSignal(signal);
			connectNum = 0;
		}
	}
	else if (signal->signalType == READY) {
		if (*status % 3 == 0) {
			if (signal->playerType[SELF] == 1)* status = SELF_CONNECT;
			else if (signal->playerType[SELF] == 2)* status = SELF_READY;
			else if (signal->playerType[SELF] == 0)* status = SELF_DIS_CONNECT;
		}
		else if (*status % 3 == 1) {
			if (signal->playerType[UPPERHOUSE] == 1)* status = UPPER_CONNECT;
			else if (signal->playerType[UPPERHOUSE] == 2)* status = UPPER_READY;
			else if (signal->playerType[UPPERHOUSE] == 0)* status = UPPER_DIS_CONNECT;
		}
		else if (*status % 3 == 2) {
			if (signal->playerType[LOWERHOUSE] == 1)* status = LOWER_CONNECT;
			else if (signal->playerType[LOWERHOUSE] == 2)* status = LOWER_READY;
			else if (signal->playerType[LOWERHOUSE] == 0)* status = LOWER_DIS_CONNECT;
		}

		readyNum++;
		if (readyNum == 3) {
			emit modelNotificationSignal(signal);
			readyNum = 0;
		}
	}
	else if (signal->signalType == CHOOSE_LANDLORD) {
		if (signal->playerType[SELF] == 1 && *status == SELF_CHOOSE_TURN)* status = SELF_CHOOSE_LAND;
		else if (signal->playerType[UPPERHOUSE] == 1 && *status == UPPER_CHOOSE_TURN)* status = UPPER_CHOOSE_LAND;
		else if (signal->playerType[LOWERHOUSE] == 1 && *status == LOWER_CHOOSE_TURN)* status = LOWER_CHOOSE_LAND;

		chooseLandNum++;
		if (chooseLandNum == 3) {
			emit modelNotificationSignal(signal);
			chooseLandNum = 0;
		}
	}
	else if (signal->signalType == SKIP_LANDLORD) {
		if (signal->playerType[SELF] == 1 && *status == SELF_CHOOSE_TURN)* status = SELF_SKIP_LAND;
		else if (signal->playerType[UPPERHOUSE] == 1 && *status == UPPER_CHOOSE_TURN)* status = UPPER_SKIP_LAND;
		else if (signal->playerType[LOWERHOUSE] == 1 && *status == LOWER_CHOOSE_TURN)* status = LOWER_SKIP_LAND;

		skipLandNum++;
		if (skipLandNum == 3) {
			emit modelNotificationSignal(signal);
			skipLandNum = 0;
		}
	}
	else if (signal->signalType == CHOOSE_TURN) {
		if (signal->playerType[SELF] == 1 && *status == SELF_NOT_CHOOSE_TURN)* status = SELF_CHOOSE_TURN;
		else if (signal->playerType[UPPERHOUSE] == 1 && *status == UPPER_NOT_CHOOSE_TURN)* status = UPPER_CHOOSE_TURN;
		else if (signal->playerType[LOWERHOUSE] == 1 && *status == LOWER_NOT_CHOOSE_TURN)* status = LOWER_CHOOSE_TURN;

		chooseTurnNum++;
		if (chooseTurnNum == 3) {
			emit modelNotificationSignal(signal);
			chooseTurnNum = 0;
		}
	}
	else if (signal->signalType == DEAL_CARD) {
		QByteArray whole = signal->cardTransfer;
		QByteArray here;
		here.resize(34);
		int start;
		start = *status % 3 == 0 ? 40 :
			(*status % 3 == 1 ? 6 : 74);

		for (int i = 0; i < 34; i++) {
			here[i] = whole[start + i];
		}
		(*onHand) = RuleCardSet(here);
		int index = 0;
		CARDSET tmp = here;
		while (!tmp.setIsEmpty()) {
			m_Card->cards[index] = tmp.setPop();
			index++;
		}
		(*m_Num) = index;

		CARDSET zero;
		(*selected) = zero;
		m_Selected->clear();
		o_Card->clear();
		(*s_Num) = 0;

		if (*status % 3 == 0) {
			if (signal->playerType[SELF] == 1) *status = SELF_CHOOSE_TURN;
			else *status = SELF_NOT_CHOOSE_TURN;
		}
		else if (*status % 3 == 1) {
			if (signal->playerType[UPPERHOUSE] == 1)  *status = UPPER_CHOOSE_TURN;
			else *status = UPPER_NOT_CHOOSE_TURN;
		}
		else {
			if (signal->playerType[LOWERHOUSE] == 1)* status = LOWER_CHOOSE_TURN;
			else *status = LOWER_NOT_CHOOSE_TURN;
		}
		dealCardNum++;
		if (dealCardNum == 3) {
			emit modelNotificationSignal(signal);
			dealCardNum = 0;
		}
	}
	else if (signal->signalType == DEAL_LANDLORD) {
		if ((*status) % 3 == 0 && signal->playerType[SELF] == 1
			|| (*status) % 3 == 1 && signal->playerType[UPPERHOUSE] == 1
			|| (*status) % 3 == 2 && signal->playerType[LOWERHOUSE] == 1
			)
		{
			QByteArray whole = signal->cardTransfer;
			QByteArray here;
			here.resize(6);
			int start = 0;  //modify here
			for (int i = 0; i < 6; i++) {
				here[i] = whole[start + i];
			}
			(*onHand) = (*onHand) + RuleCardSet(here);
			CARDSET origin;
			for (int i = 0; i < (*m_Num); i++) {
				origin.add(m_Card->cards[i]);
			}
			int index = 0;
			CARDSET tmp = here + origin;
			while (!tmp.setIsEmpty()) {
				m_Card->cards[index] = tmp.setPop();
				index++;
			}
			(*m_Num) = index;
			onTable->clear();
			*status = SELF_NOSKIP_TURN + (*status) % 3;
		}
		else {
			*status = SELF_PLAY + (*status) % 3;
		}
		dealLandNum++;
		if (dealLandNum == 3) {
			emit modelNotificationSignal(signal);
			dealLandNum = 0;
		}
	}
	else if (signal->signalType == PLAY_CARD) //this is for handing cards
	{
		if (*status % 3 == 0 && signal->playerType[SELF] == 1
			|| *status % 3 == 1 && signal->playerType[UPPERHOUSE] == 1
			|| *status % 3 == 2 && signal->playerType[LOWERHOUSE] == 1
			) {
			CARDSET zero;
			(*selected) = zero;
			(*onTable) = RuleCardSet(signal->cardTransfer);
			m_Selected->clear();
			(*onHand) = (*onHand) - RuleCardSet(signal->cardTransfer);
			CARDSET origin;
			for (int i = 0; i < (*m_Num); i++) {
				origin.add(m_Card->cards[i]);
			}
			int index = 0;
			CARDSET tmp = origin - signal->cardTransfer;
			while (!tmp.setIsEmpty()) {
				m_Card->cards[index] = tmp.setPop();
				index++;
			}
			(*m_Num) = index;

			CARDSET handOut = signal->cardTransfer;
			index = 0;
			while (!handOut.setIsEmpty()) {
				o_Card->cards[index] = handOut.setPop();
				index++;
			}
			(*s_Num) = index;

			(*status) = SELF_PLAY + *status % 3;
		}
		playCardNum++;
		if (playCardNum == 3) {
			emit modelNotificationSignal(signal);
			playCardNum = 0;
		}
	}
	else if (signal->signalType == SKIP_CARD) //this is for skipping cards
	{
		if (*status % 3 == 0 && signal->playerType[SELF] == 1
			|| *status % 3 == 1 && signal->playerType[UPPERHOUSE] == 1
			|| *status % 3 == 2 && signal->playerType[LOWERHOUSE] == 1
			) {
			CARDSET zero;
			(*selected) = zero;
			m_Selected->clear();
			o_Card->clear();
			(*s_Num) = 0;

			(*status) = SELF_SKIP + *status % 3;
		}
		skipCardNum++;
		if (skipCardNum == 3) {
			emit modelNotificationSignal(signal);
			skipCardNum = 0;
		}
	}
	else if (signal->signalType == PLAY_TURN) //this is for turn changing
	{
		if (*status % 3 == 0 && signal->playerType[SELF] == 1
			|| *status % 3 == 1 && signal->playerType[UPPERHOUSE] == 1
			|| *status % 3 == 2 && signal->playerType[LOWERHOUSE] == 1
			) {
			CARDSET zero;
			(*selected) = zero;
			m_Selected->clear();
			o_Card->clear();
			(*s_Num) = 0;

			(*status) = SELF_TURN + *status % 3;
		}
		playTurnNum++;
		if (playTurnNum == 3) {
			emit modelNotificationSignal(signal);
			playTurnNum = 0;
		}
	}
	else if (signal->signalType == PLAY_TURN_NO_SKIP) //this is for special turn changing
	{
		if (*status % 3 == 0 && signal->playerType[SELF] == 1
			|| *status % 3 == 1 && signal->playerType[UPPERHOUSE] == 1
			|| *status % 3 == 2 && signal->playerType[LOWERHOUSE] == 1
			) {
			CARDSET zero;
			onTable->clear();
			(*selected) = zero;
			m_Selected->clear();
			o_Card->clear();
			(*s_Num) = 0;

			(*status) = SELF_NOSKIP_TURN + *status % 3;
		}
		playnkTurnNum++;
		if (playnkTurnNum == 3) {
			emit modelNotificationSignal(signal);
			playnkTurnNum = 0;
		}
	}
	else if (signal->signalType == WIN_GAME) //this is for win
	{
		if (*status % 3 == 0) {
			if (signal->playerType[SELF] == 1) (*status) = SELF_WIN;
			else (*status) = SELF_LOSE;
		}
		else if (*status % 3 == 1) {
			if (signal->playerType[UPPERHOUSE] == 1) (*status) = UPPER_WIN;
			else (*status) = UPPER_LOSE;
		}
		else if (*status % 3 == 2) {
			if (signal->playerType[LOWERHOUSE] == 1) (*status) = LOWER_WIN;
			else (*status) = LOWER_LOSE;
		}

		winGameNum++;
		if (winGameNum == 3) {
			emit modelNotificationSignal(signal);
			winGameNum = 0;
		}
	}
	else if (signal->signalType == COM_PLAY) //this is for constraint play
	{
		if (*status % 3 == 0) {
			RuleCardSet tmp = onHand->findBigger(*onTable);
			RuleCardSet zero;
			if (tmp == zero) {
				signal->signalType = SKIP_CARD;
				emit modelCommandSignal(signal);
			}
			else {
				CARDSET origin;
				qint8* arr = tmp.getArr();
				for (int i = 0; i < (*m_Num); i++) {
					qint8 num = m_Card->cards[i].i;
					if (arr[num] > 0) {
						arr[num]--;
						origin.add(m_Card->cards[i]);
					}
				}
				signal->signalType = PLAY_CARD;
				signal->cardTransfer = origin.tranToSig();
				emit modelCommandSignal(signal);
			}
		}
	}
	else if (signal->signalType == COM_CHOOSE) //this is for constraint choose
	{
		if (*status == SELF_CHOOSE_TURN) {
			signal->signalType = CHOOSE_LANDLORD;
			emit modelCommandSignal(signal);
		}
	}
	else if (signal->signalType == TIME_SEC) {
		emit modelNotificationSignal(signal);
	}
}

