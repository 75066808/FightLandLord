#include "viewmodel.h"

modelView::modelView():
	onHandNum(std::make_shared<int>(0)),
	onHandCard(std::make_shared<CARD20>()),
	onHandSelected(std::make_shared<BOOL20>()),
	lowerNum(std::make_shared<int>(0)),
	lowerCard(std::make_shared<CARD20>()),
	upperNum(std::make_shared<int>(0)),
	upperCard(std::make_shared<CARD20>()),
	onTableNum(std::make_shared<int>(0)),
	onTableCard(std::make_shared<CARD20>()),
	landLordNum(std::make_shared<int>(0)),
	landLordCard(std::make_shared<CARD20>())
{
	
}

std::shared_ptr<int> modelView::getOnHandNum() {
	return onHandNum;
}
std::shared_ptr<CARD20> modelView::getOnHandCard() {
	return onHandCard;
}
std::shared_ptr<BOOL20> modelView::getOnHandSelected() {
	return onHandSelected;
}
std::shared_ptr<int> modelView::getLowerNum() {
	return lowerNum;
}
std::shared_ptr<CARD20> modelView::getLowerCard() {
	return lowerCard;
}
std::shared_ptr<int> modelView::getUpperNum() {
	return upperNum;
}
std::shared_ptr<CARD20> modelView::getUpperCard() {
	return upperCard;
}
std::shared_ptr<int> modelView::getOnTableNum() {
	return onTableNum;
}
std::shared_ptr<CARD20> modelView::getOnTableCard() {
	return onTableCard;
}
std::shared_ptr<int> modelView::getLandLordNum() {
	return landLordNum;
}
std::shared_ptr<CARD20> modelView::getLandLordCard() {
	return landLordCard;
}

void modelView::setSelf(const std::shared_ptr<Player>& model)
{
	self = model;

	connect(this, SIGNAL(viewModelCommandSignal(std::shared_ptr<Signal>)), &(*model), SLOT(modelCommandSlot(std::shared_ptr<Signal>)));
	connect(&(*model), SIGNAL(modelNotificationSignal(std::shared_ptr<Signal>)), this, SLOT(viewModelNotificationSlot(std::shared_ptr<Signal>)));
}

void modelView::setUpper(const std::shared_ptr<Player>& model)
{
	upperHouse = model;
	connect(this, SIGNAL(viewModelCommandSignal(std::shared_ptr<Signal>)), &(*model), SLOT(modelCommandSlot(std::shared_ptr<Signal>)));
	connect(&(*model), SIGNAL(modelNotificationSignal(std::shared_ptr<Signal>)), this, SLOT(viewModelNotificationSlot(std::shared_ptr<Signal>)));
}

void modelView::setLower(const std::shared_ptr<Player>& model)
{
	lowerHouse = model;
	connect(this, SIGNAL(viewModelCommandSignal(std::shared_ptr<Signal>)), &(*model), SLOT(modelCommandSlot(std::shared_ptr<Signal>)));
	connect(&(*model), SIGNAL(modelNotificationSignal(std::shared_ptr<Signal>)), this, SLOT(viewModelNotificationSlot(std::shared_ptr<Signal>)));
}

void modelView::setTable(const std::shared_ptr<Table>& model)
{
	m_table = model;
	connect(this, SIGNAL(viewModelCommandSignal(std::shared_ptr<Signal>)), &(*model), SLOT(modelCommandSlot(std::shared_ptr<Signal>)));
	connect(&(*model), SIGNAL(modelNotificationSignal(std::shared_ptr<Signal>)), this, SLOT(viewModelNotificationSlot(std::shared_ptr<Signal>)));
}

void modelView::setSocket(const std::shared_ptr <Socket>& model)
{
	socket = model;

	connect(&*self, SIGNAL(modelCommandSignal(std::shared_ptr<Signal>)),
		&*socket, SLOT(socketCommandSlot(std::shared_ptr<Signal>)));

	connect(&*upperHouse, SIGNAL(modelCommandSignal(std::shared_ptr<Signal>)),
		&*socket, SLOT(socketCommandSlot(std::shared_ptr<Signal>)));

	connect(&*lowerHouse, SIGNAL(modelCommandSignal(std::shared_ptr<Signal>)),
		&*socket, SLOT(socketCommandSlot(std::shared_ptr<Signal>)));

	connect(&*m_table, SIGNAL(modelCommandSignal(std::shared_ptr<Signal>)),
		&*socket, SLOT(socketCommandSlot(std::shared_ptr<Signal>)));

	connect(&*socket, SIGNAL(socketNotificationSignal(std::shared_ptr<Signal>)),
		&*self, SLOT(modelNotificationSlot(std::shared_ptr<Signal>)));

	connect(&*socket, SIGNAL(socketNotificationSignal(std::shared_ptr<Signal>)),
		&*upperHouse, SLOT(modelNotificationSlot(std::shared_ptr<Signal>)));

	connect(&*socket, SIGNAL(socketNotificationSignal(std::shared_ptr<Signal>)),
		&*lowerHouse, SLOT(modelNotificationSlot(std::shared_ptr<Signal>)));

	connect(&*socket, SIGNAL(socketNotificationSignal(std::shared_ptr<Signal>)),
		&*m_table, SLOT(modelNotificationSlot(std::shared_ptr<Signal>)));
}


void modelView::viewModelCommandSlot(std::shared_ptr<Signal> signal){
	qDebug() << "Window to Veiw Model" << endl;
	emit viewModelCommandSignal(signal);
}

void modelView::viewModelNotificationSlot(std::shared_ptr<Signal> signal)
{
	qDebug() << "Model to Veiw Model" << endl;
	int tmp;
	tmp = (*onHandNum) = (*self->get_Num());
	std::shared_ptr<CARD20> ctmp;
	std::shared_ptr<BOOL20> btmp;
	ctmp = self->get_Card();
	btmp = self->get_Selected();
	for (int i = 0; i < tmp; i++) {
		onHandCard->cards[i] = ctmp->cards[i];
	}
	for (int i = 0; i < tmp; i++) {
		onHandSelected->bools[i] = btmp->bools[i];
	}
	tmp = (*upperNum) = (*upperHouse->get_Num());
	ctmp = upperHouse->get_Card();
	for (int i = 0; i < tmp; i++) {
		upperCard->cards[i] = ctmp->cards[i];
	}
	tmp = (*lowerNum) = (*upperHouse->get_Num());
	ctmp = lowerHouse->get_Card();
	for (int i = 0; i < tmp; i++) {
		lowerCard->cards[i] = ctmp->cards[i];
	}
	tmp = (*onTableNum) = (*m_table->getT_Num());
	ctmp = m_table->getT_Card();
	for (int i = 0; i < tmp; i++) {
		onTableCard->cards[i] = ctmp->cards[i];
	}
	tmp = (*landLordNum) = (*m_table->getL_Num());
	ctmp = m_table->getL_Card();
	for (int i = 0; i < tmp; i++) {
		landLordCard->cards[i] = ctmp->cards[i];
	}

	emit viewModelNotificationSignal(signal);
}