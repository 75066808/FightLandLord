#include "../utility/model/model.h"

class MyQueue {
public:
	MyQueue() :lbound(0),ubound(0),cont(0) {
	}
	void push(qint8 in) {
		if (lists.empty()) {
			lbound = in;
			ubound = in;
			cont = 1;
			lists.push(in);
		}
		else {
			if (in == lbound - 1) {
				lbound = lbound - 1;
				lists.push(in);
			}
			else if (in == ubound + 1) {
				ubound = ubound + 1;
				lists.push(in);
			}
			else {
				cont = 0;
				lists.push(in);
			}
		}
	}
	const qint8& top() {
		return lists.top();
	}
	void pop() {
		lists.pop();
	}
	bool getCont() {
		return cont;
	}
	qint8 getUpper() {
		return ubound;
	}
private:
	std::priority_queue<qint8> lists;
	qint8 lbound;
	qint8 ubound;
	bool cont;
};
void RuleCardSet::setType()
{
	int sum = 0;
	qint8 numSum[5] = { 0 };
	MyQueue numList[5];

	for (int i = 3; i <= 17; i++) {
		numSum[cardLog[i]]++;
		sum += cardLog[i];
		numList[cardLog[i]].push(i);
	}
	switch (sum)
	{
	case 0:
		type = NONE;
		break;
	case 1:
		type = SINGLE;
		compareSignal = numList[1].top();
		break;
	case 2:
		if (cardLog[16] == 1 && cardLog[17] == 1) {
			type = ROCKET;
			compareSignal = 400;
		}
		else if (numSum[2] == 1) {
			type = PAIR;
			compareSignal = numList[2].top();
		}
		else type = NONE;
		break;
	case 3:
		if (numSum[3] == 1) {
			type = TRIPLE;
			compareSignal = numList[3].top();
		}
		else type = NONE;
		break;
	case 4:
		if (numSum[3] == 1 && numSum[1] == 1) {
			type = TRIPLEANDONE;
			compareSignal = numList[3].top();
		}
		else if (numSum[4] == 1) {
			type = BOMB;
			compareSignal = numList[4].top()*20;
		}
		else type = NONE;
		break;
	case 5:   //Á¬ÐøÐÔ¼ì²â
		if (numSum[3] == 1 && numSum[2] == 1) {
			type = TRIPLEANDTWO;
			compareSignal = numList[3].top();
		}
		else if (numSum[1] == 5 && numList[1].getCont() && numList[1].getUpper() <= 14){
			type = STRAIGHT;
			compareSignal = numList[1].top();
			subType = 5;
		}
		else type = NONE;
		break;
	case 6:
		if (numSum[1] == 6 && numList[1].getCont() && numList[1].getUpper() <= 14) {
			type = STRAIGHT;
			compareSignal = numList[1].top();
			subType = 6;
		}
		else if (numSum[2] == 3 && numList[2].getCont() && numList[2].getUpper() <= 14) {
			type = CONTPAIR;
			compareSignal = numList[2].top();
			subType = 3;
		}
		else if (numSum[3] == 2 && numList[3].getCont() && numList[3].getUpper() <= 14) {
			type = CONTTRIPLE;
			compareSignal = numList[3].top();
			subType = 2;
		}
		else if (numSum[4] == 1) {
			type = QUADRAANDTWO;
			compareSignal = numList[4].top();
		}
		else type = NONE;
		break;
	case 7:
		if (numSum[1] == 7 && numList[1].getCont() && numList[1].getUpper() <= 14) {
			type = STRAIGHT;
			compareSignal = numList[1].top();
			subType = 7;
		}
		else type = NONE;
		break;
	case 8:
		if (numSum[1] == 8 && numList[1].getCont() && numList[1].getUpper() <= 14) {
			type = STRAIGHT;
			compareSignal = numList[1].top();
			subType = 8;
		}
		else if (numSum[2] == 4 && numList[2].getCont() && numList[2].getUpper() <= 14) {
			type = CONTPAIR;
			compareSignal = numList[2].top();
			subType = 4;
		}
		else if (numSum[3] == 2 && numList[3].getCont() && numList[3].getUpper() <= 14){
			type = CONTTRIPLEANDONE;
			compareSignal = numList[3].top();
			subType = 2;
		}
		else if (numSum[4] == 1 && numSum[2] == 2) {
			type = QUADRAANDTWO;
			compareSignal = numList[4].top();
		}
		else type = NONE;
		break;
	case 9:
		if (numSum[1] == 9 && numList[1].getCont() && numList[1].getUpper() <= 14) {
			type = STRAIGHT;
			compareSignal = numList[1].top();
			subType = 9;
		}
		else if (numSum[3] == 3 && numList[3].getCont() && numList[3].getUpper() <= 14) {
			type = CONTTRIPLE;
			compareSignal = numList[3].top();
			subType = 3;
		}
		else type = NONE;
		break;
	case 10:
		if (numSum[1] == 10 && numList[1].getCont() && numList[1].getUpper() <= 14) {
			type = STRAIGHT;
			compareSignal = numList[1].top();
			subType = 10;
		}
		else if (numSum[2] == 5 && numList[2].getCont() && numList[2].getUpper() <= 14) {
			type = CONTPAIR;
			compareSignal = numList[2].top();
			subType = 5;
		}
		else if (numSum[3] == 2 && (numSum[2] == 2 || numSum[4] == 1) && numList[3].getCont() && numList[3].getUpper() <= 14){
			type = CONTTRIPLEANDTWO;
			compareSignal = numList[3].top();
			subType = 2;
		}
		else if (numSum[4] == 1 && numSum[2] == 2) {
			type = QUADRAANDTWO;
			compareSignal = numList[4].top();
		}
		else type = NONE;
		break;
	case 11:
		if (numSum[1] == 11 && numList[1].getCont() && numList[1].getUpper() <= 14) {
			type = STRAIGHT;
			compareSignal = numList[1].top();
			subType = 11;
		}
		else type = NONE;
		break;
	case 12:
		if (numSum[1] == 12 && numList[1].getCont() && numList[1].getUpper() <= 14) {
			type = STRAIGHT;
			compareSignal = numList[1].top();
			subType = 12;
		}
		else if (numSum[2] == 6 && numList[2].getCont() && numList[2].getUpper() <= 14) {
			type = CONTPAIR;
			compareSignal = numList[2].top();
			subType = 6;
		}
		else if (numSum[3] == 4 && numList[3].getCont() && numList[3].getUpper() <= 14) {
			type = CONTTRIPLE;
			compareSignal = numList[3].top();
			subType = 4;
		}
		else if (numSum[3] == 3 && numList[3].getCont() && numList[3].getUpper() <= 14) {
			type = CONTTRIPLEANDONE;
			compareSignal = numList[3].top();
			subType = 3;
		}
		else type = NONE;
		break;
	case 13:
		type = NONE;
		break;
	case 14:
		if (numSum[2] == 7 && numList[2].getCont() && numList[2].getUpper() <= 14) {
			type = CONTPAIR;
			compareSignal = numList[2].top();
			subType = 7;
		}
		else type = NONE;
		break;
	case 15:
		if (numSum[3] == 5 && numList[3].getCont() && numList[3].getUpper() <= 14) {
			type = CONTTRIPLE;
			compareSignal = numList[3].top();
			subType = 5;
		}
		else if (numSum[3] == 3 && (numSum[2] == 3 || numSum[2] == 1 && numSum[4] == 1) && numList[3].getCont() && numList[3].getUpper() <= 14){
			type = CONTTRIPLEANDTWO;
			compareSignal = numList[3].top();
			subType = 3;
		}
		else type = NONE;
		break;
	case 16:
		if (numSum[2] == 8 && numList[2].getCont() && numList[2].getUpper() <= 14) {
			type = CONTPAIR;
			compareSignal = numList[2].top();
			subType = 8;
		}
		else if(numSum[3] == 4 && numList[3].getCont() && numList[3].getUpper() <= 14){
			type = CONTTRIPLEANDONE;
			compareSignal = numList[3].top();
			subType = 4;
		}
		else type = NONE;
		break;
	case 17:
		type = NONE;
		break;
	case 18:
		if (numSum[2] == 9 && numList[2].getCont() && numList[2].getUpper() <= 14) {
			type = CONTPAIR;
			compareSignal = numList[2].top();
			subType = 9;
		}
		else if (numSum[3] == 6 && numList[3].getCont() && numList[3].getUpper() <= 14) {
			type = CONTTRIPLE;
			compareSignal = numList[3].top();
			subType = 6;
		}
		else type = NONE;
		break;
	case 19:
		type = NONE;
		break;
	case 20:
		if (numSum[2] == 10 && numList[2].getCont() && numList[2].getUpper() <= 14) {
			type = CONTPAIR;
			compareSignal = numList[2].top();
			subType = 10;
		}
		else if (numSum[3] == 5 && numList[3].getCont() && numList[3].getUpper() <= 14) {
			type = CONTTRIPLEANDONE;
			compareSignal = numList[3].top();
			subType = 5;
		}
		else if (numSum[3] == 4 && (numSum[2] == 4 || numSum[2] == 2 && numSum[4] == 1 || numSum[4] == 2) && numList[3].getCont() && numList[3].getUpper() <= 14){
			type = CONTTRIPLEANDTWO;
			compareSignal = numList[3].top();
			subType = 4;
		}
		else type = NONE;
		break;
	default:
		break;
	}
}

const RuleCardSet operator+(const RuleCardSet& left, const RuleCardSet& right)
{
	RuleCardSet tmp;
	for (int i = 0; i <= 17; i++) {
		tmp.cardLog[i] = left.cardLog[i] + right.cardLog[i];
	}
	return tmp;
}

const RuleCardSet operator-(const RuleCardSet& left, const RuleCardSet& right)
{
	RuleCardSet tmp;
	for (int i = 0; i <= 17; i++) {
		tmp.cardLog[i] = left.cardLog[i] - right.cardLog[i];
	}
	return tmp;
}

int operator<(RuleCardSet& left,RuleCardSet& right)
{
	left.setType();
	right.setType();
	if (left.type == NONE || right.type == NONE) return -1;
	if (left.type != BOMB && left.type != ROCKET && right.type != BOMB && right.type != ROCKET) {
		if (left.type != right.type) return -1;
		else if (left.type == right.type && left.subType != right.subType) {
			return -1;
		}
		else return left.compareSignal < right.compareSignal;
	}
	else return left.compareSignal < right.compareSignal;
}

int operator>(RuleCardSet& left, RuleCardSet& right)
{
	return 0;
}