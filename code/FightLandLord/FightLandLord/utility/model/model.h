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
	std::shared_ptr<int> gets_Num() {
		return s_Num;
	}
	std::shared_ptr<int> get_Status() {
		return status;
	}
	std::shared_ptr<CARD20> get_Card() {
		return m_Card;
	}
	std::shared_ptr<CARD20> geto_Card() {
		return o_Card;
	}
	std::shared_ptr<BOOL20> get_Selected() {
		return m_Selected;
	}

	std::shared_ptr<RuleCardSet> getOnTable() {
		return onTable;
	}
	void setOnTable(const std::shared_ptr<RuleCardSet>& on) {
		onTable = on;
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
	std::shared_ptr<RuleCardSet> onTable;

	std::shared_ptr<int> m_Num;
	std::shared_ptr<CARD20> m_Card;
	std::shared_ptr<int> s_Num;
	std::shared_ptr<BOOL20> m_Selected;
	std::shared_ptr<CARD20> o_Card;
};
