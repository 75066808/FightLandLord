#include "model.h"


Player::Player() :selected(std::make_shared<RuleCardSet>()),
onHand(std::make_shared<RuleCardSet>()),
status(std::make_shared<int>(0)),
m_Num(std::make_shared<int>(0)),
m_Card(std::make_shared<CARD20>()),
m_Selected(std::make_shared<BOOL20>())
{
}

Player::~Player()
{
}

void Player::modelCommandSlot(std::shared_ptr<Signal> signal) {
	qDebug() << "View Model to Model" << endl;
	if (*status == -2 && signal->signalType == CONNECT) {
		emit modelCommandSignal(signal);
	}
	if (*status == -2 && signal->signalType == READY) {
		*status = 2;
		emit modelCommandSignal(signal);
		//emit modelToViewModelSignal(signal);
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
	if (*status == -2 && (signal->signalType == CONNECT_SUCCESS||signal->signalType == CONNECT_FAILED)) {
		emit modelCommandSignal(signal);
	}
	else if (*status == 2) {
		if (signal->signalType == DEAL_CARD) {
			*status = 4;
			QByteArray whole = signal->cardTransfer;
			QByteArray here;
			here.resize(34);
			int start = 40;  //modify here
			for (int i = 0; i < 34; i++) {
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
			emit modelNotificationSignal(signal);
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

Table::Table() :onTable(std::make_shared<RuleCardSet>()),
landLord(std::make_shared<RuleCardSet>()),
status(std::make_shared<bool>(0)),
t_Num(std::make_shared<int>(0)),
t_Card(std::make_shared<CARD20>()),
l_Num(std::make_shared<int>(0)),
l_Card(std::make_shared<CARD20>())
{
}

Table::~Table()
{
}

void Table::modelCommandSlot(std::shared_ptr<Signal> signal) {
	qDebug() << "View Model to Model" << endl;
	if (0) {
		emit modelCommandSignal(signal);
		//emit modelToViewModelSignal(signal);
	}

}

void Table::modelNotificationSlot(std::shared_ptr<Signal> signal) {
	qDebug() << "Socket to Model" << endl;
	if (0) {
		if (*status == -2) {
			if (signal->signalType == CONNECT_SUCCESS) {
				*status = 1;
				QByteArray whole = signal->cardTransfer;
				QByteArray here;
				here.resize(6);
				int start = 0;  //modify here
				for (int i = 0; i < 6; i++) {
					here[i] = whole[start + i];
				}
				(*landLord) = (*landLord) + RuleCardSet(here);
				CARDSET origin;
				for (int i = 0; i < (*l_Num); i++) {
					origin.add(l_Card->cards[i]);
				}
				int index = 0;
				CARDSET tmp = here + origin;
				while (!tmp.setIsEmpty()) {
					l_Card->cards[index] = tmp.setPop();
					index++;
				}
				(*l_Num) = index;
				emit modelNotificationSignal(signal);
			}
		}
	}
}