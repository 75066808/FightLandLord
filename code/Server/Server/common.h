#pragma once
#include <queue>
#include <iostream>
#include <QtWidgets/QMainWindow>
#include <qdebug.h>
#include <QMetaType>

// player type
#define UPPERHOUSE         0xFF
#define SELF               0x00
#define LOWERHOUSE         0x01

// signal type
#define CONNECT            0x00
#define DISCONNECT         0x01
#define CONNECT_SUCCESS    0x02
#define CONNECT_FAILED     0x03
#define READY              0x04
#define PLAY_TURN          0x05
#define PLAY_TURN_NO_SKIP  0x06
#define CHOOSE_TURN        0x07
#define PLAY_CARD          0x08
#define SKIP_CARD          0x09
#define CHOOSE_LANDLORD    0x0A
#define SKIP_LANDLORD      0x0B
#define DEAL_CARD          0x0C
#define DEAL_LANDLORD      0x0D
#define LOSE_GAME          0x0E
#define WIN_GAME           0x0F
#define PLAYER_QUIT        0x10
#define TIME_OUT		   0x11
#define COM_PLAY           0x12
#define COM_PLAY_NO_SKIP   0x13
#define COM_CHOOSE         0x14

struct CARD {
	qint8 i;      //3->17 is legal;
	qint8 color;  //0,1,2,3 is legal;
	CARD(qint8 in = 3, qint8 incolor = 0) {
		if (in >= (qint8)3 && in <= (qint8)17 || incolor <= (qint8)3 && incolor >= (qint8)0){
			i = in;
			color = incolor;
		}
		else {
			qDebug("out of range");
			i = 0;
			color = 4;
		}
	}
	CARD(const CARD& in) {
		i = in.i;
		color = in.color;
	}
	friend bool operator<(const CARD& l, const CARD& r);
	friend bool operator>(const CARD& l, const CARD& r);
	friend bool operator!=(const CARD& l, const CARD& r);
	friend bool operator==(const CARD& l, const CARD& r);
	CARD& operator=(const CARD& r);
};


class CARDSET {
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
	CARD setPop() {
		c_num--;
		CARD tmp = cards.top();
		cards.pop();
		return tmp;
	}
	bool setIsEmpty() {
		return !c_num;
	}
	friend const CARDSET operator+(const CARDSET& l, const CARDSET& r);
	friend const CARDSET operator-(const CARDSET& l, const CARDSET& r);
	friend void distribute(CARDSET& origin, CARDSET& one, CARDSET& two, CARDSET& three, CARDSET& landlord);
	//for test
	void print() {
		for (int i = 0; i < c_num; i++) {
			int tempi = cards.top().i;
			int tempc = cards.top().color;
			std::cout << tempi << "  " << tempc << std::endl;
			cards.pop();
		}
	}
private:
	std::priority_queue<CARD> cards;
	int c_num;
};

struct Signal {
	qint8 valid;        
	qint8 signalType;
	qint8 playerType;    
	CARDSET cardTransfer;
};


class CARD20 {
public:
	CARD20() {
		for (int i = 0; i < 20; i++) cards[i] = 0;
	}
	CARD cards[20];
};

class BOOL20 {
public:
	BOOL20() {
		for (int i = 0; i < 20; i++) bools[i] = 0;
	}
	CARD bools[20];
};

Q_DECLARE_METATYPE(Signal)

