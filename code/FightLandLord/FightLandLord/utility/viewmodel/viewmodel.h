#pragma once
#include "../model/model.h"

class modelView : public QObject {
	Q_OBJECT

public:
	modelView();
	void setSelf(const std::shared_ptr<Player>& model);
	void setUpper(const std::shared_ptr<Player>& model);
	void setLower(const std::shared_ptr<Player>& model);
	void setTable(const std::shared_ptr<Table>& model);

	std::shared_ptr<RuleCardSet> getSelected() {
		return selected;
	}
	std::shared_ptr<RuleCardSet> getSelfOnHand() {
		return selfOnHand;
	}
	std::shared_ptr<RuleCardSet> getUpperOnHand() {
		return upperOnHand;
	}
	std::shared_ptr<RuleCardSet> getLowerOnHand() {
		return lowerOnHand;
	}
	std::shared_ptr<RuleCardSet> getOnTable() {
		return onTable;
	}
	std::shared_ptr<RuleCardSet> getLandLord() {
		return landLord;
	}

signals:
	void viewModelToModelSignal(std::shared_ptr<Signal> signal);
	void viewModelToWindowSignal(std::shared_ptr<Signal> signal);

public slots:
	void windowToViewModelSlot(std::shared_ptr<Signal> signal);
	void modelToViewModelSlot(std::shared_ptr<Signal> signal);

private:
	std::shared_ptr<Player> self;
	std::shared_ptr<Player> upperHouse;
	std::shared_ptr<Player> lowerHouse;
	std::shared_ptr<Table> m_table;

	std::shared_ptr<RuleCardSet> selected;
	std::shared_ptr<RuleCardSet> selfOnHand;
	std::shared_ptr<RuleCardSet> upperOnHand;
	std::shared_ptr<RuleCardSet> lowerOnHand;
	std::shared_ptr<RuleCardSet> onTable;
	std::shared_ptr<RuleCardSet> landLord;
};