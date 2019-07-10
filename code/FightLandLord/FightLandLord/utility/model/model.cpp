#include "model.h"


Player::Player() :selected(std::make_shared<RuleCardSet>()),
onHand(std::make_shared<RuleCardSet>()),
status(std::make_shared<int>(0))
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
			RuleCardSet zero;
			RuleCardSet tmp = (*onHand) = zero + RuleCardSet(signal->cardTransfer);
			const qint8* temp = onHand->getArr();
			emit modelNotificationSignal(signal);
		}
	}
}

Table::Table() :onTable(std::make_shared<RuleCardSet>()),
landLord(std::make_shared<RuleCardSet>()),
status(std::make_shared<bool>(0))
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