#pragma once
#pragma once
#include "../utility/common/common.h"

typedef enum {
	NONE,
	NOCARD,
	SINGLE,
	PAIR,
	TRIPLE,
	TRIPLEANDONE,
	TRIPLEANDTWO,
	STRAIGHT,
	CONTPAIR,
	CONTTRIPLE,
	CONTTRIPLEANDONE,
	CONTTRIPLEANDTWO,
	BOMB,
	ROCKET,
	QUADRAANDONE,
	QUADRAANDTWO
} cardsType;

class RuleCardSet {
public:
	RuleCardSet() :type(NONE), cardLog{ 0 }, compareSignal(3), subType(0){

	}
	RuleCardSet(const RuleCardSet& in) :type(NONE), cardLog{ 0 }, compareSignal(3), subType(0){
		type = in.type;
		for (int i = 0; i <= 17; i++) {
			cardLog[i] = in.cardLog[i];
		}
	}
	~RuleCardSet() {}
	void setType();
	RuleCardSet(CARDSET init) :type(NONE), cardLog{ 0 }, compareSignal(3), subType(0){
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
	const qint8* const getArr() {
		return cardLog;
	}
	cardsType getType() {
		return type;
	}

	RuleCardSet findBigger(RuleCardSet& origin);  //add here
	qint8 getSubType() { return subType; }        //add here
	int getCompSig() { return compareSignal; }    //add here
	void clear() {
		for (int i = 0; i <= 17; i++) {
			cardLog[i] = 0;
		}
		type = NONE;
		subType = 0;
		compareSignal = 3;
	}
	friend const RuleCardSet operator+(const RuleCardSet& left, const RuleCardSet& right);
	friend const RuleCardSet operator-(const RuleCardSet& left, const RuleCardSet& right);
	friend int operator<(RuleCardSet& left, RuleCardSet& right);
	friend int operator>(RuleCardSet& left, RuleCardSet& right);
	RuleCardSet& operator=(const RuleCardSet& in) {
		if (this == &in) return *this;
		type = in.type;
		for (int i = 0; i <= 17; i++) {
			cardLog[i] = in.cardLog[i];
		}
		subType = in.subType;
		compareSignal = in.compareSignal;
		return *this;
	}
private:
	qint8 cardLog[18];
	cardsType type;
	qint8 subType;
	int compareSignal;
};