#pragma once
#include "model.h"

class Player : public QObject {
	Q_OBJECT
public:
	Player();
	~Player();
	const qint8* const getSelected() {
		return selected->getArr();
	}
	const qint8* const getOnHand() {
		return onHand->getArr();
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
	const qint8* const getOnTable() {
		return onTable->getArr();
	}
	const qint8* const getLandLord() {
		return landLord->getArr();
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