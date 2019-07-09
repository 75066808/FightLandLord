#include "viewmodel.h"


Player::Player():selected(std::make_shared<RuleCardSet>()),
				 onHand(std::make_shared<RuleCardSet>()),
				 status(std::make_shared<bool>(0))
{
}

Player::~Player()
{
}

void Player::appToViewModelSlot(Singal& signal) {
	if (signal.signalCotent == CONNECT_SUCCESS) {
		*status = 1;
		signal.signalType = MODIFY_FEEDBACK;
		RuleCardSet zero;
		(*onHand) = zero + RuleCardSet(signal.cardTransfer);
		emit viewModelToAppSignal( signal);
	}

}

Table::Table():onTable(std::make_shared<RuleCardSet>()),
			   landLord(std::make_shared<RuleCardSet>()),
			   status(std::make_shared<bool>(0))
{
}

Table::~Table()
{
}

void Table::appToViewModelSlot(Singal& signal) {
	if (signal.signalCotent == CONNECT_SUCCESS) {
		*status = 1;
		signal.signalType = MODIFY_FEEDBACK;
		emit viewModelToAppSignal(signal);
	}

}