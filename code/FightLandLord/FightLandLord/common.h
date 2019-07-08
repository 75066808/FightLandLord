#pragma once
#include <queue>
#include <iostream>
#include <QtWidgets/QMainWindow>
#include <qdebug.h>

struct CARD {
	qint8 i;
	CARD(qint8 in = 3) { 
		if(in >= (qint8)3 && in <= (qint8)17)
			i = in; 
		else {
			qDebug("out of range");
			i = 0;
		}
	}
	CARD(const CARD& in) {
		i = in.i;
	}
	friend bool operator<(const CARD& l,const CARD& r);
	friend bool operator>(const CARD& l, const CARD& r);
	friend bool operator!=(const CARD& l, const CARD& r);
	friend bool operator==(const CARD& l, const CARD& r);
	CARD& operator=(const CARD& r);
};


class CARDSET{
public:
	CARDSET();
	CARDSET(QByteArray dataIn);
	CARDSET(qint8[], int size);
	CARDSET(CARD[], int size);
	~CARDSET();
	QByteArray tranToSig();
	void setToAll();   //set to default 54 cards
	bool add(CARD in);
	bool remove(CARD out);
	friend void distribute(CARDSET& origin, CARDSET& one, CARDSET& two, CARDSET& three, CARDSET& landlord);
	//for test
	void print() {
		for (int i = 0; i < c_num; i++) {
			int temp = cards.top().i;
			std::cout<<temp<<std::endl;
			cards.pop();
		}
	}
private:
	std::priority_queue<CARD> cards;
	int c_num;
};

struct SIGNAL {
	qint8 signalNum;
	qint8 player;
	CARDSET cardTransfer;
};