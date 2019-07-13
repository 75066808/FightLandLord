#pragma once
#include <queue>
#include <iostream>
#include <QtWidgets/QMainWindow>
#include <qdebug.h>
#include <QMetaType>

// player type
#define UPPERHOUSE         0x00
#define SELF               0x01
#define LOWERHOUSE         0x02

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
#define SELECT             0x15


#define SELF_DIS_CONNECT      0x00   
#define UPPER_DIS_CONNECT     0x01 
#define LOWER_DIS_CONNECT     0x02 
#define SELF_CONNECT          0x03 
#define UPPER_CONNECT         0x04 
#define LOWER_CONNECT         0x05 
#define SELF_READY            0x06
#define UPPER_READY           0x07 
#define LOWER_READY           0x08 
#define SELF_CHOOSE_TURN      0x09
#define UPPER_CHOOSE_TURN     0x0a
#define LOWER_CHOOSE_TURN     0x0b
#define SELF_WIN              0x0c
#define UPPER_WIN             0x0d
#define LOWER_WIN             0x0e 
#define SELF_TURN             0x0f
#define UPPER_TURN            0x10
#define LOWER_TURN            0x11
#define SELF_SKIP             0x12
#define UPPER_SKIP            0x13
#define LOWER_SKIP            0x14
#define SELF_PLAY             0x15
#define UPPER_PLAY            0x16
#define LOWER_PLAY            0x17
#define SELF_NOT_CHOOSE_TURN  0x18
#define UPPER_NOT_CHOOSE_TURN 0x19
#define LOWER_NOT_CHOOSE_TURN 0x1a
#define SELF_NOSKIP_TURN      0x1b
#define UPPER_NOSKIP_TURN     0x1c
#define LOWER_NOSKIP_TURN     0x1d
#define SELF_CHOOSE_LAND      0x1e
#define UPPER_CHOOSE_LAND     0x1f
#define LOWER_CHOOSE_LAND     0x20
#define SELF_SKIP_LAND        0x21
#define UPPER_SKIP_LAND       0x22
#define LOWER_SKIP_LAND       0x23
#define SELF_LOSE             0x24
#define UPPER_LOSE            0x25
#define LOWER_LOSE            0x26 


#define TABLE_NO_READY        0x00
#define TABLE_PLAY            0x01
#define TABLE_SELF            0x02
#define TABLE_UPPER           0x03
#define TABLE_LOWER           0x04


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
	qint8 playerType[3];    
	QByteArray cardTransfer;
};


class CARD20 {
public:
	CARD20() {
		for (int i = 0; i < 20; i++) cards[i] = 0;
	}
	void clear(){
		for (int i = 0; i < 20; i++) cards[i] = 0;
	}
	CARD cards[20];
};

class BOOL20 {
public:
	BOOL20() {
		for (int i = 0; i < 20; i++) bools[i] = 0;
	}
	void clear(){
		for (int i = 0; i < 20; i++) bools[i] = 0;
	}
	CARD bools[20];
};

Q_DECLARE_METATYPE(Signal)

