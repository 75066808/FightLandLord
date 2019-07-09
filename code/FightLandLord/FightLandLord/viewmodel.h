#pragma once
#include "model.h"

class Player : public QObject {
	Q_OBJECT
public:
	Player();
	~Player();
	std::shared_ptr<RuleCardSet> getSelected() {
		return selected;
	}
	std::shared_ptr<RuleCardSet> getOnHand() {
		return selected;
	}
signals:
	void viewModelToAppSignal(Singal& signal);
public slots:
	void appToViewModelSlot(Singal& signal);
private:
	std::shared_ptr<RuleCardSet> selected;
	std::shared_ptr<RuleCardSet> onHand;
	std::shared_ptr<bool> status;
};

class Table : public QObject {
	Q_OBJECT
public:
	Table();
	~Table();
	std::shared_ptr<RuleCardSet> getOnTable() {
		return onTable;
	}
	std::shared_ptr<RuleCardSet> getLandLord() {
		return landLord;
	}
signals:
	void viewModelToAppSignal(Singal& signal);
public slots:
	void appToViewModelSlot(Singal& signal);
private:
	std::shared_ptr<RuleCardSet> onTable;
	std::shared_ptr<RuleCardSet> landLord;
	std::shared_ptr<bool> status;
};