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