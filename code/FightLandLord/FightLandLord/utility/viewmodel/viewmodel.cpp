#include "viewmodel.h"

modelView::modelView() :
	onHandNum(std::make_shared<int>(0)),
	onHandCard(std::make_shared<CARD20>()),
	onHandSelected(std::make_shared<BOOL20>()),
	selfHandOut(std::make_shared<CARD20>()),
	selfHandOutNum(std::make_shared<int>(0)),
	selfStatus(std::make_shared<int>(0)),

	lowerNum(std::make_shared<int>(0)),
	lowerHandOutNum(std::make_shared<int>(0)),
	lowerCard(std::make_shared<CARD20>()),
	lowerHandOut(std::make_shared<CARD20>()),
	lowerStatus(std::make_shared<int>(0)),

	upperNum(std::make_shared<int>(0)),
	upperHandOutNum(std::make_shared<int>(0)),
	upperCard(std::make_shared<CARD20>()),
	upperHandOut(std::make_shared<CARD20>()),
	upperStatus(std::make_shared<int>(0)),

	landLordNum(std::make_shared<int>(0)),
	landLordCard(std::make_shared<CARD20>()),
	landLord(std::make_shared<int>(-1)),
	
	timeSec(std::make_shared<qint8>(-1))
{
	
}

modelView::~modelView()
{

}

//self------------------------------------------------------------------//

std::shared_ptr<int> modelView::getOnHandNum() {
	return onHandNum;
}
std::shared_ptr<CARD20> modelView::getOnHandCard() {
	return onHandCard;
}
std::shared_ptr<BOOL20> modelView::getOnHandSelected() {
	return onHandSelected;
}
std::shared_ptr<int> modelView::getStatus()
{
	return selfStatus;
}
std::shared_ptr<int> modelView::getSelfHandOutNum(){
	return selfHandOutNum;
}
std::shared_ptr<CARD20> modelView::getSelfHandOut(){
	return selfHandOut;
}

//lower------------------------------------------------------------------//

std::shared_ptr<int> modelView::getLowerNum() {
	return lowerNum;
}
std::shared_ptr<CARD20> modelView::getLowerCard() {
	return lowerCard;
}

std::shared_ptr<int> modelView::getLowerHandOutNum()
{
	return lowerHandOutNum;
}

std::shared_ptr<CARD20> modelView::getLowerHandOut()
{
	return lowerHandOut;
}

std::shared_ptr<int> modelView::getLowerStatus()
{
	return lowerStatus;
}

//upper------------------------------------------------------------------//

std::shared_ptr<int> modelView::getUpperNum() {
	return upperNum;
}
std::shared_ptr<CARD20> modelView::getUpperCard() {
	return upperCard;
}

std::shared_ptr<int> modelView::getUpperHandOutNum()
{
	return upperHandOutNum;
}

std::shared_ptr<CARD20> modelView::getUpperHandOut()
{
	return upperHandOut;
}

std::shared_ptr<int> modelView::getUpperStatus()
{
	return upperStatus;
}


std::shared_ptr<int> modelView::getLandLordNum()
{
	return landLordNum;
}
std::shared_ptr<CARD20> modelView::getLandLordCard()
{
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

void modelView::setSocket(const std::shared_ptr <Socket>& model)
{
	socket = model;

	connect(&*self, SIGNAL(modelCommandSignal(std::shared_ptr<Signal>)),
		&*socket, SLOT(socketCommandSlot(std::shared_ptr<Signal>)));

	connect(&*upperHouse, SIGNAL(modelCommandSignal(std::shared_ptr<Signal>)),
		&*socket, SLOT(socketCommandSlot(std::shared_ptr<Signal>)));

	connect(&*lowerHouse, SIGNAL(modelCommandSignal(std::shared_ptr<Signal>)),
		&*socket, SLOT(socketCommandSlot(std::shared_ptr<Signal>)));

	connect(&*socket, SIGNAL(socketNotificationSignal(std::shared_ptr<Signal>)),
		&*self, SLOT(modelNotificationSlot(std::shared_ptr<Signal>)));

	connect(&*socket, SIGNAL(socketNotificationSignal(std::shared_ptr<Signal>)),
		&*upperHouse, SLOT(modelNotificationSlot(std::shared_ptr<Signal>)));

	connect(&*socket, SIGNAL(socketNotificationSignal(std::shared_ptr<Signal>)),
		&*lowerHouse, SLOT(modelNotificationSlot(std::shared_ptr<Signal>)));
}


void modelView::viewModelCommandSlot(std::shared_ptr<Signal> signal){
	//qDebug() << "Window to Veiw Model" << endl;
	emit viewModelCommandSignal(signal);
}

void modelView::viewModelNotificationSlot(std::shared_ptr<Signal> signal)
{
	//qDebug() << "Model to Veiw Model" << endl;
	int tmp;
		
	std::shared_ptr<CARD20> ctmp;
	std::shared_ptr<BOOL20> btmp;

//self------------------------------------------------------//

	tmp = (*onHandNum) = (*self->get_Num());
	(*selfStatus) = (*self->get_Status());
	ctmp = self->get_Card();
	btmp = self->get_Selected();
	for (int i = 0; i < tmp; i++) {
		onHandCard->cards[i] = ctmp->cards[i];
	}
	for (int i = 0; i < tmp; i++) {
		onHandSelected->bools[i] = btmp->bools[i];
	}
	tmp = (*selfHandOutNum) = (*self->gets_Num());
	ctmp = self->geto_Card();
	for (int i = 0; i < tmp; i++) {
		selfHandOut->cards[i] = ctmp->cards[i];
	}

//upper------------------------------------------------------//

	tmp = (*upperNum) = (*upperHouse->get_Num());
	ctmp = upperHouse->get_Card();
	for (int i = 0; i < tmp; i++) {
		upperCard->cards[i] = ctmp->cards[i];
	}
	tmp = (*upperHandOutNum) = (*upperHouse->gets_Num());
	ctmp = upperHouse->geto_Card();
	for (int i = 0; i < tmp; i++) {
		upperHandOut->cards[i] = ctmp->cards[i];
	}
	(*upperStatus) = (*upperHouse->get_Status());

//lower------------------------------------------------------//

	tmp = (*lowerNum) = (*lowerHouse->get_Num());
	ctmp = lowerHouse->get_Card();
	for (int i = 0; i < tmp; i++) {
		lowerCard->cards[i] = ctmp->cards[i];
	}
	tmp = (*lowerHandOutNum) = (*lowerHouse->gets_Num());
	ctmp = lowerHouse->geto_Card();
	for (int i = 0; i < tmp; i++) {
		lowerHandOut->cards[i] = ctmp->cards[i];
	}
	(*lowerStatus) = (*lowerHouse->get_Status());

	if (signal->signalType == DEAL_CARD) {
		(*landLordNum) = 3;
		QByteArray whole = signal->cardTransfer;
		QByteArray here;
		here.resize(6);
		for (int i = 0; i < 6; i++) {
			here[i] = whole[i];
		}
		CARDSET tmp = here;
		int index = 0;
		while (!tmp.setIsEmpty()) {
			landLordCard->cards[index] = tmp.setPop();
			index++;
		}
	}
	else if (signal->signalType == DEAL_LANDLORD) {
		if (signal->playerType[SELF] == 1)* landLord = SELF;
		else if (signal->playerType[UPPERHOUSE] == 1)* landLord = UPPERHOUSE;
		else if (signal->playerType[LOWERHOUSE] == 1)* landLord = LOWERHOUSE;
	}
	else if (signal->signalType == CONT && (signal->playerType[SELF] == 1 || signal->playerType[SELF] == 2))* landLord = -1;
	else if (signal->signalType == TIME_SEC)* timeSec = signal->cardTransfer[0];
	else if (signal->signalType == DISCONNECT) * timeSec = -1;

	emit viewModelNotificationSignal(signal);
}