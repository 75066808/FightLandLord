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
	if (*status == -2) {
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
	if (*status == -2) {
		qDebug() << "Socket to Model" << endl;
		if (signal->signalType == CONNECT_SUCCESS) {
			*status = 1;
		    (*onHand) = (*onHand) + RuleCardSet(signal->cardTransfer);
			CARDSET origin;
			for (int i = 0; i < (*m_Num); i++) {
				origin.add(m_Card->cards[i]);
			}
			int index = 0;
			CARDSET tmp = signal->cardTransfer + origin;
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
		/*(*onHand) = (*onHand) - (*selected);
		RuleCardSet zero;
		(*selected) = zero;
		int i = 0, j = 0;
		for (; i < (*m_Num); i++){
			if (m_Selected->bools[i] == 1) {
				m_Card->cards[j] = m_Card->cards[i];
				m_Selected->bools[j] = m_Selected->bools[i];
				j++;
			}
		}
		(*m_Num) = j;*/
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
		emit modelNotificationSignal(signal);
	}
}