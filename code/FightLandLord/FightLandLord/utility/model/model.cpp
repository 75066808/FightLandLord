#include "model.h"

qint8 Player::connectNum = 0;
qint8 Player::connectFailNum = 0;
qint8 Player::readyNum = 0;
qint8 Player::dealCardNum = 0;
qint8 Player::dealLandNum = 0;

Player::Player() :selected(std::make_shared<RuleCardSet>()),
onHand(std::make_shared<RuleCardSet>()),
status(std::make_shared<int>(0)),
m_Num(std::make_shared<int>(0)),
s_Num(std::make_shared<int>(0)),
m_Card(std::make_shared<CARD20>()),
m_Selected(std::make_shared<BOOL20>()),
o_Card(std::make_shared<CARD20>())
{
}

Player::~Player()
{
}

void Player::modelCommandSlot(std::shared_ptr<Signal> signal) {
	qDebug() << "View Model to Model" << endl;
	if (*status == SELF_DIS_CONNECT && signal->signalType == CONNECT) {
		emit modelCommandSignal(signal);
	}
	else if (*status == SELF_CONNECT && signal->signalType == READY) {
		emit modelCommandSignal(signal);
	}
	else if(*status == SELF_CONNECT && signal->signalType == DISCONNECT){
		emit modelCommandSignal(signal);
	}
	else if (0)  //this is for selected
	{
		int index = 0;
		m_Selected->bools[index] = 1;
		CARDSET zero;
		zero.add(m_Card->cards[index]);
		(*selected) = (*selected) + zero;
		//for some modify
		emit modelNotificationSignal(signal);
	}
	else if (0)  //this is for cancel selected
	{
		int index = 0;
		m_Selected->bools[index] = 0;
		CARDSET zero;
		zero.add(m_Card->cards[index]);
		(*selected) = (*selected) - zero;
		//for some modify
		emit modelNotificationSignal(signal);
	}
	else if (0)  //this is for try to hand cards
	{
		if (((*onTable) < (*selected)) == 1) {
			//for some modify
			emit modelCommandSignal(signal);
		}
		else {
			//for some modify
			emit modelNotificationSignal(signal);
		}
	}
}

void Player::modelNotificationSlot(std::shared_ptr<Signal> signal) {
	qDebug() << "Socket to Model" << endl;
	if (signal->signalType == CONNECT_SUCCESS) {
		if (*status == 0) {
			if (signal->playerType[SELF] == 1) *status = SELF_CONNECT;
			else *status = SELF_DIS_CONNECT;
		}
		else if(*status == 1) {
			if (signal->playerType[UPPERHOUSE] == 1) *status = UPPER_CONNECT;
			else *status = UPPER_DIS_CONNECT;
		}
	else if (*status == 2) {
		if (signal->playerType[LOWERHOUSE] == 1) *status = LOWER_CONNECT;
		else *status = LOWER_DIS_CONNECT;
	}
	Player::connectNum++;
	if (Player::connectNum == 3) {
		emit modelNotificationSignal(signal);
		Player::connectNum = 0;
	}

	}
	else if (signal->signalType == DISCONNECT) {
		(*status) %= 3;
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
			if (signal->playerType[SELF] == 1) *status = SELF_READY;
		}
		else if(*status % 3 == 1) {
			if (signal->playerType[UPPERHOUSE] == 1) *status = UPPER_READY;
		}
		else if(*status % 3 == 2) {
			if (signal->playerType[LOWERHOUSE] == 1) *status = LOWER_READY;
		}
		readyNum++;
		if (readyNum == 3) {
			emit modelNotificationSignal(signal);
			readyNum = 0;
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
		(*onHand) = (*onHand) + RuleCardSet(here);
		CARDSET origin;
		int index = 0;
		CARDSET tmp = here + origin;
		while (!tmp.setIsEmpty()) {
			m_Card->cards[index] = tmp.setPop();
			index++;
		}
		(*m_Num) = index;

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
	else if (0) //this is for handing cards
	{
		CARDSET zero;
		(*selected) = zero;
		(*onHand) = (*onHand) - RuleCardSet(signal->cardTransfer);
		CARDSET origin;
		for (int i = 0; i < (*m_Num); i++) {
			origin.add(m_Card->cards[i]);
		}
		int index = 0;
		CARDSET tmp = signal->cardTransfer - origin;
		while (!tmp.setIsEmpty()) {
			m_Card->cards[index] = tmp.setPop();
			index++;
		}
		(*m_Num) = index;
		emit modelNotificationSignal(signal);
	}
}

