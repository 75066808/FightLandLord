#pragma once
#include "algorithm/algorithm.h"

class Player : public QObject {
	Q_OBJECT
public:
	Player();
	~Player();
	void setStatus(int in) {
		*status = in;
	}

	std::shared_ptr<int> get_Num() {
		return m_Num;
	}
	std::shared_ptr<CARD20> get_Card() {
		return m_Card;
	}
	std::shared_ptr<BOOL20> get_Selected() {
		return m_Selected;
	}
signals:
	void modelCommandSignal(std::shared_ptr<Signal> signal);
	void modelNotificationSignal(std::shared_ptr<Signal> signal);

public slots:
	void modelCommandSlot(std::shared_ptr<Signal> signal);
	void modelNotificationSlot(std::shared_ptr<Signal> signal);

private:
	std::shared_ptr<RuleCardSet> selected;
	std::shared_ptr<RuleCardSet> onHand;
	std::shared_ptr<int> status;

	std::shared_ptr<int> m_Num;
	std::shared_ptr<CARD20> m_Card;
	std::shared_ptr<BOOL20> m_Selected;
};

class Table : public QObject {
	Q_OBJECT
public:
	Table();
	~Table();

	std::shared_ptr<int> getT_Num() {
		return t_Num;
	}
	std::shared_ptr<CARD20> getT_Card() {
		return t_Card;
	}
	std::shared_ptr<int> getL_Num() {
		return l_Num;
	}
	std::shared_ptr<CARD20> getL_Card() {
		return l_Card;
	}

signals:
	void modelCommandSignal(std::shared_ptr<Signal> signal);
	void modelNotificationSignal(std::shared_ptr<Signal> signal);

public slots:
	void modelCommandSlot(std::shared_ptr<Signal> signal);
	void modelNotificationSlot(std::shared_ptr<Signal> signal);

private:
	std::shared_ptr<RuleCardSet> onTable;
	std::shared_ptr<RuleCardSet> landLord;
	std::shared_ptr<bool> status;

	std::shared_ptr<int> t_Num;
	std::shared_ptr<CARD20> t_Card;
	std::shared_ptr<int> l_Num;
	std::shared_ptr<CARD20> l_Card;
};