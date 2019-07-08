#pragma once
#include <vector>
#include <QtWidgets/QMainWindow>

struct CARD {
	qint8 i;
	CARD(qint8 in) { i = in; }
};

class CARDSET{
public:
	CARDSET();
	CARDSET(QByteArray dataIn);
	CARDSET(qint8[], int size);
	CARDSET(CARD[], int size);
	~CARDSET();
	QByteArray tranToSig();
	bool add(CARD);
	bool remove(CARD);
private:
	std::vector<CARD> cards;
	int c_num;
};

struct SIGNAL {
	int signalNum;
	CARDSET cardTransfer;
};