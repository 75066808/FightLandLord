#pragma once
#include "common.h"

class RuleCardSet : public QObject {

	Q_OBJECT
public:
	RuleCardSet() :type(0), cardLog{ 0 } {
	}
	RuleCardSet(const RuleCardSet& in) :type(0), cardLog{ 0 }{
		type = in.type;
		for (int i = 0; i <= 17; i++) {
			cardLog[i] = in.cardLog[i];
		}
	}
	~RuleCardSet(){}
	RuleCardSet(CARDSET init):type(0), cardLog{ 0 } {
		while (!init.setIsEmpty()) {
			CARD tmp = init.setPop();
			cardLog[tmp.i]++;
		}
	}
	CARDSET toCardSet() {
		CARDSET tmp;
		for (int i = 3; i <= 17; i++) {
			qint8 num = cardLog[i];
			for (int j = 0; j < num; j++) tmp.add(CARD(num));
		}
		return tmp;
	}
	std::shared_ptr<qint8[18]> getCard() {  //for read
		std::shared_ptr<qint8[18]> tmp(std::make_shared<qint8[18]>());
		for (int i = 0; i <= 17; i++) tmp[i] = cardLog[i];
		return tmp;
	}
	friend const RuleCardSet operator+(const RuleCardSet& left, const RuleCardSet& right);
	friend const RuleCardSet operator-(const RuleCardSet& left, const RuleCardSet& right);
	friend int operator<(const RuleCardSet& left, const RuleCardSet& right);
	friend int operator>(const RuleCardSet& left, const RuleCardSet& right);
private:
	qint8 cardLog[18];
	qint8 type;
};