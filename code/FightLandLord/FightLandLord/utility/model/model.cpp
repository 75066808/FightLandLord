#include "model.h"


Player::Player() :selected(std::make_shared<RuleCardSet>()),
onHand(std::make_shared<RuleCardSet>()),
status(std::make_shared<int>(0))
{
}

Player::~Player()
{
}

void Player::viewModelToModelSlot(std::shared_ptr<Signal> signal) {
	qDebug() << "View Model to Model" << endl;
	if (*status == -2) {
		emit modelToSocketSignal(signal);
		//emit modelToViewModelSignal(signal);
	}

}

void Player::socketToModelSlot(std::shared_ptr<Signal> signal) {
	if (*status == -2) {
		qDebug() << "Socket to Model" << endl;
		if (signal->signalType == CONNECT_SUCCESS) {
			*status = 1;
			RuleCardSet zero;
			RuleCardSet tmp = (*onHand) = zero + RuleCardSet(signal->cardTransfer);
			const qint8* temp = onHand->getArr();
			emit modelToViewModelSignal(signal);
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

void Table::viewModelToModelSlot(std::shared_ptr<Signal> signal) {
	if (0) {
		emit modelToSocketSignal(signal);
		emit modelToViewModelSignal(signal);
	}

}

void Table::socketToModelSlot(std::shared_ptr<Signal> signal) {
	if (0) {
		emit modelToViewModelSignal(signal);
	}
}
