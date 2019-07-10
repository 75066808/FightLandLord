#include "viewmodel.h"

modelView::modelView():selected(std::make_shared<RuleCardSet>()),
selfOnHand(std::make_shared<RuleCardSet>()),
upperOnHand(std::make_shared<RuleCardSet>()),
lowerOnHand(std::make_shared<RuleCardSet>()),
onTable(std::make_shared<RuleCardSet>()),
landLord(std::make_shared<RuleCardSet>())
{

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
	*selected = *self->getSelected();
	*selfOnHand = *self->getOnHand();
	*upperOnHand = *upperHouse->getOnHand();
	*lowerOnHand = *lowerHouse->getOnHand();
	*onTable = *m_table->getOnTable();
	*landLord = *m_table->getLandLord();
	emit viewModelNotificationSignal(signal);
}