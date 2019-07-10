#include "common.h"
#include <random>

CARDSET::CARDSET() :c_num(0)
{
}

CARDSET::CARDSET(QByteArray dataIn)
{
	c_num = dataIn.size();
	for (int i = 0; i < c_num; i++) {
		cards.push(CARD(dataIn[i]));
	}
}

CARDSET::CARDSET(qint8 arr[], int size)
{
	c_num = size;
	for (int i = 0; i < c_num; i++) {
		cards.push(CARD(arr[i]));
	}
}

CARDSET::CARDSET(CARD arr[], int size)
{
	c_num = size;
	for (int i = 0; i < c_num; i++) {
		cards.push(arr[i]);
	}
}

CARDSET::~CARDSET()
{
}

QByteArray CARDSET::tranToSig()
{
	QByteArray sig;

	sig.resize(c_num);
	for (int i = 0; i < c_num; i++) {
		sig[i] = cards.top().i;
		cards.pop();
	}

	c_num = 0;
	return sig;
}

void CARDSET::setToAll()
{
	c_num = 54;
	while (!cards.empty()) cards.pop();
	for (int i = 3; i <= 17; i++) {
		int time;
		if (i >= 3 && i <= 15) time = 4;
		else time = 1;
		for (int j = 1; j <= time; j++) {
			cards.push(CARD((qint8)i));
		}
	}

}

bool CARDSET::add(CARD in)
{
	c_num++;
	cards.push(in);
	return true;
}

bool CARDSET::remove(CARD out)
{
	std::priority_queue<CARD> tmp;
	CARD temp;
	bool sig = 0;
	for (int i = 0; i < c_num; i++) {
		if (!sig && out != cards.top()) {
			temp = cards.top();
			cards.pop();
			tmp.push(temp);
		}
		else if (!sig && out == cards.top()) {
			sig = 1;
			cards.pop();
			c_num--;
		}
		else {
			temp = cards.top();
			cards.pop();
			tmp.push(temp);
		}
	}
	for (int i = 0; i < c_num; i++) {
		temp = tmp.top();
		tmp.pop();
		cards.push(temp);
	}
	return sig;
}

bool operator<(const CARD& l, const CARD& r)
{
	return l.i < r.i;
}

bool operator>(const CARD& l, const CARD& r)
{
	return l.i > r.i;
}

bool operator!=(const CARD& l, const CARD& r)
{
	return l.i != r.i;
}

bool operator==(const CARD& l, const CARD& r)
{
	return l.i == r.i;
}

void distribute(CARDSET& origin, CARDSET& one, CARDSET& two, CARDSET& three, CARDSET& landlord)
{
	static std::default_random_engine randEng(clock());

	while (!one.setIsEmpty())
		one.setPop();
	while (!two.setIsEmpty())
		two.setPop();
	while (!three.setIsEmpty())
		three.setPop();
	while (!landlord.setIsEmpty())
		landlord.setPop();

	if (origin.c_num != 54 || one.c_num != 0 || two.c_num != 0 || three.c_num != 0 || landlord.c_num != 0) {
		qDebug("illegal distribute");
	}
	else {
		bool vSet[4] = { 1,1,1,1 };
		int vnum = 4;
		int choose;
		CARD temp;
		CARDSET* dest;
		for (int i = 54; i >= 1; i--) {
			int rnd = randEng() % vnum + 1;
			for (int j = 0; j <= 3; j++) {
				if (vSet[j] == 1) {
					rnd--;
					if (rnd == 0) {
						choose = j;
						break;
					}
				}
			}
			if (vSet[choose] == 1) {
				temp = origin.cards.top();
				origin.cards.pop();
				origin.c_num--;
				if (choose == 0) dest = &one;
				else if (choose == 1) dest = &two;
				else if (choose == 2) dest = &three;
				else if (choose == 3) dest = &landlord;
				dest->c_num++;
				dest->cards.push(temp);
				if (dest->c_num == 17 && choose <= 2) {
					vSet[choose] = 0;
					vnum--;
				}
				else if (dest->c_num == 3 && choose == 3) {
					vSet[choose] = 0;
					vnum--;
				}
			}
		}
	}
	return;
}

CARD& CARD::operator=(const CARD& r)
{
	if (this == &r) return *this;
	i = r.i;
	return *this;
}
