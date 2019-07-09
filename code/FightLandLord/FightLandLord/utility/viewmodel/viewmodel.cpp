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

	connect(this, SIGNAL(viewModelToModelSignal(std::shared_ptr<Signal>)), &(*model), SLOT(viewModelToModelSlot(std::shared_ptr<Signal>)));
	connect(&(*model), SIGNAL(modelToViewModelSignal(std::shared_ptr<Signal>)), this, SLOT(modelToViewModelSlot(std::shared_ptr<Signal>)));
}

void modelView::setUpper(const std::shared_ptr<Player>& model)
{
	upperHouse = model;
	connect(this, SIGNAL(viewModelToModelSignal(std::shared_ptr<Signal>)), &(*model), SLOT(viewModelToModelSlot(std::shared_ptr<Signal>)));
	connect(&(*model), SIGNAL(modelToViewModelSignal(std::shared_ptr<Signal>)), this, SLOT(modelToViewModelSlot(std::shared_ptr<Signal>)));
}

void modelView::setLower(const std::shared_ptr<Player>& model)
{
	lowerHouse = model;
	connect(this, SIGNAL(viewModelToModelSignal(std::shared_ptr<Signal>)), &(*model), SLOT(viewModelToModelSlot(std::shared_ptr<Signal>)));
	connect(&(*model), SIGNAL(modelToViewModelSignal(std::shared_ptr<Signal>)), this, SLOT(modelToViewModelSlot(std::shared_ptr<Signal>)));
}

void modelView::setTable(const std::shared_ptr<Table>& model)
{
	m_table = model;
	connect(this, SIGNAL(viewModelToModelSignal(std::shared_ptr<Signal>)), &(*model), SLOT(viewModelToModelSlot(std::shared_ptr<Signal>)));
	connect(&(*model), SIGNAL(modelToViewModelSignal(std::shared_ptr<Signal>)), this, SLOT(modelToViewModelSlot(std::shared_ptr<Signal>)));
}

void modelView::windowToViewModelSlot(std::shared_ptr<Signal> signal){
	qDebug() << "Window to Veiw Model" << endl;
	emit viewModelToModelSignal(signal);
}

void modelView::modelToViewModelSlot(std::shared_ptr<Signal> signal)
{
	qDebug() << "Model to Veiw Model" << endl;
	*selected = *self->getSelected();
	*selfOnHand = *self->getOnHand();
	*upperOnHand = *upperHouse->getOnHand();
	*lowerOnHand = *lowerHouse->getOnHand();
	*onTable = *m_table->getOnTable();
	*landLord = *m_table->getLandLord();
	emit viewModelToWindowSignal(signal);
}