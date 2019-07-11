#include "common.h"
#include <random>

CARDSET::CARDSET() :c_num(0)
{
}

CARDSET::CARDSET(QByteArray dataIn)
{
	c_num = dataIn.size() / 2;
	for (int i = 0; i < c_num; i++) {
		cards.push(CARD(dataIn[2 * i], dataIn[2 * i + 1]));
	}
}

CARDSET::CARDSET(qint8 arr[], int size)
{
	c_num = size / 2;
	for (int i = 0; i < c_num; i += 2) {
		cards.push(CARD(arr[i], arr[i + 1]));
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
	sig.resize(c_num * 2);
	for (int i = 0; i < c_num; i++) {
		sig[2 * i] = cards.top().i;
		sig[2 * i + 1] = cards.top().color;
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
		if (i >= 3 && i <= 15) time = 3;
		else time = 0;
		for (int j = 0; j <= time; j++) {
			cards.push(CARD((qint8)i,(qint8)j));
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
		if (out == cards.top()) {
			cards.pop();
			c_num--;
			sig = 1;
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
	return l.i != r.i || l.color != r.color;
}

bool operator==(const CARD& l, const CARD& r)
{
	return l.i == r.i && l.color == r.color;
}

const CARDSET operator+(const CARDSET& l, const CARDSET& r)
{
	CARDSET ltmp = l;
	CARDSET rtmp = r;
	while (!rtmp.setIsEmpty()) ltmp.add(rtmp.setPop());
	return ltmp;
}

const CARDSET operator-(const CARDSET& l, const CARDSET& r)
{
	CARDSET ltmp = l;
	CARDSET rtmp = r;
	while (!rtmp.setIsEmpty()) {
		ltmp.remove(rtmp.setPop());
	}
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
	color = r.color;
	return *this;
}

