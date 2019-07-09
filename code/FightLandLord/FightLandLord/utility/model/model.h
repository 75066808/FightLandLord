#pragma once
#include "algorithm/algorithm.h"

class Player : public QObject {
	Q_OBJECT
public:
	Player();
	~Player();
	std::shared_ptr<RuleCardSet> getSelected() {
		return selected;
	}
	std::shared_ptr<RuleCardSet> getOnHand() {
		return onHand;
	}
	void setStatus(int in) {
		*status = in;
	}
signals:
	void modelToSocketSignal(std::shared_ptr<Signal> signal);
	void modelToViewModelSignal(std::shared_ptr<Signal> signal);
public slots:
	void viewModelToModelSlot(std::shared_ptr<Signal> signal);
	void socketToModelSlot(std::shared_ptr<Signal> signal);

private:
	std::shared_ptr<RuleCardSet> selected;
	std::shared_ptr<RuleCardSet> onHand;
	std::shared_ptr<int> status;
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
	void modelToSocketSignal(std::shared_ptr<Signal> signal);
	void modelToViewModelSignal(std::shared_ptr<Signal> signal);
public slots:
	void viewModelToModelSlot(std::shared_ptr<Signal> signal);
	void socketToModelSlot(std::shared_ptr<Signal> signal);

private:
	std::shared_ptr<RuleCardSet> onTable;
	std::shared_ptr<RuleCardSet> landLord;
	std::shared_ptr<bool> status;
};